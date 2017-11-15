<?php

// @codeCoverageIgnore

/**
 * Provides functions to use Virtuoso full-text search operator
 * Virtuoso wants the following modifications compared to a JenaText search :
 *   1. The bif:contains predicated must be _after_ the "?s ?prop ?match." pattern
 *   2. Virtuoso does not handle unbound variables so an unbound variable is explicitely inserted with BIND(IRI("") AS ?unbound)
 *   3. the "?graph" variable needs to be deleted from the SELECT and ORDER BY clause
 */
class VirtuosoSparql extends GenericSparql
{

    /*
     * Characters that need to be quoted for the Lucene query parser.
     * See http://lucene.apache.org/core/4_10_1/queryparser/org/apache/lucene/queryparser/classic/package-summary.html#Escaping_Special_Characters
     */
    const LUCENE_ESCAPE_CHARS = ' +-&|!(){}[]^"~?:\\/';

    /*
     * note: don't include * because we want wildcard expansion
     *
     * /**
     * Make a Virtuoso query condition that narrows the amount of search
     * results in term searches
     *
     * @param string $term search term
     * @param string $property property to search (e.g. 'skos:prefLabel'), or '' for default
     * @return string SPARQL text search clause
     */
    private function createTextQueryCondition($term, $property = '', $lang = '')
    {
        // construct the lucene search term for jena-text
        
        // 1. Ensure characters with special meaning in Lucene are escaped
        $lucenemap = array();
        foreach (str_split(self::LUCENE_ESCAPE_CHARS) as $char) {
            $lucenemap[$char] = '\\' . $char; // escape with a backslash
        }
        $term = strtr($term, $lucenemap);
        
        // 2. Ensure proper SPARQL quoting
        $term = str_replace('\\', '\\\\', $term); // escape backslashes
        $term = str_replace("'", "\\'", $term); // escape single quotes
        
        $langClause = empty($lang) ? '' : "FILTER (langMatches(lang(?match), \"" + $lang + "\"))";

        // This is where Virtuoso bif:contains is inserted
        $sparqlRequest = <<<EOQ
              ?match bif:contains '"$term"' option (score ?sc).  
EOQ;
        return $sparqlRequest;
    }

    /**
     * Generate Virtuoso search condition for matching labels in SPARQL
     *
     * @param string $term
     *            search term
     * @param string $searchLang
     *            language code used for matching labels (null means any language)
     * @return string sparql query snippet
     */
    protected function generateConceptSearchQueryCondition($term, $searchLang)
    {
        // make text query clauses
        $textcond = $this->createTextQueryCondition($term, '?prop', $searchLang);
        
        if ($this->isDefaultEndpoint()) {
            // if doing a global search, we should target the union graph instead of a specific graph
            $textcond = "GRAPH <urn:x-arq:UnionGraph> { $textcond }";
        }
        
        return $textcond;
    }

    /**
     * Query for concepts using a search term.
     * 
     * @param array|null $fields
     *            extra fields to include in the result (array of strings). (default: null = none)
     * @param boolean $unique
     *            restrict results to unique concepts (default: false)
     * @param ConceptSearchParameters $params
     * @return string sparql query
     */
    protected function generateConceptSearchQuery($fields, $unique, $params, $showDeprecated = false)
    {
        $vocabs = $params->getVocabs();
        $gcl = $this->graphClause;
        $fcl = empty($vocabs) ? '' : $this->generateFromClause($vocabs);
        $formattedtype = $this->formatTypes($params->getTypeLimit());
        $formattedfields = $this->formatExtraFields($params->getLang(), $fields);
        $extravars = $formattedfields['extravars'];
        $extrafields = $formattedfields['extrafields'];
        $schemes = $params->getSchemeLimit();
        
        $schemecond = '';
        if (! empty($schemes)) {
            foreach ($schemes as $scheme) {
                $schemecond .= "?s skos:inScheme <$scheme> . ";
            }
        }
        
        // extra conditions for parent and group, if specified
        $parentcond = ($params->getParentLimit()) ? "?s skos:broader+ <" . $params->getParentLimit() . "> ." : "";
        $groupcond = ($params->getGroupLimit()) ? "<" . $params->getGroupLimit() . "> skos:member ?s ." : "";
        $pgcond = $parentcond . $groupcond;
        
        $orderextra = $this->isDefaultEndpoint() ? $this->graph : '';
        
        // make VALUES clauses
        $props = array(
            'skos:prefLabel',
            'skos:altLabel'
        );
        if ($params->getHidden()) {
            $props[] = 'skos:hiddenLabel';
        }
        
        $filterGraph = empty($vocabs) ? $this->formatFilterGraph($vocabs) : '';

        $filterDeprecated="";
        //show or hide deprecated concepts
        if(!$showDeprecated){
            $filterDeprecated="FILTER NOT EXISTS { ?s owl:deprecated true }";
        }
        
        // remove futile asterisks from the search term
        $term = $params->getSearchTerm();
        while (strpos($term, '**') !== false) {
            $term = str_replace('**', '*', $term);
        }
        
        $labelpriority = <<<EOQ
        FILTER(BOUND(?s))
        BIND(IRI("") AS ?unbound)
        BIND(STR(SUBSTR(?hit,1,1)) AS ?pri)
        BIND(IF((SUBSTR(STRBEFORE(?hit, '@'),1) != ?pri), STRLANG(STRAFTER(?hit, '@'), SUBSTR(STRBEFORE(?hit, '@'),2)), STRAFTER(?hit, '@')) AS ?match)
        BIND(IF((?pri = "1" || ?pri = "2") && ?match != ?label, ?match, ?unbound) as ?plabel)
        BIND(IF((?pri = "3" || ?pri = "4"), ?match, ?unbound) as ?alabel)
        BIND(IF((?pri = "5" || ?pri = "6"), ?match, ?unbound) as ?hlabel)
EOQ;
        $innerquery = $this->generateConceptSearchQueryInner($params->getSearchTerm(), $params->getLang(), $params->getSearchLang(), $props, $unique, $filterGraph);
        if ($params->getSearchTerm() === '*' || $params->getSearchTerm() === '') {
            $labelpriority = '';
        }
        $query = <<<EOQ
        SELECT DISTINCT ?s ?label ?plabel ?alabel ?hlabel  ?notation (GROUP_CONCAT(DISTINCT STR(?type);separator=' ') as ?types) $extravars
        $fcl
        WHERE {
         $gcl {
          {
          $innerquery
          }
          $labelpriority
          $formattedtype
          { $pgcond
           ?s a ?type .
           $extrafields $schemecond
          }
          $filterDeprecated
         }
         $filterGraph
        }
        GROUP BY ?s ?match ?label ?plabel ?alabel ?hlabel ?notation 
        ORDER BY LCASE(STR(?match)) LANG(?match) $orderextra
EOQ;
        return $query;
    }

    protected function generateConceptSearchQueryInner($term, $lang, $searchLang, $props, $unique, $filterGraph)
    {
        $valuesProp = $this->formatValues('?prop', $props);
        $textcond = $this->generateConceptSearchQueryCondition($term, $searchLang);
        $rawterm = str_replace('\\', '\\\\', str_replace('*', '', $term));
        
        // graph clause, if necessary
        $graphClause = $filterGraph != '' ? 'GRAPH ?graph' : '';
        
        // extra conditions for label language, if specified
        $labelcondLabel = ($lang) ? "LANGMATCHES(lang(?label), '$lang')" : "lang(?match) = '' || LANGMATCHES(lang(?label), lang(?match))";
        // if search language and UI/display language differ, must also consider case where there is no prefLabel in
        // the display language; in that case, should use the label with the same language as the matched label
        $labelcondFallback = ($searchLang != $lang) ? "OPTIONAL { # in case previous OPTIONAL block gives no labels\n" . "?s skos:prefLabel ?label . FILTER (LANGMATCHES(LANG(?label), LANG(?match))) }" : "";
        
        // Including the labels if there is no query term given.
        if ($rawterm === '') {
            $labelClause = "?s skos:prefLabel ?label .";
            $labelClause = ($lang) ? $labelClause . " FILTER (LANGMATCHES(LANG(?label), '$lang'))" : $labelClause . "";
            return $labelClause . " BIND(?label AS ?match)";
        }
        
        /*
         * This query does some tricks to obtain a list of unique concepts.
         * From each match generated by the text index, a string such as
         * "1en@example" is generated, where the first character is a number
         * encoding the property and priority, then comes the language tag and
         * finally the original literal after an @ sign. Of these, the MIN
         * function is used to pick the best match for each concept. Finally,
         * the structure is unpacked to get back the original string. Phew!
         */
        $hitvar = $unique ? '(MIN(?matchstr) AS ?hit)' : '(?matchstr AS ?hit)';
        $hitgroup = $unique ? 'GROUP BY ?s ?label ?notation' : '';
        
        $query = <<<EOQ
       SELECT DISTINCT ?s ?label ?notation $hitvar
       WHERE {
        $graphClause {
         {
         $valuesProp
         VALUES (?prop ?pri) { (skos:prefLabel 1) (skos:altLabel 3) (skos:hiddenLabel 5)}
         ?s ?prop ?match. 
         $textcond
        }
         UNION
         { ?s skos:notation "$rawterm" }
         OPTIONAL {
          ?s skos:prefLabel ?label .
          FILTER ($labelcondLabel)
         } $labelcondFallback
         BIND(IF(langMatches(LANG(?match),'$lang'), ?pri, ?pri+1) AS ?npri)
         BIND(CONCAT(STR(?npri), LANG(?match), '@', STR(?match)) AS ?matchstr)
         OPTIONAL { ?s skos:notation ?notation }
        }
        $filterGraph
       }
       $hitgroup
EOQ;
        return $query;
    }
}

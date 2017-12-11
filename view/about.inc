<h1>Les vocabulaires contrôlés de la législation luxembourgeoise</h1>
<p>Les systèmes de diffusion de la loi luxembourgeoise, <a href='http://legilux.public.lu'>Legilux</a> pour la recherche et la navigation dans les textes de lois, et <a href='http://data.legilux.public.lu'>Casemates</a> pour l’accès aux données et aux fichiers bruts réutilisables, sont basés sur les technologies du web sémantique. Cette approche permet des descriptions riches et détaillées des textes de loi, qui s’appuient sur des référentiels pour tous les aspects de description d&#39;une loi : ses thématiques, le type d&#39;acte, son ministère d’origine, ses formats de fichier, etc.</p>
<p>Tous ces vocabulaires contrôlés sont mis à disposition dans cette interface, permettant la compréhension, la navigation et la réutilisation de ces listes et de ses hiérarchies.</p>
<h2>Vocabulaires disponibles</h2>
<p><em>A compléter ou on recopie le tableau de la doc de Legilux ?</em></p>
<h2>License d&#39;utilisation des vocabulaires</h2>
<p>Les vocabulaires sont mis à disposition selon la licence d’utilisation <a href='http://creativecommons.org/licenses/by/4.0/'>http://creativecommons.org/licenses/by/4.0/</a> qui autorise leur réutilisation pour des utilisations commerciales ou non.</p>
<h2>Réutilisation de vocabulaires</h2>
<p>Le luxembourg s&#39;appuie sur les vocabulaires déjà existants de langues et de pays publiés par l&#39;Office des Publications de l&#39;UE sur le <a href='http://publications.europa.eu/mdr/authority/index.html'>Metadata Registry</a>.</p>
<h2>Vocabulaires ELI</h2>
<p>L&#39;identifiant européen de la législation (ELI – « European Legislation Identifier ») est un projet qui permet de rendre la législation accessible en ligne dans un format normalisé. Cette initiative, dont le Luxembourg est le père fondateur, regroupe différents pays et les institutions de l&#39;UE. Elle est inscrite dans les conclusions du Conseil du 26 octobre 2012<a href='http://eur-lex.europa.eu/legal-content/FR/TXT/?uri=CELEX:52012XG1026(01)'> (2012/C 325/02)</a>.</p>
<p>Plus d’informations sont disponibles sur<a href='http://eur-lex.europa.eu/eli'> http://eur-lex.europa.eu/eli</a>.</p>
<p>Un certain nombre de vocabulaires sont nécessaires pour la publication en ELI des métadonnées de la loi du Luxembourg :</p>
<ul><li>
Les types d&#39;acte, pour la propriété <a href='http://data.europa.eu/eli/ontology#type_document'>eli:type_document</a>;</li>
<li>
Les thématiques juridiques pour la propriété <a href='http://data.europa.eu/eli/ontology#is_about'>eli:is_about</a>;</li>
<li>
Les institutions juridiques pour la propriété <a href='http://data.europa.eu/eli/ontology#responsibility_of_agent'>eli:responsibility_of_agent</a>, eli:publisher_agent, <a href='http://data.europa.eu/eli/ontology#rightsholder_agent'>eli:rightsholder_agent</a>;</li>
<li>
Les lieux pour <a href='http://data.europa.eu/eli/ontology#relevant_for'>eli:relevant_for</a>;</li>
<li>
Les langues pour la propriété <a href='http://data.europa.eu/eli/ontology#language'>eli:language</a>;</li>
</ul>
<h2>Modèle de données des vocabulaires</h2>
<h4>Vocabulaires utilisés</h4>
<p>Les vocabulaires sont structurés dans le standard <a href='https://www.w3.org/TR/2009/REC-skos-reference-20090818/'>SKOS</a>, avec plusieurs extensions :</p>
<ul><li>
DubinCore Terms pour la description des vocabulaires, les dates de création des Concepts (dct:created), leur source (<code>dct:source</code>) ou les liens de remplacement des concepts dépréciés (<code>dct:replaces</code>);</li>
<li>
Euvoc pour les dates de début et de fin de validité des Concepts (<code>euvoc:startDate</code>, <code>euvoc:endDate</code>) et leur statut (<code>euvoc:status</code>);</li>
<li>
Des extensions spécifiques dans l&#39;ontologie <a href='%5Bhttp://data.legilux.public.lu/ontology%5D(http://data.legilux.public.lu/ontology)'>JOLux</a> pour la description des personnes;</li>
</ul>
<h4>Concepts dépréciés</h4>
<p>Certains concepts sont dépréciés, c&#39;est-à-dire qu&#39;ils ont été remplacés par un nouveau terme, et/ou que leur utilisation dans une indexation documentaire est déconseillée. Dans ce cas :</p>
<ul><li>
Le concept porte la valeur <code>euvoc:status</code> avec la valeur <code>http://publications.europa.eu/resource/authority/concept-status/DEPRECATED</code></li>
<li>
Le concept porte la valeur <code>owl:deprecated</code>avec la valeur <code>true</code>;</li>
<li>
Il peut indiquer son concept de remplacement avec la propriété <code>dct:replacedBy</code>;</li>
<li>
Il peut indiquer sa date de fin de validité avec la propriété <code>euvoc:endDate</code>;</li>
</ul>
<p>Ces concepts font l&#39;objet d&#39;un affichage spécial avec un avertissement (comme par exemple &quot;<a href='http://data.legilux.public.lu/resource/authority/legal-subject/1604'>infrastructure</a>&quot; ).</p>
<h4>Liens entre les vocabulaires</h4>
<p>Des articulations existent entre certain vocabulaires :</p>
<ul><li>
Lien entre l&#39;historique des institutions juridiques et les institutions actuelles;</li>
<li>
Lien entre un type de projet législatif et le type d&#39;acte issu du projet;</li>
<li>
Lien entre une personne et son institution d&#39;appartenance d&#39;une part, et sa fonction d&#39;autre part;</li>
</ul>
<h2>Structure des URIs</h2>
<p>Les URIs des vocabulaires (ConceptScheme) suivent la forme :</p>
<pre><code>
http://data.legilux.public.lu/resource/authority/{id-vocabulaire}
</code></pre>
<p>Par exemple : <a href='http://data.legilux.public.lu/resource/authority/legal-subject-theme' target='_blank' >http://data.legilux.public.lu/resource/authority/legal-subject-theme</a></p>
<p>Les URIs des concepts suivent la forme :</p>
<pre><code>
http://data.legilux.public.lu/resource/authority/{id-vocabulaire}/{id-concept}
</code></pre>
<p>Par exemple : <a href='http://data.legilux.public.lu/resource/authority/legal-institution/SCL.' target='_blank' >http://data.legilux.public.lu/resource/authority/legal-institution/SCL.</a></p>
<p>Il y a une exception à cette règle : les URIs des Concepts dans les vocabulaires <code>legal-subject-theme</code>, <code>legal-subject-place</code>, et <code>legal-subject-organisation</code> ont des URIs de la forme <code>.../authority/legal-subject/{id-concept}</code>.</p>
<p>Les URIs des collections suivent la forme :</p>
<pre><code>
http://data.legilux.public.lu/resource/authority/{id-vocabulaire}/collection/{id-collection}
</code></pre>
<p>Par exemple : <a href='http://data.legilux.public.lu/resource/authority/legal-institution/collection/INIT' target='_blank' >http://data.legilux.public.lu/resource/authority/legal-institution/collection/INIT</a></p>
<h2>Comment récupérer les données des vocabulaires</h2>
<h3>En téléchargeant les fichiers de données</h3>
<p>Les fichiers RDF source de tous les vocabulaires sont disponibles dans le portail Open Data du Luxembourg : <a href='http://data.public.lu' target='_blank' >http://data.public.lu</a> (chercher &quot;Legilux&quot;).</p>
<h3>Via les URIs des Concepts (négociation de contenu)</h3>
<p>Les URIs des Concepts et des ConceptSchemes sont déréférençables pour obtenir une représentation RDF/XML, Turtle, JSON-LD ou HTML. Par exemple</p>
<pre><code>
curl --header &quot;Accept: application/rdf+xml&quot; http://data.legilux.public.lu/resource/authority/legal-subject/494
</code></pre>
<h3>En SPARQL</h3>
<h4>Endpoint SPARQL Casemates</h4>
<p>Les données des vocabulaires (ainsi que toutes les métadonnées des lois), sont accessible dans le service SPARQL de Casemates à <a href='http://data.legilux.public.lu/sparql.' target='_blank' >http://data.legilux.public.lu/sparql.</a></p>
<p>Chaque vocabulaire est chargé dans un graphe nommé séparé, dont l&#39;URI est</p>
<pre><code>
http://{URI-du-concept-scheme}/graph
</code></pre>
<p>Par exemple <a href='http://data.legilux.public.lu/resource/authority/legal-subject-theme/graph' target='_blank' >http://data.legilux.public.lu/resource/authority/legal-subject-theme/graph</a></p>
<p>Pour interroger un vocabulaire spécifique on peut donc facilement limiter la requête au graphe correspondant. Par exemple :</p>
<pre><code class='language-SPARQL' lang='SPARQL'>
SELECT ...
FROM &lt;http://data.legilux.public.lu/resource/authority/legal-subject-theme/graph&gt;
WHERE {  
    ...
}
</code></pre>
<h4>Exemples de requêtes SPARQL sur les vocabulaires</h4>
<h5>Lister tous les vocabulaires et le graphe nommé correspondant</h5>
<pre><code>
PREFIX skos: &lt;http://www.w3.org/2004/02/skos/core#&gt; 
SELECT ?vocabulaire (STR(?prefLabel) AS ?label) ?graph
WHERE {
  GRAPH ?graph {
    ?vocabulaire a skos:ConceptScheme .
    ?vocabulaire skos:prefLabel ?prefLabel .
    FILTER(langMatches(lang(?prefLabel), &quot;fr&quot;))
  }
} 
ORDER BY ?label
</code></pre>
<h5>Lister tous les concepts d&#39;un vocabulaire avec leur libellé</h5>
<pre><code>
PREFIX skos: &lt;http://www.w3.org/2004/02/skos/core#&gt; 
SELECT ?concept (STR(?prefLabel) AS ?label)
FROM &lt;http://data.legilux.public.lu/resource/authority/legal-subject-organisation/graph&gt;
WHERE {
  ?concept a skos:Concept .
  ?concept skos:prefLabel ?prefLabel
} 
ORDER BY ?label
</code></pre>
<h5>Rechercher un concept par son libellé</h5>
<pre><code>
PREFIX skos: &lt;http://www.w3.org/2004/02/skos/core#&gt; 
SELECT ?concept ?vocabulaire ?prefLabel
WHERE {
  ?concept a skos:Concept .
  ?concept skos:inScheme ?vocabulaire .
  ?concept skos:prefLabel|skos:altLabel ?label .
  FILTER(CONTAINS(LCASE(STR(?label)), &quot;luxembourg&quot;)) .
  ?concept skos:prefLabel ?prefLabel .
  FILTER(lang(?prefLabel) = &quot;fr&quot;)
} 
ORDER BY ?prefLabel
</code></pre>
<h2>Outils de gestion et de diffusion des vocabulaires contrôlés</h2>
<p>La maintenance et la diffusion des vocabulaires contrôlés de Legilux repose sur 3 outils :</p>
<ol start='' ><li>
Le <a href='http://labs.sparna.fr/skos-play/convert'>convertisseur Excel vers SKOS</a> de SKOS Play permet de produire des fichiers SKOS à partir d&#39;un tableau Excel dans lequel sont maintenus les données des vocabulaires;</li>
<li>
Les référentiels SKOS sont chargés dans <a href='https://virtauoso.openlinksw.com'>Virtuoso</a> qui assure le <a href='http://data.legilux.public.lu/sparql'>service SPARQL de Casemates</a>;</li>
<li>
<a href='http://skosmos.org'>Skosmos</a> est l&#39;outil qui offre les écrans de navigation et de recherche (ceux que vous voyez actuellement) dans les vocabulaires en interrogeant Casemates;</li>
</ol>
<p>De nombreuses contributions ont été faites au cours de ce projet de publications de vocabulaires aux projets open-source SKOS Play et Skosmos.</p>
<h2>Liens utiles</h2>
<ul><li>
<a href='http://data.legilux.public.lu'>Casemates</a></li>
<li>
<a href='http://legilux.public.lu/editorial/casemates'>Le web sémantique dans Casemates et Legilux</a></li>
<li>
<a href='https://data.public.lu/en/datasets/legilux-journal-officiel-du-grand-duche-de-luxembourg/'>Portail open data du Luxembourg data.public.lu : données de Legilux</a></li>
<li>
<a href='http://skosmos.org/'>Skosmos</a></li>
</ul>
<?php

/**
 * Class for handling entries in the concept history.
 */
class HistoryEntry
{
    /** the vocabulary corresponding to this history entry */
    private $vocab;
    /**
     * the concept object of this concept in the associated vocab
     */
    private $concept;

    public function __construct($vocab, $concept)
    {
        $this->vocab = $vocab;
        $this->concept = $concept;
    }

    public function getVersion()
    {
        return $this->vocab->getConfig()->getVersion();
    }
    
    public function getVersionDate()
    {
        return $this->vocab->getConfig()->getVersionDate();
    }
    
    public function getConcept()
    {
        return $this->concept;
    }

    public function getVersionDateAsString()
    {
        // if the versionDate is a date object converting it to a human readable representation.
        if ($this->getVersionDate() instanceof DateTime) {
            try {
                return Punic\Calendar::formatDate($this->getVersionDate(), 'short');
            } catch (Exception $e) {
                trigger_error($e->getMessage(), E_USER_WARNING);
                return (string) $this->getVersionDate();
            }
        }
        return $this->getVersionDate();
    }
    
    public function getVocab()
    {
        return $this->vocab;
    }
    
    
}

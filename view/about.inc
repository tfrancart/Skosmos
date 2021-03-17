{# This is the template for the about page. You can enter any html here and show different language versions by using the lang value in a twig conditional as demonstrated below. #}
{% if request.lang == 'fr' %}

<p>Bienvenue sur la plateforme d’exposition et de partage des référentiels thématiques INRAE.</p>

<p>Ces référentiels sont représentés selon les standards du web sémantique et suivent les principes FAIR : standard de représentation SKOS, identifiants uniques et pérennes, métadonnées riches, etc.</p>

<p>L'export intégral en RDF/XML du Thesaurus INRAE est disponible en téléchargement <a href="https://vocabulaires.irstea.fr/exports/thesaurus/latest/thesaurusINRAE.rdf">ici</a>.</p>

<div>
	<img src="resource/pics/DipSO_logo_gradient_rvb.png" style="max-width:200px;" />
</div>


<p>Ces ressources sont administrées par le pôle Num4Sci de la Direction pour la Science Ouverte. Vous pouvez nous contacter à l’aide du formulaire en cliquant sur '<a href="feedback">Nous contacter</a>'</p>

<p>Nous utilisons <a href="http://skosmos.org">Skosmos</a>, un outil libre pour visualiser les thésaurus et les ontologies.</p>

{% elseif request.lang == 'en' %}

<p>Welcome to the INRAE platform for exhibiting and sharing INRAE's knowledge organization systems.</p>

<p>These semantic resources are represented according to the Semantic Web standards and follow the FAIR principles: SKOS representation standard, unique and persistent identifiers, rich metadata, etc.</p>

<p>The full export of the INRAE Thesaurus in RDF/XML is available for download <a href="https://vocabulaires.irstea.fr/exports/thesaurus/latest/thesaurusINRAE.rdf">here</a>.</p>

<div>
        <img src="resource/pics/DipSO_logo_gradient_rvb.png" style="max-width:200px;" />
</div>


<p>These resources are administered by the Num4Sci team from the Open Science Department of INRAE. Click on « Feedback » to contact us.</p>

<p>We use <a href="http://skosmos.org">Skosmos</a>, an open source terminology browser.</p>



{% endif %}

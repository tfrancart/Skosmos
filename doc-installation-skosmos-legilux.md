
# Procédure d'installation de Skosmos pour Legilux


Cette documentation explique comment déployer Skosmos pour donner accès aux vocabulaires dans Casemates.

Skosmos est une application PHP.


## Documentation de Skosmos

Pour référence, la documentation officielle de Skosmos est disponible dans le wiki Skosmos à https://github.com/NatLibFi/Skosmos/wiki/Installation.


## Prérequis

On recommande que Skosmos soit installé sur _une machine différente du serveur Casemates_ pour éviter des effets de bord ou des problèmes de sécurité.

Pour réaliser cette installation, on a besoin des composants suivants :

- Machine Linux _avec connexion Internet_. En particulier la machine doit pouvoir envoyer des requêtes SPARQL à Casemates (sur le port HTTP classique)
- git (pour récupérer les sources)
- Apache
- module `php` pour Apache
- les modules Apache `mod_rewrite`, `proxy` et `proxy_http`



## Récupérer les sources

La récupération des sources s'effectue avec git, depuis le dépôt qui contient la version customisée de Skosmos pour Legilux :

```
cd /var/www/html
git clone -b skosmos-legilux https://github.com/tfrancart/skosmos.git skosmos
```

Note : on pourrait remplacer le nom du répertoire `skosmos` par le répertoire `authority` pour être plus proche de la forme des URIs

Cette version de Skosmos contient déjà tous les fichiers de configuration nécessaires pour Skosmos, avec les connexion à Casemates et tous les vocabulaires paramétrés.


## Installer les dépendances

Lancer composer pour télécharger les dépendances PHP :


```
cd /var/www/html/skosmos
wget https://getcomposer.org/composer.phar
php composer.phar install --no-dev
```


## Configurer Apache

Skosmos a besoin que :

1. le module `mod_rewrite` pour Apache soit activé
2. la directive `AllowOverride All` soit activée pour le répertoire de Skosmos.

Typiquement, il s'agit de rajouter cet élément de configuration à Apache :

```
		# activer le module rewrite
		RewriteEngine On

        # SKOSMOS AllowOverride
        <Directory "/var/www/html/skosmos">
                AllowOverride All
        </Directory>
```


## Tester l'accès

Une fois les sources récupérées et Apache configuré :

1. Accéder à `http://<serveur-skosmos>/skosmos`. On doit avoir un résultat similaire à `http://erato.sparna.fr/authority`;
2. Sélectionner le vocabulaire "Thèmes". On doit voir la fiche du vocabulaire s'afficher, et une liste de concepts affichés sur la gauche;
3. Cliquer sur un concept sur la gauche; la "fiche" du concept doit s'afficher à droite;

## Configurer les redirections Apache

__Attention, cette partie de la doc n'a pas été testée, il faudra sans doute l'ajuster.__


Une fois Skosmos installé et une fois les fiches des concepts accessibles via Skosmos, il faut que les URIs des Concepts redirigent vers Skosmos plutôt que vers Casemates.

Voir la documentation de Skosmos à `https://github.com/NatLibFi/Skosmos/wiki/ServingLinkedData`.

La forme d'une URI de Concept est :

`http://data.legilux.public.lu/resource/authority/<id-du-vocabulaire>/<code-du-concept>`

Skosmos permet d'accéder directement à une ressource via son URL `/entity` avec en paramètre l'URI du Concept :

`http://<serveur-skosmos>/skosmos/entity?uri=<uri-du-concept>`

Par exemple :

`http://erato.sparna.fr/authority/entity?uri=http://data.legilux.public.lu/resource/authority/resource-type/LOI`

On peut donc ajouter cette directive Apache pour effectuer la redirection.

```
RewriteEngine On
RewriteRule ^/resource/authority/(.*) http://<serveur-skosmos>/skosmos/entity?uri=http://data.legilux.public.lu/resource/authority/$0 [P]
```

## Comment publier un nouveau vocabulaire ?

Lorsqu'un nouveau vocabulaire est prêt à être publié, il faut :

1. Convertir le nouveau vocabulaire en SKOS et le charger dans le triplestore Casemates (procédure classique de rechargement des vocabulaires);
2. Modifier le fichier de config `vocabularies-legilux.ttl` à la racine du répertoire d'installation de Skosmos pour ajouter ce nouveau vocabulaire à la config; cela peut se faire manuellement ou en éditant un tableau Excel source (voir ci-dessous);
3. Commiter la modification du fichier dans ce repository;
4. Tester que le vocabulaire apparait bien sur la home page de Skosmos, et tester qu'on voit bien quelque chose quand on clique dessu; il n'est pas nécessaire de redémarrer le serveur;

### Déclarer un nouveau vocabulaire dans `vocabularies-legilux.ttl`

#### A la main :

Copier-coller un bloc de vocabulaire, et ajuster les informations en conséquence; en particulier, il faut ajuster :

  - l'URI du vocabulaire sur la première ligne (`this:resource-type` dans l'exemple ci-dessous) pour qu'elle corresponde à la forme des URIs des concepts dans le nouveau vocabulaire;
  - `dct:title` et `skosmos:shortName` : mettre le nom du nouveau vocabulaire;
  - le `dct:subject` qui sert à classer le vocabulaire sur la Home page de Skosmos;
  - `skosmos:fullAlphabeticalIndex` : mettre à false si le vocabulaire est très gros ( > ~500 concepts)
  - `skosmos:mainConceptScheme` mettre l'URI du nouveau Concept Scheme
  - `skosmos:sparqlGraph` : ajuster pour correspondre au graphe dans lequel est stocké ce vocabulaire dans Casemates;
  - `void:dataDump` : ajuster l'URI du graphe;
  - `void:uriSpace` : ajuster la fin de l'URI pour qu'elle corresponde au début des URIs des Concepts;
  

```
this:resource-type a skosmos:Vocabulary , void:Dataset ;
	dct:subject vocdomain:3-types ;
	dct:title "Types des actes"@fr ;
	dct:type mdrtype:NAL ;
	skosmos:defaultLanguage "fr" ;
	skosmos:explicitLanguageTags "false"^^xsd:boolean ;
	skosmos:fullAlphabeticalIndex "true"^^xsd:boolean ;
	skosmos:hasMultilingualProperty skos:definition , skos:scopeNote ;
	skosmos:language "fr" ;
	skosmos:loadExternalResources "true"^^xsd:boolean ;
	skosmos:mainConceptScheme <http://data.legilux.public.lu/resource/authority/resource-type> ;
	skosmos:shortName "Types des actes"@fr ;
	skosmos:showChangeList "true"^^xsd:boolean ;
	skosmos:showNotation "false"^^xsd:boolean ;
	skosmos:showStatistics "false"^^xsd:boolean ;
	skosmos:showTopConcepts "true"^^xsd:boolean ;
	skosmos:sparqlGraph <http://data.legilux.public.lu/resource/authority/resource-type/graph> ;
	void:dataDump <http://data.legilux.public.lu/sparql?query=CONSTRUCT { ?s ?p ?o } WHERE { GRAPH <http://data.legilux.public.lu/resource/authority/resource-type/graph\> { ?s ?p ?o } }&format=application%2Frdf%2Bxml> ;
	void:sparqlEndpoint <http://data.legilux.public.lu/sparql> ;
	void:uriSpace "http://data.legilux.public.lu/resource/authority/resource-type/" .
```


#### Via le tableau Excel

1. Modifier le fichier Excel à https://docs.google.com/spreadsheets/d/1zsPBpbd_xQRQbKanAXXd2XseuVEIE0nPf_AuE9Lttoc/edit?usp=sharing et ajouter une ligne pour déclarer le nouveau vocabulaire.
2. Convertir le fichier via Skos Play 
3. Remplacer `vocabularies-legilux.ttl` par le résultat de la conversion

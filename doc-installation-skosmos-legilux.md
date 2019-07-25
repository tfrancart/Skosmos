
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

* Attention, cette partie de la doc n'a pas été testée, il faudra sans doute l'ajuster. *


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

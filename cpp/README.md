# TP OOP

Songsheng YING
INF224


## Faire tourner le code

Dans le terminal en répertoire de travail en cours, ```make all```, ```make server```, ```make client``` vont compiler les parties du projet.

```make run```, ```make run-server```, ```make run-client``` vont demarrer les deux parties du projet.

Pour plus de control, le serveur peut se lancer avec ```/path/to/server [port] *[serial file ./src/serial.out]```, le client peut se lancer avec ```java Remote [adresse] [port]```.


## Réponses aux questions

+ 4e, comment appelle-t'on ce type de méthode et comment faut-il les déclarer : en mettant ```virtual``` devant la signature de la fonction et ```=0``` dérrière en lui rendant virtuelle pure;
+ 4e, raison de ne pouvoir plus instancer des objets de la classe de base : parce que la classe est virtuelle à cause de la fonction virtuelle pure alors que l'instance de classe de base n'a pas cette fonction implementée.
+ 5e, proriété : polymorphisme
+ 5e, la nécessité de le faire dans C++ : avec les méthodes virtuelles
+ 5e, le tableau contient les pointeurs vers ces objets : d'une part à cause de la taille différente des sous-classes qui ne peut pas être prévue lors de la construction du tableau, d'autre part en raison du mécanisme de ```new``` qui renvoie un pointeur.
+ 5e, le type de pointés est nécessairement des sous-classes de type de pointé déclaré pour ce tableau, puisque C++ n'autorise que des ```upcasting``` sauf si explicité.
+ 5e, comparaison avec JAVA, JAVA utilise par défault les références des objets non base, et les méthodes sont par défault virtuelles.
+ 6e, plein contrôle sur le tableau de durées des chapitres au sein de la classe mais pas dehors : protection de pointeur et du contenu pointé s'implémentent avec le cast de "const" sur le pointeur et le pointé.
+ 6e, défense contre la modification des contenus pointés retournés : genre ```const int * const```.
+ 7e, évite de fuite mémoire pour la classe ```Film```, dans laquelle il s'agit des allocations avec ```new```.
+ 7e, la copie d'objet copie des membres variables de l'instance, incluant les pointeurs. Sauf il faut copier les contenus pointés au lieu de copier simplement les pointeurs. (Une copie profonde)
+ 10e, pour éviter la manipulation des objets hors classe de gestion, on peut supprimer les opérateurs ```new``` et ```new[]``` pour éviter les créations des objets par allocation mémoire dynamique, alors on peut pas ```delete``` les objets sous smart pointers. Mais pour éviter les manipulations des instances allouées sur stack, il nous faut mettre en privé les constructeurs et créer une méthode privée de créations des smart pointers, en gardant la classe gestionnaire comme un ```friend```.

## Questions traitées

### C++/Objet

1 - 13, avec les questions additionnelles de 10.2 (manipulation ```new```, ```delete```), 11.1 (list, dump), 12.1 (opérateurs ```<<```, ```>>```).

### Java Swing

1 - 4

## Notes sur 12e étape

+ Dans le projet, on a surchargé l'opérateur ```<<``` de la classe multimédia, et créé une méthode virtuelle spécifique pour chaque sous-classes.
+ Par contre l'opérateur ```>>``` n'est pas surchargé, à cause du principe d'administration centralisée des objets, alors c'est à la classe de gestion de les créer. On a ainsi surchargé l'opérateur de cette classe de gestion, et implémenté les traitements de toutes les sous-classes de multimédia.
+ Si on décommente la section ```dump``` dans ```main.cpp```, le serveur va sérialiser la base de donnnée au début d'exécution.
+ Sinon, depuis le client, en cliquant sur le boutton ```dump```, on peut aussi apercevoir ce qui ce passe pour la sérialisation.
+ Pour désérialiser une base, il suffit de supplier le fichier au démarrage du serveur, en tapant dans un terminal ```./server [port] [file]```


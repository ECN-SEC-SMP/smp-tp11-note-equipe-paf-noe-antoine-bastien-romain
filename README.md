# Les Aventuriers du Rail – TP11

## Règles du jeu

### Mise en place

- Chaque joueur reçoit **20 wagons** d'une couleur (rouge, jaune, vert ou bleu).
- Les cartes Train sont mélangées et **4 cartes** sont distribuées à chaque joueur.
- Les tickets sont mélangés et **2 tickets** sont distribués à chaque joueur.
- Les cartes restantes forment une pioche face cachée ; idem pour les tickets.

### Déroulement d'un tour

À son tour, un joueur effectue **une seule** des actions suivantes :

1. **Piocher** deux cartes Train depuis la pioche.
2. **Poser des wagons** sur une voie ferrée pour la prendre.
3. **Échanger ses tickets** : défausser ses deux tickets et en piocher deux nouveaux.

### Prendre une voie ferrée

- Le joueur joue autant de cartes Train de la **couleur correspondante** que la longueur de la voie.
- Les **locomotives** sont des jokers (remplacent n'importe quelle couleur).
- Une voie ne peut être prise **qu'une seule fois**.
- Pour les **voies doubles**, un joueur ne peut pas posséder les deux voies parallèles.

### Réussir un ticket

Un ticket est réussi quand les deux villes indiquées sont reliées par un **chemin continu de wagons** appartenant au joueur. Le joueur annonce alors « Ticket ! ».

### Grande Traversée

Le **premier joueur** à relier une ville de la côte ouest à une ville de la côte est remporte la carte Bonus Grande Traversée, qui compte comme un ticket réussi supplémentaire.

### Fin de partie

La partie s'arrête dès qu'un joueur :
- réussit son **6e ticket**, ou
- pose son **dernier wagon**.

---

## Compilation et exécution


### Build

```bash
cd build
cmake ..
make
```

### Lancer le jeu

```bash
cd build
./aventuriers
```

---

## Documentation

La documentation est générée avec **Doxygen** à partir des commentaires du code source.

### Générer la doc

```bash
doxygen Doxyfile
```

La documentation HTML est produite dans `docs/html/`. Ouvrir `docs/html/index.html` dans un navigateur pour la consulter.

---

## Tests

Les tests unitaires utilisent **Google Test**, téléchargé automatiquement par CMake.

### Compiler les tests

dans le repertoire du projet (pas dans build/ !!!!)

```bash
cmake --build build --target tests
```

### Exécuter les tests


```bash
cd build && ./tests
```

### CHOIX DE CONCEPTION : Expliquation diagramme de classe et diagramme use case 

Dans notre diagramme de classes, nous avons fait le choix d’organiser l’architecture autour de la classe Jeu, car elle représente le centre logique de notre système. C’est elle qui coordonne l’ensemble des éléments : les joueurs, le plateau, les pioches et le déroulement des tours. En regroupant dans cette classe les méthodes d’initialisation, de gestion des tours et de vérification de la fin de partie, nous assurons une vision globale et cohérente du fonctionnement du jeu. Ce choix nous permet aussi de clarifier les responsabilités : le plateau s’occupe uniquement de la carte, les joueurs gèrent leurs propres actions, et le jeu orchestre l’ensemble.
Nous avons conçu la classe Plateau comme le module chargé de la structure géographique. Elle contient toutes les villes et routes, ainsi qu’une méthode de chargement depuis un fichier CSV. Cela nous offre une grande flexibilité et permet d’adapter le jeu à n’importe quelle carte. Le plateau propose également des fonctions permettant d’identifier les connexions possibles, car il est naturel que ce soit lui qui détermine quelles routes sont accessibles à un joueur. Cette répartition des rôles renforce la modularité et évite que la logique se disperse dans d’autres classes qui n’en seraient pas responsables.
La classe Joueur regroupe toutes les informations propres à chaque participant, comme son nom, sa couleur, ses cartes, ses tickets et son nombre de wagons. Nous y avons intégré les actions qu’un joueur peut effectuer, telles que piocher des cartes, prendre une route ou échanger ses tickets. De plus, la présence d’une méthode permettant de vérifier s’il possède un chemin continu entre deux villes lui offre une autonomie cohérente avec les règles du jeu. À travers ces choix, nous avons cherché à construire un modèle où chaque entité possède clairement les données et comportements dont elle est responsable.
Les classes Route, Ville, Ticket et Carte ont été pensées pour représenter fidèlement les éléments fondamentaux du domaine. Une route relie deux villes, possède une couleur, une longueur et éventuellement un propriétaire, ce qui correspond directement aux mécaniques du jeu. Les villes restent volontairement simples afin de ne pas surcharger leur rôle. Les tickets, quant à eux, comportent les objectifs et une méthode permettant de tester leur validation, ce qui renforce la cohérence interne du modèle. Enfin, l’utilisation d’un enum Couleur nous permet d’éviter des valeurs ambiguës et garantit une meilleure fiabilité dans l’utilisation des couleurs.

Pour le diagramme de cas d’usage, nous avons représenté le Joueur comme acteur principal, car c’est lui qui interagit avec le système tout au long de la partie. Le cas d’usage « Jouer un tour » constitue le scénario central de notre modèle. Les différentes actions que le joueur peut réaliser au cours de son tour — piocher des cartes, échanger ses tickets, prendre une route ou valider un ticket — apparaissent comme des extensions du scénario principal. Nous avons choisi l’esthétique « extend » pour ces actions, car elles sont optionnelles et ne se produisent pas systématiquement à chaque tour. La détection de fin de partie est également représentée comme une extension, car elle n’intervient que dans des conditions particulières.
De plus, le cas d’usage « Initier la partie » est séparé du déroulement des tours, ce qui nous permet d’illustrer clairement la phase de préparation du jeu : chargement du plateau, distribution des cartes, choix des tickets, etc. Ainsi, notre diagramme de cas d’usage reflète fidèlement la structure du jeu tout en mettant en avant les différents scénarios possibles du point de vue du joueur.
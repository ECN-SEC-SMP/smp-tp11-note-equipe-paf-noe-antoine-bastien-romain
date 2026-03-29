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

```bash
cmake --build build --target tests
```

### Exécuter les tests


```bash
cd build && ./tests
```

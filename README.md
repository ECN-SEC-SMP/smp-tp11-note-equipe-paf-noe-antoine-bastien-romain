# Les Aventuriers du Rail – Mon Premier Voyage

Implémentation en C++ du jeu de plateau Les Aventuriers du Rail – Mon Premier Voyage, jouable de 2 à 4 joueurs en mode texte.

---

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

### Prérequis

- CMake ≥ 3.10
- Compilateur C++17 (g++, clang++)
- Connexion internet (pour le téléchargement de Google Test au premier build)

### Build

```bash
cmake -B build
cmake --build build
```

### Lancer le jeu

```bash
cd build
./aventuriers
```

> Le jeu doit être lancé depuis le dossier `build/` afin de trouver les fichiers de données `src/map.csv` et `src/ticket.csv`.

---

## Tests

Les tests unitaires utilisent **Google Test**, téléchargé automatiquement par CMake.

### Compiler les tests

```bash
cmake --build build --target tests
```

### Exécuter les tests

```bash
cd build && ctest
```

ou directement :

```bash
cd build && ./tests
```

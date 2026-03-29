                                E COLE C ENTRALE DE N ANTES




                          SMP - TP10
               TP noté - Les Aventuriers du Rail




                                       1 O BJECTIF
Le but de ce TP est d’implémenter en C++ une version simplifiée du jeu Les Aventuriers du
Rail – Mon Premier Voyage.
Le jeu devra permettre de jouer à 2 à 4 joueurs.


                                   2 R ÈGLES DU JEU
Le plateau représente un réseau de villes reliées par des voies ferrées colorées. La figure 2.1
montre un exemple de plateau de jeu.
Chaque joueur dispose :
   — de 20 wagons d’une couleur (rouge, jaune, vert ou bleu) ;
   — de cartes Train (6 couleurs + locomotives) ;
   — de tickets reliant deux villes.
Le but du jeu est d’être le premier à réussir 6 tickets.

                                    2.1 M ISE EN PLACE
   — Chaque joueur prend 20 wagons d’une couleur.
   — Mélanger les cartes Train et distribuer 4 cartes à chaque joueur.
   — Former une pioche face cachée avec les cartes restantes.
   — Mélanger les tickets et distribuer 2 tickets à chaque joueur.
   — Former une pioche face cachée avec les tickets restants.
   — Les cartes des joueurs restent secrètes.




                                                                                             1
                                F IGURE 2.1 – Plateau de jeu


                            2.2 D ÉROULEMENT D ’ UN TOUR
À son tour, un joueur effectue une seule action parmi :
   — Piocher deux cartes Train ;
   — Poser ses wagons sur une voie ferrée pour la prendre ;
   — Passer son tour pour défausser ses deux tickets et en reprendre deux nouveaux.

                            2.3 P RENDRE UNE VOIE FERRÉE
Pour prendre une voie ferrée :
   — Le joueur joue autant de cartes Train de la couleur correspondante que la longueur de
       la voie ;
   — Les cartes sont défaussées ;
   — Il place ses wagons sur la voie ;
   — Une voie ne peut être prise qu’une seule fois.
Les locomotives sont des jokers. Elles remplacent n’importe quel wagon de couleur.
Pour les voies doubles, un joueur ne peut pas prendre les deux voies parallèles.

                                 2.4 R ÉUSSIR UN TICKET
Un ticket est réussi lorsque les deux villes indiquées sont reliées par un chemin continu de
wagons appartenant au joueur.
Le joueur :
   — annonce “Ticket !” ;
   — place le ticket face visible ;




                                                                                          2
   — pioche un nouveau ticket.

                                  2.5 G RANDE TRAVERSÉE
Le premier joueur reliant une ville de la côte ouest à une ville de la côte est gagne une carte
Bonus “Grande traversée”.
Cette carte compte comme un ticket réussi.

                                       2.6 F IN DU JEU
Le jeu s’arrête :
   — lorsqu’un joueur réussit son 6e ticket ;
   — ou lorsqu’un joueur pose son dernier wagon.

                                   2.7 C ONTENU DU JEU
   — 1 plateau de jeu
   — 80 wagons en plastique (20 par joueur)
   — 72 cartes Train (10 cartes par couleur jaunes, vertes, blanches, noires, bleues, rouges et
     12 locomotives (multicolores))
   — 32 tickets
   — 4 cartes Bonus “Grande traversée”
   — 1 ticket d’or “Golden Ticket”


                                  3 T RAVAIL DEMANDÉ
Les données représentant les tickets et les routes entre les villes du plateaudevront être char-
gées depuis les fichiers CSV fournis.
Le programme devra permettre :
   — l’initialisation d’une partie ;
   — la gestion de 2 à 4 joueurs ;
   — la pioche de cartes ;
   — la prise de voie ferrée ;
   — la mise à jour des ressources ;
   — la vérification automatique qu’un chemin continu de wagons relie les deux villes d’un
      ticket via les routes possédées par le joueur ;
   — la détection de fin de partie.
Une interface texte complète est suffisante. L’état de la partie doit être lisible à tout moment.

Remarque : Quand il n’y a plus de tickets à piocher, les tickets défaussés sont mélangés et
remis dans la pioche.




                                                                                               3
                                  4 T RAVAIL À FAIRE
À l’issue du TP il est attendu dans le dossier GitHub de votre groupe :
    — une description de votre conception du jeu sous forme d’un diagramme de cas d’utili-
        sation et d’un diagramme de classes (en pdf ou en markdown) avec à minima
    — une implémentation en C++ pour permettre à plusieurs joueurs de jouer à tour de rôle
        avec un affichage de l’état de la partie sous forme texte, le code sera documenté et
        testé.
    — l’illustration du bon fonctionnement des différentes fonctionnalités par des jeux d’es-
        sais.
Le code sera documenté, testé et versionné sous GitHub dans la branche main de votre groupe.
Vous expliciterez dans le README les instructions de compilation et d’exécution.


                            5 C RITÈRES D ’ ÉVALUATION
   — Qualité de la conception et de la modélisation objet : 25%
   — Correct fonctionnement du moteur de jeu (gestion des tours, actions, fin de partie) :
     25%
   — Gestion des connexions entre villes et validation des tickets : 20%
   — Qualité du code (structure, lisibilité, séparation des responsabilités, documentation) :
     15%
   — Tests, robustesse et gestion des cas particuliers : 15%




                                                                                           4

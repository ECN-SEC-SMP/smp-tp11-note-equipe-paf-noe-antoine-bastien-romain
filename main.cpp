#include <iostream>
#include "headers/Jeu.h"

static int lireEntier(int min, int max) {
    int val;
    while (true) {
        if (std::cin >> val) {
            std::cin.ignore(1000, '\n');
            if (val >= min && val <= max) return val;
        } else {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
        std::cout << "Entree invalide, entrez un nombre entre " << min << " et " << max << " : ";
    }
}

int main() {
    std::cout << "Nombre de joueurs (2-4) : ";
    int nbJoueurs = lireEntier(2, 4);

    Jeu jeu;
    jeu.chargerDonnees("src/map.csv", "src/ticket.csv");
    jeu.initialiser(nbJoueurs);
    jeu.lancerPartie();

    return 0;
}

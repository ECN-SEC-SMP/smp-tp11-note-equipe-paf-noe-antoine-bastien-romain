#ifndef JEU_H
#define JEU_H

#include <vector>
#include <string>
#include "Plateau.h"
#include "Joueur.h"
#include "Pioche.h"
#include "CarteTrain.h"
#include "Ticket.h"

class Jeu {
private:
    Plateau plateau;
    std::vector<Joueur> joueurs;
    Pioche<CarteTrain> piocheCartes;
    Pioche<Ticket> piocheTickets;
    int joueurCourant;
    bool grandeTraverseeAttribuee;

    void actionPiocher();
    void actionPoserWagons();
    void actionEchangerTickets();
    void verifierGrandeTraversee(Joueur& joueur);
    void chargerTicketsCSV(const std::string& fichier);

public:
    Jeu();

    void initialiser(int nbJoueurs);
    void jouerTour();
    bool verifierFinPartie() const;
    void afficherEtat() const;
    void chargerDonnees(const std::string& fichierMap, const std::string& fichierTickets);
    void lancerPartie();
};

#endif

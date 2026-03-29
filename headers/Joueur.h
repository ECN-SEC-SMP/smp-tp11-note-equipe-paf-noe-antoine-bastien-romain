#ifndef JOUEUR_H
#define JOUEUR_H

#include <string>
#include <vector>
#include "Ticket.h"
#include "Route.h"
#include "Plateau.h"
#include "Couleur.h"
#include "CarteTrain.h"
#include "Pioche.h"

class Route;
class Plateau;

class Joueur {
private:
    std::string nom;
    Couleur couleur;
    int wagonsRestants;
    std::vector<CarteTrain> mainCartes;
    std::vector<Ticket> tickets;
    int ticketsReussis;
    bool aGrandeTraversee;

public:
    Joueur();
    Joueur(const std::string& nom, Couleur couleur);

    const std::string& getNom() const                       { return nom; }
    Couleur getCouleur() const                              { return couleur; }
    int getWagonsRestants() const                           { return wagonsRestants; }
    const std::vector<CarteTrain>& getMainCartes() const    { return mainCartes; }
    std::vector<Ticket>& getTickets()                       { return tickets; }
    int getTicketsReussis() const                           { return ticketsReussis; }
    bool getAGrandeTraversee() const                        { return aGrandeTraversee; }

    void setAGrandeTraversee(bool val)                      { aGrandeTraversee = val; }
    void incrementerTicketsReussis()                        { ticketsReussis++; }

    void ajouterCarte(const CarteTrain& carte);
    void ajouterTicket(const Ticket& ticket);
    void ajouterTicket(const Ticket& ticket);
    void diminuerWagons(int n);                             { wagonsRestants -= n;}

    std::vector<CarteTrain> selectionnerCartes(Couleur couleur, int longueur) const;

    void piocher(Pioche<CarteTrain>& pioche);
    bool poserWagons(Route& r, std::vector<CarteTrain>& cartes);
    void echangerTickets(Pioche<Ticket>& pioche);
    void verifierTickets(Plateau& plateau);
    bool aGagne() const;

    void afficher() const;
};

#endif

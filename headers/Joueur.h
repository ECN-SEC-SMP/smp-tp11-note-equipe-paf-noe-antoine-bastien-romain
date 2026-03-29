#ifndef JOUEUR_H
#define JOUEUR_H

#include <string>
#include <vector>
#include "Couleur.h"
#include "CarteTrain.h"
#include "Ticket.h"
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

    const std::string& getNom() const;
    Couleur getCouleur() const;
    int getWagonsRestants() const;
    const std::vector<CarteTrain>& getMainCartes() const;
    std::vector<Ticket>& getTickets();
    int getTicketsReussis() const;
    bool getAGrandeTraversee() const;

    void setAGrandeTraversee(bool val);
    void incrementerTicketsReussis();

    void ajouterCarte(const CarteTrain& carte);
    void ajouterTicket(const Ticket& ticket);
    void utiliserCartes(const std::vector<CarteTrain>& cartes);
    void diminuerWagons(int n);

    /// sélectionne d'abord les cartes de la bonne couleur, puis complète avec des locomotives si nécessaire
    std::vector<CarteTrain> selectionnerCartes(Couleur couleur, int longueur) const;

    void piocher(Pioche<CarteTrain>& pioche);
    bool poserWagons(Route& r, std::vector<CarteTrain>& cartes);
    void echangerTickets(Pioche<Ticket>& pioche);
    void verifierTickets(Plateau& plateau);
    bool aGagne() const;

    void afficher() const;
};

#endif

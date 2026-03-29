#ifndef JOUEUR_H
#define JOUEUR_H

#include <string>
#include <vector>
#include "Ticket.h"
#include "Route.h"
#include "Plateau.h"

class Route;
class Plateau;

class Joueur {
private:
    std::string nom;
    int wagonsRestants;
    std::vector<Ticket> tickets;
    int ticketsReussis;
    bool aGrandeTraversee;

public:
    Joueur();
    Joueur(const std::string& nom);

    const std::string& getNom() const                       { return nom; }
    int getWagonsRestants() const                           { return wagonsRestants; }
    std::vector<Ticket>& getTickets()                       { return tickets; }
    int getTicketsReussis() const                           { return ticketsReussis; }
    bool getAGrandeTraversee() const                        { return aGrandeTraversee; }

    void setAGrandeTraversee(bool val)                      { aGrandeTraversee = val; }
    void incrementerTicketsReussis()                        { ticketsReussis++; }

    void ajouterTicket(const Ticket& ticket);
    void diminuerWagons(int n);                             { wagonsRestants -= n;}

    void verifierTickets(Plateau& plateau);
    bool aGagne() const;

    void afficher() const;
};

#endif

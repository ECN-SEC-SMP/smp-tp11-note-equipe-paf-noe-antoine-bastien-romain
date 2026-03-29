#ifndef TICKET_H
#define TICKET_H

#include "Ville.h"

class Joueur;
class Plateau;

class Ticket {
private:
    Ville villeDepart;
    Ville villeArrivee;
    bool estReussi;

public:
    Ticket();
    Ticket(const Ville& depart, const Ville& arrivee);

    const Ville& getVilleDepart() const;
    const Ville& getVilleArrivee() const;
    bool getEstReussi() const;
    void setEstReussi(bool val);

    bool verifier(Joueur& joueur, Plateau& plateau);
};

#endif

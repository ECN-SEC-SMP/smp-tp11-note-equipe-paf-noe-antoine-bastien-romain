#include "../headers/Ticket.h"
#include "../headers/Joueur.h"
#include "../headers/Plateau.h"
#include <queue>
#include <set>
#include <string>

Ticket::Ticket() : estReussi(false) {}

Ticket::Ticket(const Ville& depart, const Ville& arrivee)
    : villeDepart(depart), villeArrivee(arrivee), estReussi(false) {}

const Ville& Ticket::getVilleDepart() const { return villeDepart; }

const Ville& Ticket::getVilleArrivee() const { 
    return villeArrivee;
}




bool Ticket::getEstReussi() const { return estReussi;}

void Ticket::setEstReussi(bool val) { estReussi = val;}

bool Ticket::verifier(Joueur& joueur, Plateau& plateau) {
    return plateau.existeCheminJoueur(villeDepart, villeArrivee, joueur);
}

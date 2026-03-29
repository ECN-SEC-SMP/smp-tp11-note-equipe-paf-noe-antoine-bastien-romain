#ifndef ROUTE_H
#define ROUTE_H

#include "Ville.h"
#include "Joueur.h"
#include <vector>

class Joueur;

class Route {
private:
    Ville villeA;
    Ville villeB;
    int longueur;
    bool estDouble;
    Joueur* proprietaire;

public:
    Route();
    Route(const Ville& a, const Ville& b, int longueur, bool estDouble = false);

    const Ville& getVilleA() const      { return villeA; }
    const Ville& getVilleB() const      { return villeB; }
    int getLongueur() const             { return longueur; }
    bool getEstDouble() const           { return estDouble; }
    void setEstDouble(bool val)         { estDouble = val; }
    Joueur* getProprietaire() const  { return proprietaire; }

    bool estDisponible() const;
};

#endif

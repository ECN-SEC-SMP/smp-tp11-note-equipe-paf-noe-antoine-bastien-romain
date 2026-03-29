#ifndef ROUTE_H
#define ROUTE_H

#include "Ville.h"
#include "Couleur.h"
#include "CarteTrain.h"
#include <vector>

class Joueur;

class Route {
private:
    Ville villeA;
    Ville villeB;
    int longueur;
    Couleur couleur;
    bool estDouble;
    Joueur* proprietaire;

public:
    Route();
    Route(const Ville& a, const Ville& b, int longueur, Couleur couleur, bool estDouble = false);

    const Ville& getVilleA() const;
    const Ville& getVilleB() const;
    int getLongueur() const;
    Couleur getCouleur() const;
    bool getEstDouble() const;
    void setEstDouble(bool val);
    Joueur* getProprietaire() const;

    bool estDisponible() const;
    bool prendre(Joueur& j, std::vector<CarteTrain>& cartes);
};

#endif

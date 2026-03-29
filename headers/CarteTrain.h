#ifndef CARTETRAIN_H
#define CARTETRAIN_H

#include "Couleur.h"

class CarteTrain {
private:
    Couleur couleur;

public:
    CarteTrain(Couleur couleur);

    Couleur getCouleur() const;
    bool estLocomotive() const;
};

#endif
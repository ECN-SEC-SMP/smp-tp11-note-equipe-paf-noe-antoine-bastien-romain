#include "../headers/CarteTrain.h"

CarteTrain::CarteTrain(Couleur couleur) : couleur(couleur) {}

Couleur CarteTrain::getCouleur() const { return couleur; }

bool CarteTrain::estLocomotive() const {
    return couleur == Couleur::LOCOMOTIVE;
}

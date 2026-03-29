#include "../headers/Ville.h"

Ville::Ville() : nom(""), estCoteOuest(false), estCoteEst(false) {}

Ville::Ville(const std::string& nom, bool estCoteOuest, bool estCoteEst) : nom(nom), estCoteOuest(estCoteOuest), estCoteEst(estCoteEst) {}

const std::string& Ville::getNom() const { return nom; }
bool Ville::getEstCoteOuest() const { return estCoteOuest; }
bool Ville::getEstCoteEst() const { return estCoteEst; }


bool Ville::operator==(const Ville& other) const {
    return nom == other.nom;
}

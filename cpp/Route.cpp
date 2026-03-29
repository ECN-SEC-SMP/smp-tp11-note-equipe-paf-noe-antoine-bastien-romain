#include "../headers/Route.h"
#include "../headers/Joueur.h"

Route::Route() : longueur(0), couleur(Couleur::NOIR), estDouble(false), proprietaire(nullptr) {}

Route::Route(const Ville& a, const Ville& b, int longueur, Couleur couleur, bool estDouble)
    : villeA(a), villeB(b), longueur(longueur), couleur(couleur), estDouble(estDouble), proprietaire(nullptr) {}


const Ville& Route::getVilleA() const { return villeA; }
const Ville& Route::getVilleB() const { return villeB; }
int Route::getLongueur() const { return longueur; }
Couleur Route::getCouleur() const { return couleur; }
bool Route::getEstDouble() const { return estDouble; }
void Route::setEstDouble(bool val) { estDouble = val; }
Joueur* Route::getProprietaire() const { return proprietaire; }


bool Route::estDisponible() const {
    return proprietaire == nullptr;
}

bool Route::prendre(Joueur& j, std::vector<CarteTrain>& cartes) {
    if (!estDisponible()) return false;
    if (j.getWagonsRestants() < longueur) return false;
    if ((int)cartes.size() != longueur) return false;

    // vérifie que les cartes sont bien de la bonne couleur ou des locomotives (jokers)
    int bonnesCouleur = 0;
    int locomotives = 0;
    for (const auto& c : cartes) {
        if (c.estLocomotive()) {
            locomotives++;
        } else if (c.getCouleur() == couleur) {
            bonnesCouleur++;
        } else {
            return false; // carte d'une mauvaise couleur
        }
    }
    if (bonnesCouleur + locomotives < longueur) return false;

    j.utiliserCartes(cartes);
    j.diminuerWagons(longueur);
    proprietaire = &j;
    return true;
}

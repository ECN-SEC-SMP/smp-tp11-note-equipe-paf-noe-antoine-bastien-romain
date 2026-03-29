#include "../headers/Route.h"

Route::Route() : longueur(0), couleur(Couleur::NOIR), estDouble(false), proprietaire(nullptr) {}

Route::Route(const Ville& a, const Ville& b, int longueur, Couleur couleur, bool estDouble)
    : villeA(a), villeB(b), longueur(longueur), couleur(couleur), estDouble(estDouble), proprietaire(nullptr) {}

bool Route::estDisponible() const {
    return proprietaire == nullptr;
}

bool Route::prendre(Joueur& j, std::vector<CarteTrain>& cartes) {
    if (!estDisponible()) return false;
    if (j.getWagonsRestants() < longueur) return false;
    if (static_cast<int>(cartes.size()) != longueur) return false;

    int bonnesCouleur = 0;
    int locomotives = 0;
    for (const auto& c : cartes) {
        if (c.estLocomotive()) {
            locomotives++;
        } else if (c.getCouleur() == couleur) {
            bonnesCouleur++;
        } else {
            return false;
        }
    }
    if (bonnesCouleur + locomotives < longueur) return false;

    j.utiliserCartes(cartes);
    j.diminuerWagons(longueur);
    proprietaire = &j;
    return true;
}

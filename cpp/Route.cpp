#include "../headers/Route.h"

Route::Route() : longueur(0), estDouble(false) {}

Route::Route(const Ville& a, const Ville& b, int longueur, bool estDouble)
   : villeA(a), villeB(b), longueur(longueur),  estDouble(estDouble) {}

bool Route::estDisponible() const {
    //return proprietaire == nullptr;
}


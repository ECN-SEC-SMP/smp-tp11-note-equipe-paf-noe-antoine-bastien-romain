#ifndef COULEUR_H
#define COULEUR_H

#include <string>

enum class Couleur {
    ROUGE, JAUNE, VERT, BLEU, BLANC, NOIR, ORANGE, LOCOMOTIVE
};

std::string couleurToString(Couleur c);
Couleur stringToCouleur(const std::string& s);

#endif

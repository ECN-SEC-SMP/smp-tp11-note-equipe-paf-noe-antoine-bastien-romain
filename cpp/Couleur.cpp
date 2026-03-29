#include "../headers/Couleur.h"

std::string couleurToString(Couleur c) {
    switch (c) {
        case Couleur::ROUGE:      return "Rouge";
        case Couleur::JAUNE:      return "Jaune";
        case Couleur::VERT:       return "Vert";
        case Couleur::BLEU:       return "Bleu";
        case Couleur::BLANC:      return "Blanc";
        case Couleur::NOIR:       return "Noir";
        case Couleur::ORANGE:     return "Orange";
        case Couleur::LOCOMOTIVE: return "Locomotive";
        default:                  return "Inconnu";
    }
}

Couleur stringToCouleur(const std::string& s) {
    if (s == "red"    || s == "rouge")      return Couleur::ROUGE;
    if (s == "yellow" || s == "jaune")      return Couleur::JAUNE;
    if (s == "green"  || s == "vert")       return Couleur::VERT;
    if (s == "blue"   || s == "bleu")       return Couleur::BLEU;
    if (s == "white"  || s == "blanc")      return Couleur::BLANC;
    if (s == "black"  || s == "noir")       return Couleur::NOIR;
    if (s == "orange")                      return Couleur::ORANGE;
    if (s == "locomotive")                  return Couleur::LOCOMOTIVE;
    return Couleur::NOIR;
}

#include "../headers/Plateau.h"
#include "../headers/Joueur.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <queue>
#include <set>
#include <algorithm>

static bool estOuest(const std::string& nom) {
    return nom == "Seattle" || nom == "San Francisco" || nom == "Los Angeles";
}

static bool estEst(const std::string& nom) {
    return nom == "New York" || nom == "Washington" || nom == "Miami" || nom == "Montreal";
}

Plateau::Plateau() {}

const std::vector<Ville>& Plateau::getVilles() const { return villes; }


std::vector<Route>& Plateau::getRoutes() { return routes; }


const std::vector<Route>& Plateau::getRoutes() const { return routes; }

Ville* Plateau::trouverVille(const std::string& nom) {
    for (auto& v : villes) {
        if (v.getNom() == nom) return &v;
    }
    return nullptr;
}

std::vector<Route*> Plateau::getVoisines(const Ville& v) {
    std::vector<Route*> result;
    for (auto& r : routes) {
        if (r.getVilleA().getNom() == v.getNom() || r.getVilleB().getNom() == v.getNom()) {
            result.push_back(&r);
        }
    }
    return result;
}

bool Plateau::routeDisponible(const Route& r) const {
    return r.estDisponible();
}

bool Plateau::existeCheminJoueur(const Ville& depart, const Ville& arrivee, Joueur& joueur) const {

    
    std::set<std::string> visites;
    std::queue<std::string> file;

    file.push(depart.getNom());
    visites.insert(depart.getNom());

    while (!file.empty()) {
        std::string courant = file.front();
        file.pop();

        if (courant == arrivee.getNom()) return true;

        for (const auto& route : routes) {
            if (route.getProprietaire() != &joueur) continue;
            std::string suivant;
            if (route.getVilleA().getNom() == courant) suivant = route.getVilleB().getNom();
            else if (route.getVilleB().getNom() == courant) suivant = route.getVilleA().getNom();
            if (!suivant.empty() && visites.find(suivant) == visites.end()) {
                visites.insert(suivant);
                file.push(suivant);
            }
        }
    }
    return false;
}

void Plateau::chargerCSV(const std::string& fichier) {
    std::ifstream f(fichier);
    if (!f.is_open()) {
        std::cerr << "Impossible d'ouvrir " << fichier << "\n";
        return;
    }

    std::string ligne;
    std::getline(f, ligne); //getlinbe permet de recup une ligne sous la forme d'un str en comptant les espace dcp c'est plutôt pratique

    while (std::getline(f, ligne)) {
        if (ligne.empty()) continue;

        std::istringstream ss(ligne);
        std::string nomA, nomB, couleurStr, longueurStr;

        std::getline(ss, nomA, ',');
        std::getline(ss, nomB, ',');
        std::getline(ss, couleurStr, ',');
        std::getline(ss, longueurStr, ',');

        if (nomA.empty() || nomB.empty()) continue;

        if (!trouverVille(nomA)) {
            villes.emplace_back(nomA, estOuest(nomA), estEst(nomA));
        }
        if (!trouverVille(nomB)) {
            villes.emplace_back(nomB, estOuest(nomB), estEst(nomB));
        }

        Ville* vA = trouverVille(nomA);
        Ville* vB = trouverVille(nomB);
        int longueur = std::stoi(longueurStr);
        Couleur couleur = stringToCouleur(couleurStr);

        routes.emplace_back(*vA, *vB, longueur, couleur);
    }


    for (unsigned int i = 0; i < routes.size(); ++i) {
        for (unsigned int j = i + 1; j < routes.size(); ++j) {
            bool memeAB = routes[i].getVilleA().getNom() == routes[j].getVilleA().getNom() && routes[i].getVilleB().getNom() == routes[j].getVilleB().getNom();

            bool inverseAB = routes[i].getVilleA().getNom() == routes[j].getVilleB().getNom() && routes[i].getVilleB().getNom() == routes[j].getVilleA().getNom();

            if (memeAB || inverseAB) {
                routes[i].setEstDouble(true);
                routes[j].setEstDouble(true);
            }
        }
    }
}


void Plateau::afficher() const {
    std::cout << "=== Plateau ===\n";
    std::cout << "Villes : ";
    for (const auto& v : villes) {
        std::cout << v.getNom();
        if (v.getEstCoteOuest()) {
            std::cout << "(O)";
        }
        if (v.getEstCoteEst()) std::cout << "(E)";
        std::cout << " ";
    }
    std::cout << "\n";

    std::cout << "Routes disponibles :\n";
    
    for (const auto& r : routes) {
        if (r.estDisponible()) {
            std::cout << "  " << r.getVilleA().getNom() << " - " << r.getVilleB().getNom() << " [" << couleurToString(r.getCouleur()) << ", " << r.getLongueur() << "]";
            if (r.getEstDouble()) std::cout << " (double)";
            std::cout << "\n";
        }
    }
}

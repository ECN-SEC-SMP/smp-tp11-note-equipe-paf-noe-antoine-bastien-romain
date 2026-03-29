#ifndef PLATEAU_H
#define PLATEAU_H

#include <vector>
#include <string>
#include "Ville.h"
#include "Route.h"

class Joueur;

class Plateau {
private:
    std::vector<Ville> villes;
    std::vector<Route> routes;

public:
    Plateau();

    const std::vector<Ville>& getVilles() const;
    
    std::vector<Route>& getRoutes();
    const std::vector<Route>& getRoutes() const;

    Ville* trouverVille(const std::string& nom);
    std::vector<Route*> getVoisines(const Ville& v);
    bool routeDisponible(const Route& r) const;

    /// BFS sur les routes possédées par joueur pour vérifier la connexité entre depart et arrivee
    bool existeCheminJoueur(const Ville& depart, const Ville& arrivee, Joueur& joueur) const;

    void chargerCSV(const std::string& fichier);
    void afficher() const;
};

#endif

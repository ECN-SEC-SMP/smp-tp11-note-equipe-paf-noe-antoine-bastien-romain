#ifndef PIOCHE_H
#define PIOCHE_H

#include <vector>
#include <algorithm>
#include <random>
#include <stdexcept>


// class template donc les methodes doivent être écrites dans le cpp pour la compilation
template<typename T>
class Pioche {
private:
    std::vector<T> cartes;
    std::vector<T> defausse;

public:
    Pioche() {}

    void ajouter(const T& carte) {
        cartes.push_back(carte);
    }

    T piocher() {
        if (estVide()) recyclerDefausse();
        if (estVide()) throw std::runtime_error("Pioche vide");
        T carte = cartes.back();
        cartes.pop_back();
        return carte;
    }

    void melanger() {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(cartes.begin(), cartes.end(), g);
    }

    bool estVide() const {
        return cartes.empty();
    }

    bool defausseVide() const {
        return defausse.empty();
    }

    void recyclerDefausse() {
        cartes.insert(cartes.end(), defausse.begin(), defausse.end());
        defausse.clear();
        melanger();
    }

    void ajouterDefausse(const T& carte) {
        defausse.push_back(carte);
    }

    int taille() const {
        return static_cast<int>(cartes.size());
    }
};

#endif

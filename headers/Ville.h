#ifndef VILLE_H
#define VILLE_H

#include <string>

class Ville {
private:
    std::string nom;
    bool estCoteOuest;
    bool estCoteEst;

public:
    Ville();
    Ville(const std::string& nom, bool estCoteOuest = false, bool estCoteEst = false);

    const std::string& getNom() const;
    bool getEstCoteOuest() const;
    bool getEstCoteEst() const;

    bool operator==(const Ville& other) const;
};

#endif

#include "../headers/Jeu.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

static int lireEntier(int min, int max) {
    int val;
    while (true) {
        if (std::cin >> val) {
            std::cin.ignore(1000, '\n');
            if (val >= min && val <= max) return val;
        } else {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
        std::cout << "Entree invalide, entrez un nombre entre " << min << " et " << max << " : ";
    }
}

static Couleur couleurJoueur(int i) {
    Couleur cols[] = {Couleur::ROUGE, Couleur::JAUNE, Couleur::VERT, Couleur::BLEU};
    return cols[i % 4];
}

Jeu::Jeu() : joueurCourant(0), grandeTraverseeAttribuee(false) {}

void Jeu::chargerDonnees(const std::string& fichierMap, const std::string& fichierTickets) {
    plateau.chargerCSV(fichierMap);
    chargerTicketsCSV(fichierTickets);
}

void Jeu::chargerTicketsCSV(const std::string& fichier) {
    std::ifstream f(fichier);
    if (!f.is_open()) {
        std::cerr << "Impossible d'ouvrir " << fichier << "\n";
        return;
    }

    std::string ligne;
    std::getline(f, ligne); // ignore l'en-tête CSV

    while (std::getline(f, ligne)) {
        if (ligne.empty()) continue;
        std::istringstream ss(ligne);
        std::string id, nomA, nomB;
        std::getline(ss, id, ',');
        std::getline(ss, nomA, ',');
        std::getline(ss, nomB, ',');
        if (nomA.empty() || nomB.empty()) continue;

        Ville* vA = plateau.trouverVille(nomA);
        Ville* vB = plateau.trouverVille(nomB);
        if (!vA) {
            plateau.getRoutes(); // force le chargement des villes si elles n'ont pas encore été créées
            vA = plateau.trouverVille(nomA);
        }
        if (vA && vB) {
            piocheTickets.ajouter(Ticket(*vA, *vB));
        }
    }
    piocheTickets.melanger();
}

void Jeu::initialiser(int nbJoueurs) {
    joueurs.reserve(4);
    for (int i = 0; i < nbJoueurs; ++i) {
        std::cout << "Nom du joueur " << (i + 1) << " : ";
        std::string nom;
        std::cin >> nom;
        joueurs.emplace_back(nom, couleurJoueur(i));
    }

    Couleur couleurs[] = {Couleur::ROUGE, Couleur::JAUNE, Couleur::VERT, Couleur::BLEU,
                          Couleur::BLANC, Couleur::NOIR, Couleur::ORANGE};
    // 10 cartes par couleur + 12 locomotives (joker)
    for (Couleur c : couleurs) {
        for (int i = 0; i < 10; ++i) piocheCartes.ajouter(CarteTrain(c));
    }
    for (int i = 0; i < 12; ++i) piocheCartes.ajouter(CarteTrain(Couleur::LOCOMOTIVE));
    piocheCartes.melanger();

    // distribution initiale : 2 cartes train + 2 tickets de destination par joueur
    // auto& : évite de répéter le type Joueur, qui pourrait changer sans casser la boucle
    for (auto& j : joueurs) {
        j.piocher(piocheCartes);
        j.piocher(piocheCartes);
        j.ajouterTicket(piocheTickets.piocher());
        j.ajouterTicket(piocheTickets.piocher());
    }

    joueurCourant = 0;
}

void Jeu::afficherEtat() const {
    std::cout << "\n========================================\n";
    for (const auto& j : joueurs) {
        j.afficher();
    }
    std::cout << "========================================\n";
}

void Jeu::actionPiocher() {
    Joueur& j = joueurs[joueurCourant];
    j.piocher(piocheCartes);
    std::cout << j.getNom() << " a pioche 2 cartes.\n";
}

void Jeu::actionPoserWagons() {
    Joueur& j = joueurs[joueurCourant];

    std::vector<Route*> disponibles;
    for (auto& r : plateau.getRoutes()) {
        if (!r.estDisponible()) continue;
        if (r.getEstDouble()) {
            // règle : un joueur ne peut pas prendre les deux voies parallèles entre les mêmes villes
            bool dejaParallele = false;
            for (const auto& r2 : plateau.getRoutes()) {
                if (&r2 == &r) continue;
                bool memeAB = r2.getVilleA().getNom() == r.getVilleA().getNom() &&
                              r2.getVilleB().getNom() == r.getVilleB().getNom();
                bool inverseAB = r2.getVilleA().getNom() == r.getVilleB().getNom() &&
                                 r2.getVilleB().getNom() == r.getVilleA().getNom();
                if ((memeAB || inverseAB) && r2.getProprietaire() == &j) {
                    dejaParallele = true;
                    break;
                }
            }
            if (dejaParallele) continue;
        }
        // auto : le type exact retourné par selectionnerCartes (vector<CarteTrain>) n'a pas à être répété ici
        auto cartes = j.selectionnerCartes(r.getCouleur(), r.getLongueur());
        if (!cartes.empty()) {
            disponibles.push_back(&r);
        }
    }

    if (disponibles.empty()) {
        std::cout << "Aucune route accessible avec votre main actuelle.\n";
        return;
    }

    std::cout << "Routes disponibles :\n";
    for (size_t i = 0; i < disponibles.size(); ++i) {
        const Route* r = disponibles[i];
        std::cout << "  " << (i + 1) << ") " << r->getVilleA().getNom()
                  << " - " << r->getVilleB().getNom()
                  << " [" << couleurToString(r->getCouleur()) << ", " << r->getLongueur() << " wagons]\n";
    }
    std::cout << "  0) Annuler\n";
    std::cout << "Choix : ";

    int nbDispo = disponibles.size();
    int choix = lireEntier(0, nbDispo);
    if (choix == 0) return;

    Route* r = disponibles[choix - 1];
    auto cartes = j.selectionnerCartes(r->getCouleur(), r->getLongueur());
    if (j.poserWagons(*r, cartes)) {
        std::cout << j.getNom() << " a pris la route "
                  << r->getVilleA().getNom() << " - " << r->getVilleB().getNom() << " !\n";
        j.verifierTickets(plateau);
        verifierGrandeTraversee(j);
    } else {
        std::cout << "Impossible de prendre cette route.\n";
    }
}

void Jeu::actionEchangerTickets() {
    Joueur& j = joueurs[joueurCourant];
    if (piocheTickets.estVide() && piocheTickets.defausseVide()) {
        std::cout << "Plus de tickets disponibles.\n";
        return;
    }
    // remet les tickets actuel dans la défausse avant d'en piocher de nouveaux
    for (const auto& t : j.getTickets()) {
        piocheTickets.ajouterDefausse(t);
    }
    j.echangerTickets(piocheTickets);
    std::cout << j.getNom() << " a echange ses tickets.\n";
}

void Jeu::verifierGrandeTraversee(Joueur& joueur) {
    if (grandeTraverseeAttribuee) return;
    // teste toutes les paires (ville ouest, ville est) ; dès qu'un chemin existe, le bonus est attribuée
    for (const auto& v : plateau.getVilles()) {
        if (!v.getEstCoteOuest()) continue;
        for (const auto& v2 : plateau.getVilles()) {
            if (!v2.getEstCoteEst()) continue;
            if (plateau.existeCheminJoueur(v, v2, joueur)) {
                joueur.setAGrandeTraversee(true);
                joueur.incrementerTicketsReussis();
                grandeTraverseeAttribuee = true;
                std::cout << "*** " << joueur.getNom() << " remporte la Grande Traversee ! ***\n";
                return;
            }
        }
    }
}

void Jeu::jouerTour() {
    Joueur& j = joueurs[joueurCourant];
    std::cout << "\n--- Tour de " << j.getNom()
              << " (" << couleurToString(j.getCouleur()) << ") ---\n";
    std::cout << "  Wagons : " << j.getWagonsRestants()
              << " | Tickets reussis : " << j.getTicketsReussis() << "\n";

    std::cout << "Action :\n";
    std::cout << "  1) Piocher 2 cartes Train\n";
    std::cout << "  2) Poser des wagons sur une route\n";
    std::cout << "  3) Echanger ses tickets\n";
    std::cout << "Choix : ";

    int choix = lireEntier(1, 3);

    switch (choix) {
        case 1: actionPiocher(); break;
        case 2: actionPoserWagons(); break;
        case 3: actionEchangerTickets(); break;
        default: break;
    }

    int nbJoueurs = joueurs.size();
    joueurCourant = (joueurCourant + 1) % nbJoueurs; // passage au joueur suivant en boucle
}

bool Jeu::verifierFinPartie() const {
    for (const auto& j : joueurs) {
        if (j.aGagne()) {
            std::cout << "\n*** " << j.getNom() << " a gagne avec "
                      << j.getTicketsReussis() << " tickets reussis ! ***\n";
            return true;
        }
        if (j.getWagonsRestants() == 0) {
            // fin de partie déclenchée quand un joueur épuise tous ses wagons
            std::cout << "\n*** " << j.getNom() << " a pose son dernier wagon ! ***\n";
            return true;
        }
    }
    return false;
}

void Jeu::lancerPartie() {
    std::cout << "\n=== Les Aventuriers du Rail - Mon Premier Voyage ===\n";
    afficherEtat();

    while (!verifierFinPartie()) {
        jouerTour();
    }

    std::cout << "\n=== Fin de partie ===\n";
    for (const auto& j : joueurs) {
        std::cout << j.getNom() << " : " << j.getTicketsReussis() << " ticket(s) reussi(s)";
        if (j.getAGrandeTraversee()) std::cout << " + Grande Traversee";
        std::cout << "\n";
    }
}

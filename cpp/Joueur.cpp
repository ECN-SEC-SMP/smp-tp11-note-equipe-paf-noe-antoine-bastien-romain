#include "../headers/Joueur.h"
#include "../headers/Route.h"
#include "../headers/Plateau.h"
#include <iostream>
#include <algorithm>

Joueur::Joueur() : nom(""), couleur(Couleur::ROUGE), wagonsRestants(20), ticketsReussis(0), aGrandeTraversee(false) {}

Joueur::Joueur(const std::string& nom, Couleur couleur)
    : nom(nom), couleur(couleur), wagonsRestants(20), ticketsReussis(0), aGrandeTraversee(false) {}

const std::string& Joueur::getNom() const { return nom; }
Couleur Joueur::getCouleur() const { return couleur; }
int Joueur::getWagonsRestants() const { return wagonsRestants; }
const std::vector<CarteTrain>& Joueur::getMainCartes() const { return mainCartes; }
std::vector<Ticket>& Joueur::getTickets() { return tickets; }
int Joueur::getTicketsReussis() const { return ticketsReussis; }
bool Joueur::getAGrandeTraversee() const { return aGrandeTraversee; }

void Joueur::setAGrandeTraversee(bool val) { aGrandeTraversee = val; }

void Joueur::incrementerTicketsReussis() { ticketsReussis++; }

void Joueur::ajouterCarte(const CarteTrain& carte) {
    mainCartes.push_back(carte);
}

void Joueur::ajouterTicket(const Ticket& ticket) {
    tickets.push_back(ticket);
}

void Joueur::utiliserCartes(const std::vector<CarteTrain>& cartes) {
    for (const auto& c : cartes) {
        for (auto it = mainCartes.begin(); it != mainCartes.end(); ++it) {
            if (it->getCouleur() == c.getCouleur()) {
                mainCartes.erase(it);
                break;
            }
        }
    }
}

void Joueur::diminuerWagons(int n) {
    wagonsRestants -= n;
}

std::vector<CarteTrain> Joueur::selectionnerCartes(Couleur couleur, int longueur) const {
    std::vector<CarteTrain> selection;
    std::vector<CarteTrain> locomotives;
    int nbSelectionnes = 0;

    // premier passage : on prend les cartes de la bonne couleur, les locos sont mises de côté
    for (const auto& c : mainCartes) {
        if (c.estLocomotive()) {
            locomotives.push_back(c);
        } else if (c.getCouleur() == couleur && nbSelectionnes < longueur) {
            selection.push_back(c);
            nbSelectionnes++;
        }
    }

    // second passage : on complète avec des locomotives si on n'a pas assez de cartes colorées
    int manquantes = longueur - nbSelectionnes;
    for (const auto& loco : locomotives) {
        if (manquantes <= 0) break;
        selection.push_back(loco);
        manquantes--;
        nbSelectionnes++;
    }

    if (nbSelectionnes < longueur) {
        return {};
    }
    return selection;
}

void Joueur::piocher(Pioche<CarteTrain>& pioche) {
    for (int i = 0; i < 2; ++i) {
        if (!pioche.estVide()) {
            ajouterCarte(pioche.piocher());
        }
    }
}

bool Joueur::poserWagons(Route& r, std::vector<CarteTrain>& cartes) {
    return r.prendre(*this, cartes);
}

void Joueur::echangerTickets(Pioche<Ticket>& pioche) {
    tickets.clear();
    for (int i = 0; i < 2; ++i) {
        if (!pioche.estVide()) {
            tickets.push_back(pioche.piocher());
        }
    }
}

void Joueur::verifierTickets(Plateau& plateau) {
    for (auto& ticket : tickets) {
        if (!ticket.getEstReussi() && ticket.verifier(*this, plateau)) {
            ticket.setEstReussi(true);
            ticketsReussis++;
            std::cout << nom << " a reussi le ticket " << ticket.getVilleDepart().getNom()
                      << " -> " << ticket.getVilleArrivee().getNom() << " ! Ticket !\n";
        }
    }
    if (aGrandeTraversee) {
        // recalcule depuis zéro pour éviter les doublons si verifierTickets est appelé plusieurs fois
        ticketsReussis = 0;
        for (const auto& t : tickets) {
            if (t.getEstReussi()) ticketsReussis++;
        }
        ticketsReussis++; // +1 pour la grande traversée elle-même
    }
}

bool Joueur::aGagne() const {
    int total = ticketsReussis;
    if (aGrandeTraversee) total++;
    return total >= 6;
}

void Joueur::afficher() const {
    std::cout << "Joueur : " << nom << " (" << couleurToString(couleur) << ")\n";
    std::cout << "  Wagons restants : " << wagonsRestants << "\n";
    std::cout << "  Tickets reussis : " << ticketsReussis;
    if (aGrandeTraversee) std::cout << " + Grande Traversee";
    std::cout << "\n";

    std::cout << "  Main (" << mainCartes.size() << " cartes) : ";
    Couleur all[] = {Couleur::ROUGE, Couleur::JAUNE, Couleur::VERT, Couleur::BLEU,
                     Couleur::BLANC, Couleur::NOIR, Couleur::ORANGE, Couleur::LOCOMOTIVE};
    for (auto col : all) {
        int count = 0;
        for (const auto& c : mainCartes) {
            if (c.getCouleur() == col) count++;
        }
        if (count > 0) {
            std::cout << couleurToString(col) << "x" << count << " ";
        }
    }
    std::cout << "\n";

    std::cout << "  Tickets :\n";
    for (const auto& t : tickets) {
        std::cout << "    " << t.getVilleDepart().getNom() << " -> " << t.getVilleArrivee().getNom()
                  << (t.getEstReussi() ? " [REUSSI]" : "") << "\n";
    }
}

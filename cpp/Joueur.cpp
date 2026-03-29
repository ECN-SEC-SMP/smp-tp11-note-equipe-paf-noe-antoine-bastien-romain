#include "../headers/Joueur.h"
#include <iostream>
#include <algorithm>

Joueur::Joueur() : nom(""), couleur(Couleur::ROUGE), wagonsRestants(20), ticketsReussis(0), aGrandeTraversee(false) {}

Joueur::Joueur(const std::string& nom, Couleur couleur)
    : nom(nom), couleur(couleur), wagonsRestants(20), ticketsReussis(0), aGrandeTraversee(false) {}


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

std::vector<CarteTrain> Joueur::selectionnerCartes(Couleur couleur, int longueur) const {
    std::vector<CarteTrain> selection;
    std::vector<CarteTrain> locomotives;

    for (const auto& c : mainCartes) {
        if (c.estLocomotive()) {
            locomotives.push_back(c);
        } else if (c.getCouleur() == couleur && static_cast<int>(selection.size()) < longueur) {
            selection.push_back(c);
        }
    }

    int manquantes = longueur - static_cast<int>(selection.size());
    for (int i = 0; i < manquantes && i < static_cast<int>(locomotives.size()); ++i) {
        selection.push_back(locomotives[i]);
    }

    if (static_cast<int>(selection.size()) < longueur) {
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
        ticketsReussis = 0;
        for (const auto& t : tickets) {
            if (t.getEstReussi()) ticketsReussis++;
        }
        ticketsReussis++;
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
    int counts[8] = {0};
    for (const auto& c : mainCartes) {
        counts[static_cast<int>(c.getCouleur())]++;
    }
    Couleur all[] = {Couleur::ROUGE, Couleur::JAUNE, Couleur::VERT, Couleur::BLEU,
                     Couleur::BLANC, Couleur::NOIR, Couleur::ORANGE, Couleur::LOCOMOTIVE};
    for (auto col : all) {
        int idx = static_cast<int>(col);
        if (counts[idx] > 0) {
            std::cout << couleurToString(col) << "x" << counts[idx] << " ";
        }
    }
    std::cout << "\n";

    std::cout << "  Tickets :\n";
    for (const auto& t : tickets) {
        std::cout << "    " << t.getVilleDepart().getNom() << " -> " << t.getVilleArrivee().getNom()
                  << (t.getEstReussi() ? " [REUSSI]" : "") << "\n";
    }
}
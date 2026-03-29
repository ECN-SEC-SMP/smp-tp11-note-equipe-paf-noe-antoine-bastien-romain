#include "../headers/Joueur.h"
#include <iostream>
#include <algorithm>

Joueur::Joueur() : nom(""), wagonsRestants(20), ticketsReussis(0), aGrandeTraversee(false) {}

Joueur::Joueur(const std::string& nom)
    : nom(nom), wagonsRestants(20), ticketsReussis(0), aGrandeTraversee(false) {}

void Joueur::ajouterTicket(const Ticket& ticket) {
    tickets.push_back(ticket);
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
    std::cout << "  Tickets :\n";
    for (const auto& t : tickets) {
        std::cout << "    " << t.getVilleDepart().getNom() << " -> " << t.getVilleArrivee().getNom()
                  << (t.getEstReussi() ? " [REUSSI]" : "") << "\n";
    }
}

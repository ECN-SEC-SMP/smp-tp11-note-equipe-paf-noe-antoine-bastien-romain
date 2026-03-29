#include <gtest/gtest.h>
#include "../headers/Couleur.h"
#include "../headers/CarteTrain.h"
#include "../headers/Pioche.h"
#include "../headers/Ville.h"
#include "../headers/Route.h"
#include "../headers/Joueur.h"
#include "../headers/Ticket.h"
#include "../headers/Plateau.h"

// ─── Couleur ───────────────────────────────────────────────────────────────

TEST(Couleur, CouleurToString) {
    EXPECT_EQ(couleurToString(Couleur::ROUGE), "Rouge");
    EXPECT_EQ(couleurToString(Couleur::LOCOMOTIVE), "Locomotive");
}

TEST(Couleur, StringToCouleur) {
    EXPECT_EQ(stringToCouleur("red"),   Couleur::ROUGE);
    EXPECT_EQ(stringToCouleur("rouge"), Couleur::ROUGE);
    EXPECT_EQ(stringToCouleur("blue"),  Couleur::BLEU);
}

// ─── CarteTrain ────────────────────────────────────────────────────────────

TEST(CarteTrain, GetCouleur) {
    CarteTrain c(Couleur::VERT);
    EXPECT_EQ(c.getCouleur(), Couleur::VERT);
}

TEST(CarteTrain, EstLocomotive) {
    CarteTrain loco(Couleur::LOCOMOTIVE);
    CarteTrain normale(Couleur::BLEU);
    EXPECT_TRUE(loco.estLocomotive());
    EXPECT_FALSE(normale.estLocomotive());
}

// ─── Pioche ────────────────────────────────────────────────────────────────

TEST(Pioche, AjouterEtTaille) {
    Pioche<CarteTrain> p;
    p.ajouter(CarteTrain(Couleur::ROUGE));
    p.ajouter(CarteTrain(Couleur::BLEU));
    EXPECT_EQ(p.taille(), 2);
}

TEST(Pioche, EstVideSiVide) {
    Pioche<CarteTrain> p;
    EXPECT_TRUE(p.estVide());
    p.ajouter(CarteTrain(Couleur::NOIR));
    EXPECT_FALSE(p.estVide());
}

TEST(Pioche, PiocherReduitTaille) {
    Pioche<CarteTrain> p;
    p.ajouter(CarteTrain(Couleur::ROUGE));
    p.ajouter(CarteTrain(Couleur::BLEU));
    p.piocher();
    EXPECT_EQ(p.taille(), 1);
}

TEST(Pioche, RecyclerDefausse) {
    Pioche<CarteTrain> p;
    p.ajouterDefausse(CarteTrain(Couleur::ROUGE));
    p.ajouterDefausse(CarteTrain(Couleur::BLEU));
    EXPECT_TRUE(p.estVide());
    p.recyclerDefausse();
    EXPECT_EQ(p.taille(), 2);
    EXPECT_TRUE(p.defausseVide());
}

TEST(Pioche, PiocherVideLanceException) {
    Pioche<CarteTrain> p;
    EXPECT_THROW(p.piocher(), std::runtime_error);
}

// ─── Ville ─────────────────────────────────────────────────────────────────

TEST(Ville, NomEtCotes) {
    Ville v("Paris", true, false);
    EXPECT_EQ(v.getNom(), "Paris");
    EXPECT_TRUE(v.getEstCoteOuest());
    EXPECT_FALSE(v.getEstCoteEst());
}

TEST(Ville, Egalite) {
    Ville a("Lyon");
    Ville b("Lyon");
    Ville c("Marseille");
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
}

// ─── Route ─────────────────────────────────────────────────────────────────

TEST(Route, EstDisponibleParDefaut) {
    Ville a("Paris");
    Ville b("Lyon");
    Route r(a, b, 3, Couleur::ROUGE);
    EXPECT_TRUE(r.estDisponible());
}

TEST(Route, PrendreAvecBonnesCartes) {
    Ville a("Paris");
    Ville b("Lyon");
    Route r(a, b, 2, Couleur::ROUGE);

    Joueur j("Alice", Couleur::ROUGE);
    for (int i = 0; i < 2; i++) j.ajouterCarte(CarteTrain(Couleur::ROUGE));

    std::vector<CarteTrain> cartes = j.selectionnerCartes(Couleur::ROUGE, 2);
    ASSERT_EQ((int)cartes.size(), 2);
    EXPECT_TRUE(r.prendre(j, cartes));
    EXPECT_FALSE(r.estDisponible());
}

TEST(Route, PrendreEchoueSiPasDeCarte) {
    Ville a("Paris");
    Ville b("Lyon");
    Route r(a, b, 3, Couleur::BLEU);

    Joueur j("Bob", Couleur::BLEU);
    std::vector<CarteTrain> cartes;
    EXPECT_FALSE(r.prendre(j, cartes));
}

// ─── Joueur ────────────────────────────────────────────────────────────────

TEST(Joueur, SelectionnerCartesExactes) {
    Joueur j("Alice", Couleur::ROUGE);
    j.ajouterCarte(CarteTrain(Couleur::BLEU));
    j.ajouterCarte(CarteTrain(Couleur::BLEU));
    j.ajouterCarte(CarteTrain(Couleur::ROUGE));

    auto cartes = j.selectionnerCartes(Couleur::BLEU, 2);
    EXPECT_EQ((int)cartes.size(), 2);
}

TEST(Joueur, SelectionnerCartesInsuffisantes) {
    Joueur j("Alice", Couleur::ROUGE);
    j.ajouterCarte(CarteTrain(Couleur::BLEU));

    auto cartes = j.selectionnerCartes(Couleur::BLEU, 3);
    EXPECT_TRUE(cartes.empty());
}

TEST(Joueur, SelectionnerCartesAvecLocomotives) {
    Joueur j("Alice", Couleur::ROUGE);
    j.ajouterCarte(CarteTrain(Couleur::VERT));
    j.ajouterCarte(CarteTrain(Couleur::LOCOMOTIVE));
    j.ajouterCarte(CarteTrain(Couleur::LOCOMOTIVE));

    auto cartes = j.selectionnerCartes(Couleur::VERT, 3);
    EXPECT_EQ((int)cartes.size(), 3);
}

TEST(Joueur, AGagneApres6Tickets) {
    Joueur j("Alice", Couleur::ROUGE);
    for (int i = 0; i < 6; i++) j.incrementerTicketsReussis();
    EXPECT_TRUE(j.aGagne());
}

TEST(Joueur, PasGagneAvant6Tickets) {
    Joueur j("Alice", Couleur::ROUGE);
    for (int i = 0; i < 5; i++) j.incrementerTicketsReussis();
    EXPECT_FALSE(j.aGagne());
}

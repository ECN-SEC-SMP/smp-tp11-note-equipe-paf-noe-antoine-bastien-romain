# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build & Run

```bash
# Configure (from repo root)
cmake -B build

# Build
cmake --build build

# Run (must be run from build/ so CSV paths resolve correctly)
cd build && ./aventuriers
```

The executable expects `src/map.csv` and `src/ticket.csv` relative to its working directory (CMake copies them into `build/src/` automatically).

## Architecture

This is a C++17 implementation of the board game "Les Aventuriers du Rail" (Ticket to Ride). The project uses CMake and has no external dependencies.

**Class hierarchy and responsibilities:**

- `Jeu` — top-level game controller. Owns the `Plateau`, a list of `Joueur`s, and two `Pioche<T>` decks. Drives the turn loop (`jouerTour`, `lancerPartie`) and handles game-end detection.
- `Plateau` — the board: holds all `Ville`s and `Route`s loaded from `src/map.csv`. Provides graph traversal (`existeCheminJoueur` via BFS/DFS) used to validate tickets.
- `Joueur` — a player: holds a hand of `CarteTrain`s, a list of `Ticket`s, and a wagon count. Implements the three main actions: `piocher`, `poserWagons`, `echangerTickets`.
- `Route` — an edge between two `Ville`s with a length, a `Couleur`, and an optional owner pointer. `prendre()` claims the route for a player.
- `Ticket` — a destination card (depart → arrivee). `verifier()` delegates to `Plateau::existeCheminJoueur`.
- `CarteTrain` — a train card with a `Couleur`. `LOCOMOTIVE` acts as a wild.
- `Pioche<T>` — generic template deck supporting draw, discard pile, and automatic reshuffle.
- `Couleur` — `enum class` with helpers `couleurToString` / `stringToCouleur`.

**Data files (`src/`):**
- `map.csv` — route definitions loaded by `Plateau::chargerCSV`
- `ticket.csv` — destination tickets loaded by `Jeu::chargerTicketsCSV`

**Headers are in `headers/`, implementations in `cpp/`, entry point is `main.cpp`.**

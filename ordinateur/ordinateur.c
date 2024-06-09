#include <stdio.h>
#include <stdbool.h>
#include "ordinateur.h"

#define LIGNES 6
#define COLONNES 7

#define JOUEUR 1
#define BOT 2


bool estPleine(int grilleJeu[LIGNES][COLONNES], int col) {
    return grilleJeu[0][col] != 0;
}

void jouerBot(int grilleJeu[LIGNES][COLONNES], int col) {
    int ligne = LIGNES - 1;
    while (ligne >= 0 && grilleJeu[ligne][col] != 0) {
        ligne--;
    }
    if (ligne >= 0) {
        grilleJeu[ligne][col] = BOT;
    }
}

void enleverBot(int grilleJeu[LIGNES][COLONNES], int col) {
    int ligne = 0;
    while (ligne < LIGNES && grilleJeu[ligne][col] == 0) {
        ligne++;
    }
    if (ligne < LIGNES) {
        grilleJeu[ligne][col] = 0;
    }
}

void jouerJoueur(int grilleJeu[LIGNES][COLONNES], int col) {
    int ligne = LIGNES - 1;
    while (ligne >= 0 && grilleJeu[ligne][col] != 0) {
        ligne--;
    }
    if (ligne >= 0) {
        grilleJeu[ligne][col] = JOUEUR;
    }
}

void enleverJoueur(int grilleJeu[LIGNES][COLONNES], int col) {
    int ligne = 0;
    while (ligne < LIGNES && grilleJeu[ligne][col] == 0) {
        ligne++;
    }
    if (ligne < LIGNES) {
        grilleJeu[ligne][col] = 0;
    }
}

bool verifierLigne(int a, int b, int c, int d) {
    return (a == b && a == c && a == d && a != 0);
}

bool jeuTermine(int grilleJeu[LIGNES][COLONNES]) {
    for (int ligne = 0; ligne < LIGNES; ligne++) {
        for (int col = 0; col < COLONNES - 3; col++) {
            if (verifierLigne(grilleJeu[ligne][col], grilleJeu[ligne][col + 1], grilleJeu[ligne][col + 2], grilleJeu[ligne][col + 3])) {
                return true;
            }
        }
    }

    for (int ligne = 0; ligne < LIGNES - 3; ligne++) {
        for (int col = 0; col < COLONNES; col++) {
            if (verifierLigne(grilleJeu[ligne][col], grilleJeu[ligne + 1][col], grilleJeu[ligne + 2][col], grilleJeu[ligne + 3][col])) {
                return true;
            }
        }
    }

    for (int ligne = 0; ligne < LIGNES - 3; ligne++) {
        for (int col = 0; col < COLONNES - 3; col++) {
            if (verifierLigne(grilleJeu[ligne][col], grilleJeu[ligne + 1][col + 1], grilleJeu[ligne + 2][col + 2], grilleJeu[ligne + 3][col + 3])) {
                return true;
            }
        }
    }

    for (int ligne = 3; ligne < LIGNES; ligne++) {
        for (int col = 0; col < COLONNES - 3; col++) {
            if (verifierLigne(grilleJeu[ligne][col], grilleJeu[ligne - 1][col + 1], grilleJeu[ligne - 2][col + 2], grilleJeu[ligne - 3][col + 3])) {
                return true;
            }
        }
    }

    for (int col = 0; col < COLONNES; col++) {
        if (!estPleine(grilleJeu, col)) {
            return false;
        }
    }

    return true;
}

int evaluerPosition(int a, int b, int c, int d) {
    int score = 0;
    int botCount = (a == BOT) + (b == BOT) + (c == BOT) + (d == BOT);
    int joueurCount = (a == JOUEUR) + (b == JOUEUR) + (c == JOUEUR) + (d == JOUEUR);

    if (botCount == 4) {
        score += 100;
    } else if (botCount == 3 && joueurCount == 0) {
        score += 5;
    } else if (botCount == 2 && joueurCount == 0) {
        score += 2;
    }

    if (joueurCount == 4) {
        score -= 100;
    } else if (joueurCount == 3 && botCount == 0) {
        score -= 5;
    } else if (joueurCount == 2 && botCount == 0) {
        score -= 2;
    }

    return score;
}

int evaluerScore(int grilleJeu[LIGNES][COLONNES]) {
    int score = 0;

    for (int ligne = 0; ligne < LIGNES; ligne++) {
        for (int col = 0; col < COLONNES - 3; col++) {
            score += evaluerPosition(grilleJeu[ligne][col], grilleJeu[ligne][col + 1], grilleJeu[ligne][col + 2], grilleJeu[ligne][col + 3]);
        }
    }

    for (int ligne = 0; ligne < LIGNES - 3; ligne++) {
        for (int col = 0; col < COLONNES; col++) {
            score += evaluerPosition(grilleJeu[ligne][col], grilleJeu[ligne + 1][col], grilleJeu[ligne + 2][col], grilleJeu[ligne + 3][col]);
        }
    }

    for (int ligne = 0; ligne < LIGNES - 3; ligne++) {
        for (int col = 0; col < COLONNES - 3; col++) {
            score += evaluerPosition(grilleJeu[ligne][col], grilleJeu[ligne + 1][col + 1], grilleJeu[ligne + 2][col + 2], grilleJeu[ligne + 3][col + 3]);
        }
    }

    for (int ligne = 3; ligne < LIGNES; ligne++) {
        for (int col = 0; col < COLONNES - 3; col++) {
            score += evaluerPosition(grilleJeu[ligne][col], grilleJeu[ligne - 1][col + 1], grilleJeu[ligne - 2][col + 2], grilleJeu[ligne - 3][col + 3]);
        }
    }

    return score;
}

int minimax(int grilleJeu[LIGNES][COLONNES], int profondeur, bool estMaximisant) {
    if (profondeur == 0 || jeuTermine(grilleJeu)) {
        return evaluerScore(grilleJeu);
    }

    if (estMaximisant) {
        int meilleurScore = -9999;

        for (int col = 0; col < COLONNES; col++) {
            if (estPleine(grilleJeu, col)) {
                continue;
            }

            jouerBot(grilleJeu, col);
            int score = minimax(grilleJeu, profondeur - 1, false);
            enleverBot(grilleJeu, col);

            if (score > meilleurScore) {
                meilleurScore = score;
            }
        }

        return meilleurScore;
    } else {
        int meilleurScore = 9999;

        for (int col = 0; col < COLONNES; col++) {
            if (estPleine(grilleJeu, col)) {
                continue;
            }

            jouerJoueur(grilleJeu, col);
            int score = minimax(grilleJeu, profondeur - 1, true);
            enleverJoueur(grilleJeu, col);

            if (score < meilleurScore) {
                meilleurScore = score;
            }
        }

        return meilleurScore;
    }
}

int meilleurCoup(int grilleJeu[LIGNES][COLONNES], int profondeur) {
    int meilleurCoup = -1;
    int meilleurScore = -9999;

    for (int col = 0; col < COLONNES; col++) {
        if (estPleine(grilleJeu, col)) {
            continue;
        }

        jouerBot(grilleJeu, col);
        int score = minimax(grilleJeu, profondeur, false);
        enleverBot(grilleJeu, col);

        if (score > meilleurScore) {
            meilleurScore = score;
            meilleurCoup = col;
        }
    }

    return meilleurCoup;
}

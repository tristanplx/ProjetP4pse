#include <stdio.h>
#include <stdbool.h>
#include "../ordinateur/ordinateur.h" 
#include "jeu.h"

#define ROWS 6
#define COLS 7

void afficherGrille(char grille[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("|%c", grille[i][j]);
        }
        printf("|\n");
    }
    // Afficher les numéros de colonnes
    for (int j = 0; j < COLS; j++) {
        printf(" %d", j + 1);
    }
    printf("\n");
}

void initialiserGrille(char grille[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            grille[i][j] = ' ';
        }
    }
}

void ajouterPion(char grille[ROWS][COLS], int colonne, char pion) {
    int ligne = ROWS - 1;
    while (ligne >= 0) {
        if (grille[ligne][colonne] == ' ') {
            grille[ligne][colonne] = pion;
            break;
        }
        ligne--;
    }
}

bool verifierVictoire(char grille[ROWS][COLS], char pion) {
    // Vérifier les lignes
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS - 3; j++) {
            if (grille[i][j] == pion && grille[i][j + 1] == pion && grille[i][j + 2] == pion && grille[i][j + 3] == pion) {
                return true;
            }
        }
    }

    // Vérifier les colonnes
    for (int i = 0; i < ROWS - 3; i++) {
        for (int j = 0; j < COLS; j++) {
            if (grille[i][j] == pion && grille[i + 1][j] == pion && grille[i + 2][j] == pion && grille[i + 3][j] == pion) {
                return true;
            }
        }
    }

    // Vérifier les diagonales ascendantes
    for (int i = 3; i < ROWS; i++) {
        for (int j = 0; j < COLS - 3; j++) {
            if (grille[i][j] == pion && grille[i - 1][j + 1] == pion && grille[i - 2][j + 2] == pion && grille[i - 3][j + 3] == pion) {
                return true;
            }
        }
    }

    // Vérifier les diagonales descendantes
    for (int i = 3; i < ROWS; i++) {
        for (int j = 3; j < COLS; j++) {
            if (grille[i][j] == pion && grille[i - 1][j - 1] == pion && grille[i - 2][j - 2] == pion && grille[i - 3][j - 3] == pion) {
                return true;
            }
        }
    }

    return false;
}

void jeu() {
    char grille[ROWS][COLS];
    int joueur = 1;
    int colonne;

    // Initialiser la grille avec des espaces vides
    initialiserGrille(grille);

    while (true) {
        // Afficher la grille
        afficherGrille(grille);

        // Demander au joueur de choisir une colonne
        printf("Joueur %d, choisissez une colonne (1-%d) : ", joueur, COLS);
        scanf("%d", &colonne);
        colonne--; // Convertir de l'index 1 à l'index 0

        // Ajouter le pion dans la colonne choisie
        ajouterPion(grille, colonne, (joueur == 1) ? 'X' : 'O');

        // Vérifier si le joueur a gagné
        if (verifierVictoire(grille, (joueur == 1) ? 'X' : 'O')) {
            printf("Le joueur %d a gagné!\n", joueur);
            break;
        }

        // Changer de joueur
        joueur = (joueur == 1) ? 2 : 1;
    }

    // Afficher la grille finale
    afficherGrille(grille);
}


void interface() {
    int choix;

    printf("Bienvenue dans le jeu Puissance 4 !\n");
    printf("1. Mode 1 joueur\n");
    printf("2. Mode 2 joueurs\n");
    printf("Choisissez un mode de jeu : ");
    scanf("%d", &choix);

    switch (choix) {
        case 1:
            jeuContreOrdinateur();
            break;
        case 2:
            jeu();
            break;
        default:
            printf("Choix invalide. Veuillez choisir un mode de jeu valide.\n");
            interface();
            break;
    }
}

void jeuContreOrdinateur() {
    char grille[ROWS][COLS];
    int joueur = 1;
    int colonne;
    int niveau;

    // Initialiser la grille avec des espaces vides
    initialiserGrille(grille);

    // Demander au joueur de choisir le niveau
    printf("Choisissez le niveau de difficulté (1-3) : ");
    scanf("%d", &niveau);

    while (true) {
        // Afficher la grille
        afficherGrille(grille);

        if (joueur == 1) {
            // Demander au joueur de choisir une colonne
            printf("Joueur %d, choisissez une colonne (1-%d) : ", joueur, COLS);
            scanf("%d", &colonne);
            colonne--; // Convertir de l'index 1 à l'index 0
        } else {
            // Laisser l'ordinateur choisir une colonne
            // Appeler la fonction bot pour choisir la colonne
            colonne = meilleurCoup(grille, niveau);
        }

        // Ajouter le pion dans la colonne choisie
        ajouterPion(grille, colonne, (joueur == 1) ? 'X' : 'O');

        // Vérifier si le joueur a gagné
        if (verifierVictoire(grille, (joueur == 1) ? 'X' : 'O')) {
            printf("Le joueur %d a gagné!\n", joueur);
            break;
        }

        // Changer de joueur
        joueur = (joueur == 1) ? 2 : 1;
    }

    // Afficher la grille finale
    afficherGrille(grille);
}


int main() {
    interface();
    return 0;
}
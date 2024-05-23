#ifndef ORDINATEUR_H
#define ORDINATEUR_H

#define ROWS 6
#define COLS 7

#include <stdbool.h>

void initialiserMatrice(int grillePoids[ROWS][COLS]);
bool estPleine(int grilleJeu[ROWS][COLS], int col);
void jouerBot(int grilleJeu[ROWS][COLS], int col);
void enleverBot(int grilleJeu[ROWS][COLS], int col);
int minimax(int grilleJeu[ROWS][COLS], int profondeur, bool estMaximisant);
int meilleurCoup(int grille[ROWS][COLS], int depth);

#endif // ORDINATEUR_H
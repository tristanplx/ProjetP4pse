#ifndef ORDINATEUR_H
#define ORDINATEUR_H

#define ROWS 6
#define COLS 7

#include <stdbool.h>

void initializeMatrix();
bool estPleine(int grilleJeu[ROWS][COLS], int col);
void jouerBot(int grilleJeu[ROWS][COLS], int col);
void enleverBot(int grilleJeu[ROWS][COLS], int col);
int minimax(int depth, bool isMaximizing, int grille[ROWS][COLS]);
int meilleurCoup(int grille[ROWS][COLS], int depth);

#endif // ORDINATEUR_H
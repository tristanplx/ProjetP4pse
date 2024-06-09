#ifndef ORDINATEUR_H
#define ORDINATEUR_H

#define LIGNES 6
#define COLONNES 7

bool estPleine(int grilleJeu[LIGNES][COLONNES], int col);
void jouerBot(int grilleJeu[LIGNES][COLONNES], int col);
void enleverBot(int grilleJeu[LIGNES][COLONNES], int col);
void jouerJoueur(int grilleJeu[LIGNES][COLONNES], int col);
void enleverJoueur(int grilleJeu[LIGNES][COLONNES], int col);
bool verifierLigne(int a, int b, int c, int d);
bool jeuTermine(int grilleJeu[LIGNES][COLONNES]);
int evaluerPosition(int a, int b, int c, int d);
int evaluerScore(int grilleJeu[LIGNES][COLONNES]);
int minimax(int grilleJeu[LIGNES][COLONNES], int profondeur, bool estMaximisant);
int meilleurCoup(int grilleJeu[LIGNES][COLONNES], int profondeur);

#endif // ORDINATEUR_H

#ifndef JEU_H
#define JEU_H

#define ROWS 6
#define COLS 7

void afficherGrille(char grille[ROWS][COLS]);
void initialiserGrille(char grille[ROWS][COLS]);
void ajouterPion(char grille[ROWS][COLS], int colonne, char pion);
void jeuContreOrdinateur();
void jeu();
void interface();
bool verifierVictoire(char grille[ROWS][COLS], char pion);

#endif // JEU_H
#ifndef JEU_H
#define JEU_H

#define ROWS 6
#define COLS 7

void afficherGrille(int grille[ROWS][COLS]);
void initialiserGrille(int grille[ROWS][COLS]);
void ajouterPion(int grille[ROWS][COLS], int colonne, int pion);
void jeuContreOrdinateur();
void jeu();
void interface();
bool verifierVictoire(int grille[ROWS][COLS], int pion);



#endif // JEU_H
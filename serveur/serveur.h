#ifndef SERVEUR_H
#define SERVEUR_H

#define CMD   "serveur"

#define NB_WORKERS 2
#define ROWS 6
#define COLS 7

void sessionClient(int canal1,int canal2, int grille[ROWS][COLS], int type_jeu, int niv_bot1, int niv_bot2);


#endif // SERVEUR_H
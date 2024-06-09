#ifndef CLIENT_H
#define CLIENT_H

#define CMD  "client"

#define ROWS 6
#define COLS 7

void jouer(int sock, int term, int niv_bot);
void choisirModeDeJeu(int sock, int *term, int *niv_bot);

#endif /* CLIENT_H */
#include "../include/pse.h"
#include "../game/jeu.h"
#include "../ordinateur/ordinateur.h"
#include "client.h"

#define CMD   "client"
#define ROWS 6
#define COLS 7


int jouerRobot(int grille[ROWS][COLS], int niveau);

int main(int argc, char *argv[]) {
    int sock, ret;
    struct sockaddr_in *adrServ;
    char buffer[1024];
    int term = 0, niv_bot = 0;

    if (argc != 3)
        erreur("usage: %s machine port\n", argv[0]);

    printf("%s: creating a socket\n", CMD);
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
        erreur_IO("socket");

    printf("%s: DNS resolving for %s, port %s\n", CMD, argv[1], argv[2]);
    adrServ = resolv(argv[1], argv[2]);
    if (adrServ == NULL)
        erreur("adresse %s port %s inconnus\n", argv[1], argv[2]);

    printf("%s: adr %s, port %hu\n", CMD,
           stringIP(ntohl(adrServ->sin_addr.s_addr)),
           ntohs(adrServ->sin_port));

    printf("%s: connecting the socket\n", CMD);
    ret = connect(sock, (struct sockaddr *)adrServ, sizeof(struct sockaddr_in));
    if (ret < 0)
        erreur_IO("connect");

    ret = read(sock, buffer, sizeof(buffer)); // Lire le message du serveur demandant le mode de jeu
    while (true) {
        if (ret <= 0)
            erreur_IO("read mode de jeu");
        printf("\n\n---------------------------\n\n");
        printf("%s", buffer);
        printf("\n\n---------------------------\n\n");
        scanf("%d", &term);
        if (term == 1 || term == 2) {
            write(sock, &term, sizeof(term)); // Envoyer le mode de jeu au serveur
            break;
        } else {
            printf("Mode de jeu invalide, veuillez entrer 1 ou 2.\n");
        }
    }

    // Recevoir le niveau du bot si applicable
    if (term == 2) {
        ret = read(sock, buffer, sizeof(buffer)); // Lire le message du serveur demandant le niveau du bot
        while (true) {
            if (ret <= 0)
                erreur_IO("read niveau bot");
            printf("%s", buffer);
            scanf("%d", &niv_bot);
            if (niv_bot >= 1 && niv_bot <= 3) {
                write(sock, &niv_bot, sizeof(niv_bot)); // Envoyer le niveau du bot au serveur
                break;
            } else {
                printf("Niveau du bot invalide, veuillez entrer une valeur à nouveau.\n");
            }
        }
    }
    while(1){
        jouer(sock, term, niv_bot);
    }

    return 0;
}

void jouer(int sock, int term, int niv_bot) {
    int fin = FAUX;
    int grille[ROWS][COLS];
    int ret;

    while (!fin) {
        int numColonne;

        printf("\n---------------------------\n\nAttente de l'adversaire...\n\n---------------------------\n");
        // Recevoir l'état de la grille du serveur
        printf("\n");
        ret = read(sock, &grille, sizeof(grille));
        if (ret <= 0)
            erreur_IO("read grille");
        printf("\n");
        afficherGrille(grille);

        if (grillePleine(grille)) {
            printf("\n---------------------------\nLa grille est pleine, match nul !\n");
            fin = VRAI;
            break;
        }

        if (verifierVictoire(grille, 1)) {
            printf("\n---------------------------\nVous avez perdu!\n");
            fin = VRAI;
            break;
        }

        if (verifierVictoire(grille, 2)) {
            printf("\n---------------------------\nVous avez perdu!\n");
            fin = VRAI;
            break;
        }

        if (term == 2) { // Si c'est un bot
            int colonne = meilleurCoup(grille, niv_bot);
            colonne++;
            ret = write(sock, &colonne, sizeof(colonne)); // Envoyer la colonne choisie par le bot
        } else { // Si c'est un humain
            printf("\n---------------------------\n\nChoisissez une colonne (1-7) : \n");
            scanf("%d", &numColonne);
            ret = write(sock, &numColonne, sizeof(numColonne)); // Envoyer la colonne choisie par l'humain
        }

        printf("\n---------------------------\n\nLe coup que vous avez joué est:\n\n");
        ret = read(sock, &grille, sizeof(grille));
        if (ret <= 0)
            erreur_IO("read grille après coup");
        afficherGrille(grille);

        if (verifierVictoire(grille, 1)) {
            printf("\n---------------------------\nVous avez gagné!\n");
            fin = VRAI;
            break;
        }

        if (verifierVictoire(grille, 2)) {
            printf("\n---------------------------\nVous avez gagné!\n");
            fin = VRAI;
            break;
        }

        if (grillePleine(grille)) {
            printf("\n---------------------------\nLa grille est pleine, match nul !\n");
            fin = VRAI;
            break;
        }
    }
}
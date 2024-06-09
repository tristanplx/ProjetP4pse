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
    int fin = FAUX;
    char buffer[1024];
    int grille[ROWS][COLS];
    int term, niv_bot = 0;

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

    // Recevoir le choix du mode de jeu et le niveau du bot si applicable
    ret = read(sock, buffer, sizeof(buffer)); // Lire le message du serveur demandant le mode de jeu
    if (ret <= 0)
        erreur_IO("read mode de jeu");
    printf("%s", buffer);
    scanf("%d", &term);
    write(sock, &term, sizeof(term)); // Envoyer le mode de jeu au serveur

    if (term == 2) {
        ret = read(sock, buffer, sizeof(buffer)); // Lire le message du serveur demandant le niveau du bot
        if (ret <= 0)
            erreur_IO("read niveau bot");
        printf("%s", buffer);
        scanf("%d", &niv_bot);
        write(sock, &niv_bot, sizeof(niv_bot)); // Envoyer le niveau du bot au serveur
    }

    while (!fin) {

        int numColonne;

        printf("Attente de l'adversaire...\n");
        // Recevoir l'état de la grille du serveur
        printf("avant recevoir grille\n");
        read(sock, &grille, sizeof(grille));
        printf("apres recevoir grille\n");
        afficherGrille(grille);


        if (grillePleine(grille)) {
            printf("La grille est pleine, match nul !\n");
            fin = VRAI;
            break;
        }

        if (verifierVictoire(grille, 1)) {
            printf("Vous avez perdu!\n");
            fin = VRAI;
            break;
        }

        if (verifierVictoire(grille, 2)) {
            printf("Vous avez perdu!\n");
            fin = VRAI;
            break;
        }

        if (term == 2) { // Si c'est un bot
            int colonne = jouerRobot(grille, niv_bot);
            ret = write(sock, &colonne, sizeof(colonne)); // Envoyer la colonne choisie par le bot
        } else { // Si c'est un humain
            printf("Choisissez une colonne (1-7) : \n");
            scanf("%d", &numColonne);
            ret = write(sock, &numColonne, sizeof(numColonne)); // Envoyer la colonne choisie par l'humain
        }

        printf("Le coup que vous avez joué est:\n");
        read(sock, &grille, sizeof(grille));
        afficherGrille(grille);

        if (verifierVictoire(grille, 1)) {
            printf("Vous avez gagné!\n");
            fin = VRAI;
            break;
        }

        if (verifierVictoire(grille, 2)) {
            printf("Vous avez gagné!\n");
            fin = VRAI;
            break;
        }

        if (grillePleine(grille)) {
            printf("La grille est pleine, match nul !\n");
            fin = VRAI;
            break;
        }

    }

}

int jouerRobot(int grille[ROWS][COLS], int niveau) {
    return meilleurCoup(grille, niveau);
}

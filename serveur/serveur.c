#include <pthread.h>
#include "../include/pse.h"
#include "../game/jeu.h"
#include "../ordinateur/ordinateur.h"
#include "serveur.h"

#define CMD         "serveur"
#define NB_WORKERS  2
#define ROWS 6
#define COLS 7

#define JOUEUR_1 1
#define JOUEUR_2 2
#define BOT 3

typedef struct {
    int canal1;
    int canal2;
    int grille[ROWS][COLS];
    int id; // Ajout d'un identifiant unique pour chaque partie
} partie;

int main(int argc, char *argv[]) {
    short port;//port du serveur
    int ecoute, canal1, canal2, ret;
    struct sockaddr_in adrEcoute, adrClient;
    unsigned int lgAdrClient = sizeof(adrClient);
    int game_id = 1; // Compteur pour les identifiants de parties

    if (argc != 2)
        erreur("usage: %s port\n", argv[0]);

    port = (short)atoi(argv[1]);

    ecoute = socket(AF_INET, SOCK_STREAM, 0);
    if (ecoute < 0)
        erreur_IO("socket");

    adrEcoute.sin_family = AF_INET;
    adrEcoute.sin_addr.s_addr = INADDR_ANY;
    adrEcoute.sin_port = htons(port);
    printf("%s: binding to INADDR_ANY address on port %d\n", CMD, port);
    ret = bind(ecoute, (struct sockaddr *)&adrEcoute, sizeof(adrEcoute));
    if (ret < 0)
        erreur_IO("bind");

    printf("%s: listening to potential clients\n", CMD);
    ret = listen(ecoute, 5);
    if (ret < 0)
        erreur_IO("listen");

    while (1) {
        canal1 = accept(ecoute, (struct sockaddr *)&adrClient, &lgAdrClient);
        if (canal1 < 0)
            erreur_IO("accept");

        printf("%s: client1 connected\n", CMD);

        canal2 = accept(ecoute, (struct sockaddr *)&adrClient, &lgAdrClient);
        if (canal2 < 0)
            erreur_IO("accept");

        printf("%s: client2 connected\n", CMD);

        partie *game = malloc(sizeof(partie));
        game->canal1 = canal1;
        game->canal2 = canal2;
        game->id = game_id++; // Initialisation de l'identifiant unique
        initialiserGrille(game->grille);

        pthread_t thread;//création d'un thread pour chaque partie
        pthread_create(&thread, NULL, handleClients, game);//appel de la fonction handleClients
        pthread_detach(thread);
    }

    close(ecoute);
    return 0;
}

void *handleClients(void *arg) {//fonction pour gérer les clients
    partie *game = (partie *)arg;
    int canal1 = game->canal1;//canal pour le client1
    int canal2 = game->canal2;//canal pour le client2
    int term1, niv_bot1, term2, niv_bot2;
    int type_jeu;

    int choix = 1;
    while (choix == 1) {//boucle pour rejouer
        initialiserGrille(game->grille);//initialisation de la grille
        type_jeu = changerModeJeu(canal1, canal2, &term1, &niv_bot1, &term2, &niv_bot2);//changement du mode de jeu
        sessionClient(canal1, canal2, game->grille, sizeof(game->grille), type_jeu, niv_bot1, niv_bot2, game->id);//déroulement de la partie
        printf("Partie %d terminée.\n", game->id);
        printf("\n\n---------------------------\n\n");
        printf("Nouvelle partie ? (1: oui, 2: non) : ");
        scanf("%d", &choix);
        while (choix != 1 && choix != 2) {
            printf("Choix invalide. Veuillez choisir 1 ou 2.\n");
            printf("Nouvelle partie ? (1: oui, 2: non) : ");
            scanf("%d", &choix);
            printf("\n\n---------------------------\n\n");
        }
    }

    if (close(canal1) == -1)//fermeture du canal1
        erreur_IO("close canal1");

    if (close(canal2) == -1)//fermeture du canal2
        erreur_IO("close canal2");

    free(game);//libération de la mémoire
    pthread_exit(NULL);//fin du thread
}

int changerModeJeu(int canal1, int canal2, int *term1, int *niv_bot1, int *term2, int *niv_bot2) {//fonction pour changer le mode de jeu
    int ret;

    write(canal1, "Choisissez le mode de jeu (1: classique, 2: robot): ", 53);
    ret = read(canal1, term1, sizeof(*term1));
    if (ret <= 0)
        erreur_IO("read term1");

    if (*term1 == 2) {
        write(canal1, "Choisissez le niveau du bot (0: facile, 1: modéré, 2: difficile, 3: expert): ", 79);
        ret = read(canal1, niv_bot1, sizeof(*niv_bot1));
        if (ret <= 0)
            erreur_IO("read niv_bot1");
    }

    write(canal2, "Choisissez le mode de jeu (1: classique, 2: robot): ", 53);
    ret = read(canal2, term2, sizeof(*term2));
    if (ret <= 0)
        erreur_IO("read term2");

    if (*term2 == 2) {
        write(canal2, "Choisissez le niveau du bot (0: facile, 1: modéré, 2: difficile, 3: expert): ", 79);
        ret = read(canal2, niv_bot2, sizeof(*niv_bot2));
        if (ret <= 0)
            erreur_IO("read niv_bot2");
    }

    if (*term1 == 1 && *term2 == 1) {
        return 1; // Humain vs Humain
    } else if (*term1 == 1 && *term2 == 2) {
        return 2; // Humain vs Robot
    } else if (*term1 == 2 && *term2 == 1) {
        return 2; // Robot vs Humain
    } else if (*term1 == 2 && *term2 == 2) {
        return 3; // Robot vs Robot
    } else {
        printf("Mode de jeu invalide.\n");
        exit(EXIT_FAILURE);
    }
}

void sessionClient(int canal1, int canal2, int grille[ROWS][COLS], int tailleGrille, int type_jeu, int niv_bot1, int niv_bot2, int game_id) {//fonction pour dérouler la partie
    int fin = FAUX;
    int colonne = 0;

    while (!fin) {
        printf("\n---------------------------\n");
        write(canal1, grille, tailleGrille);//envoi de la grille au client1
        read(canal1, &colonne, sizeof(colonne));//lecture de la colonne jouée par le client1
        printf("\n\nPartie %d - Le joueur client1 a joué la colonne: %d\n\n", game_id, colonne);
        colonne--;
        ajouterPion(grille, colonne, JOUEUR_1);//ajout du pion du client1 dans la grille
        afficherGrille(grille);

        write(canal1, grille, tailleGrille);

        fin = verifierVictoire(grille, JOUEUR_1);

        if (fin) {
            printf("\n---------------------------\n\n");
            afficherGrille(grille);
            printf("\n---------------------------\n\n");
            write(canal2, grille, tailleGrille);
            break;
        }

        fin = grillePleine(grille);

        if (fin) {
            printf("\n---------------------------\n\n");
            afficherGrille(grille);
            printf("\n---------------------------\n\n");
            write(canal2, grille, tailleGrille);
            break;
        }

        write(canal2, grille, tailleGrille);//envoi de la grille au client2
        printf("\n---------------------------\n");
        read(canal2, &colonne, sizeof(colonne));//lecture de la colonne jouée par le client2
        printf("\n\nPartie %d - Le joueur client2 a joué la colonne: %d\n\n", game_id, colonne);
        colonne--;
        ajouterPion(grille, colonne, JOUEUR_2);//  Ajout du pion du client2 dans la grille
        afficherGrille(grille);
        write(canal2, grille, tailleGrille);

        fin = verifierVictoire(grille, JOUEUR_2);

        if (fin) {
            printf("\n---------------------------\n\n");
            afficherGrille(grille);
            printf("\n---------------------------\n\n");
            write(canal1, grille, tailleGrille);
            break;
        }

        fin = grillePleine(grille);

        if (fin) {
            printf("\n---------------------------\n\n");
            afficherGrille(grille);
            printf("\n---------------------------\n\n");
            write(canal1, grille, tailleGrille);
            break;
        }
    }
}

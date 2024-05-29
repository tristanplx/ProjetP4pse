#include "../include/pse.h"
#include "../game/jeu.h"
#include "../ordinateur/ordinateur.h"
#include "serveur.h"
#include "../Makefile.inc"

#define   CMD         "serveur"
#define   NB_WORKERS  2
#define ROWS 6
#define COLS 7

#define JOUEUR_1 1
#define JOUEUR_2 2
#define BOT 3

int GRILLE[ROWS][COLS];

int main(int argc, char *argv[]) {
  short port;
  int ecoute, canal1, canal2, ret;
  struct sockaddr_in adrEcoute, adrClient;
  unsigned int lgAdrClient;

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

  for (int i = 0; i < NB_WORKERS; i++) {
    canal1 = accept(ecoute, (struct sockaddr *)&adrClient, &lgAdrClient);
    if (canal1 < 0)
      erreur_IO("accept");

    printf("%s: client1 connected\n", CMD);

    int term1;
    int niv_bot1 = 0; // Niveau du bot de 1 à 3

    // Demander le mode de jeu pour le joueur 1
    write(canal1, "Choisissez le mode de jeu (1: classique, 2: robot): ", 53);
    ret = read(canal1, &term1, sizeof(term1));
    if (ret <= 0)
        erreur_IO("read term1");


    if (term1 == 2) {
      write(canal1, "Choisissez le niveau du bot (1: facile, 2: moyen, 3: difficile): ", 66);
      ret = read(canal1, &niv_bot1, sizeof(niv_bot1));
      if (ret <= 0)
          erreur_IO("read niv_bot1");
    }


    canal2 = accept(ecoute, (struct sockaddr *)&adrClient, &lgAdrClient);
    if (canal2 < 0)
      erreur_IO("accept");

    printf("%s: client2 connected\n", CMD);

    int term2;
    int niv_bot2 = 0; // Niveau du bot de 1 à 3

    // Demander le mode de jeu pour le joueur 2
    write(canal2, "Choisissez le mode de jeu (1: classique, 2: robot): ", 53);
    ret = read(canal2, &term2, sizeof(term2));
    if (ret <= 0)
        erreur_IO("read term2");

    if (term2 == 2) {
      write(canal2, "Choisissez le niveau du bot (1: facile, 2: moyen, 3: difficile): ", 66);
      ret = read(canal2, &niv_bot2, sizeof(niv_bot2));
      if (ret <= 0)
          erreur_IO("read niv_bot2");
    }

    int type_jeu;

    if (term1 == 1 && term2 == 1) {
      type_jeu = 1; // Humain vs Humain
    } else if (term1 == 1 && term2 == 2) {
      type_jeu = 2; // Humain vs Robot
    } else if (term1 == 2 && term2 == 1) {
      type_jeu = 2; // Robot vs Humain
    } else if (term1 == 2 && term2 == 2) {
      type_jeu = 3; // Robot vs Robot
    } else {
      printf("Mode de jeu invalide.\n");
      exit(EXIT_FAILURE);
    }

    initialiserGrille(GRILLE);
    sessionClient(canal1, canal2, GRILLE, type_jeu, niv_bot1, niv_bot2);

    if (close(canal1) == -1)
      erreur_IO("close canal1");
    
    if (close(canal2) == -1)
      erreur_IO("close canal2");

    exit(EXIT_SUCCESS);
  }
}

void sessionClient(int canal1,int canal2, int grille[ROWS][COLS], int type_jeu, int niv_bot1, int niv_bot2){
  int fin = FAUX;
  int colonne;

  while (!fin) {
    afficherGrille(grille);
    write(canal1, "C'est votre tour !\n", 19);
    colonne = read(canal1, &colonne, sizeof(colonne));
    colonne --;
    ajouterPion(grille, colonne, JOUEUR_1);

    fin = verifierVictoire(grille, JOUEUR_1);
  
    if (fin) {
      write(canal1, "Vous avez gagné !\n", 19);
      write(canal2, "Vous avez perdu !\n", 18);
      break;
    }

    fin = grillePleine(grille);

    if (fin) {
      write(canal1, "Match nul !\n", 12);
      write(canal2, "Match nul !\n", 12);
      break;
    }

    afficherGrille(grille);
    write(canal2, "C'est votre tour !\n", 19);
    colonne = read(canal2, &colonne, sizeof(colonne));
    colonne --;
    
    ajouterPion(grille, colonne, JOUEUR_2);

    fin = verifierVictoire(grille, JOUEUR_2);

    if (fin) {
      write(canal2, "Vous avez gagné !\n", 19);
      write(canal1, "Vous avez perdu !\n", 18);
      break;
    }

    fin = grillePleine(grille);

    if (fin) {
      write(canal1, "Match nul !\n", 12);
      write(canal2, "Match nul !\n", 12);
      break;
    }
  }
}

/*
    } else if (type_jeu == 2) {
      // Humain vs Robot
      afficherGrille(grille);
      write(canal1, "C'est votre tour !\n", 19);
      colonne = read(canal1, &colonne, sizeof(colonne));
      colonne --;
      ajouterPion(grille, colonne, JOUEUR_1);

      fin = verifierVictoire(grille, JOUEUR_1);

      if (fin) {
        write(canal1, "Vous avez gagné !\n", 19);
        write(canal2, "Vous avez perdu !\n", 18);
        break;
      }

      fin = grillePleine(grille);

      if (fin) {
        write(canal1, "Match nul !\n", 12);
        write(canal2, "Match nul !\n", 12);
        break;
      }

      afficherGrille(grille);
      write(canal2, "C'est au tour du bot !\n", 24);
      colonne = meilleurCoup(grille, niv_bot2);
      ajouterPion(grille, colonne, JOUEUR_2);

      fin = verifierVictoire(grille, JOUEUR_2);

      if (fin) {
        write(canal2, "Vous avez gagné !\n", 19);
        write(canal1, "Vous avez perdu !\n", 18);
        break;
      }

      fin = grillePleine(grille);

      if (fin) {
        write(canal1, "Match nul !\n", 12);
        write(canal2, "Match nul !\n", 12);
        break;
      }
      
    } else if (type_jeu == 3) {
      // Robot vs Robot
      afficherGrille(grille);
      write(canal1, "C'est au tour du bot 1 !\n", 26);
      colonne = meilleurCoup(grille, niv_bot1);
      ajouterPion(grille, colonne, JOUEUR_1);

      fin = verifierVictoire(grille, JOUEUR_1);

      if (fin) {
        write(canal1, "Vous avez gagné !\n", 19);
        write(canal2, "Vous avez perdu !\n", 18);
        break;
      }

      fin = grillePleine(grille);

      if (fin) {
        write(canal1, "Match nul !\n", 12);
        write(canal2, "Match nul !\n", 12);
        break;
      }

      afficherGrille(grille);
      write(canal2, "C'est au tour du bot 2 !\n", 26);
      colonne = meilleurCoup(grille, niv_bot2);
      ajouterPion(grille, colonne, JOUEUR_2);

      fin = verifierVictoire(grille, JOUEUR_2);

      if (fin) {
        write(canal2, "Vous avez gagné !\n", 19);
        write(canal1, "Vous avez perdu !\n", 18);
        break;
      }

      fin = grillePleine(grille);

      if (fin) {
        write(canal1, "Match nul !\n", 12);
        write(canal2, "Match nul !\n", 12);
        break;
      }
    }
  }

*/






















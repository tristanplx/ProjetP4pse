[![English](https://cdn-icons-png.flaticon.com/512/197/197374.png)](#english-version) 
[![Français](https://cdn-icons-png.flaticon.com/512/197/197560.png)](#version-française)
# ProjetP4pse

## <a name="english-version"></a> English Version

## Connect 4 Project

This project implements a Connect 4 game using sockets to enable communication between a server and multiple clients. The game supports the following modes: Human vs Human, Human vs Robot, and Robot vs Robot. The robot's level is chosen by the user.

## Project Structure
```
. 
├── client
│ ├── client
│ ├── client.c 
│ ├── client.h 
│ └── Makefile 
├── game 
│ ├── game.c
│ └── game.h 
├── include 
│ ├── dataspec.h 
│ ├── datathread.h
│ ├── error.h 
│ ├── line.h 
│ ├── msgbox.h 
│ ├── msg.h
│ ├── pse.h 
│ └── resolv.h 
├── lib 
│ └── libpse.a 
├── Makefile.inc 
├── modules
│ ├── datathread.c 
│ ├── error.c 
│ ├── line.c
│ ├── Makefile
│ ├── msgbox.c
│ ├── msg.c
│ └── resolv.c
├── computer
│ ├── computer.c
│ └── computer.h
├── packages.microsoft.gpg
├── README.md
└── server   
├── Makefile   
├── server.c   
└── server.h
```

## Compilation

To compile the project, use `gcc`:

1. In the first terminal for the server, navigate to the server folder. To build the file, run:

    ```sh
    make
    ```

2. In another terminal for the client (and a second one), navigate to the client folder. To build the file, run:

    ```sh
    make
    ```

3. The application can handle multiple games at the same time. Repeat step 2 in new terminals to launch more games.

### Starting the Server

To start the server, use the following command:

```sh
./server <port>
```
Where <port> is the port number that the server will use to listen for client connections.

Starting the Client
To start a client, use the following command:

```sh
./client localhost <port>
```
Where <port> is the port number where the server is listening.

Example
Start the server:

```sh
make
./server 2000
```
Start two clients (in two separate terminals):

```sh
make
./client localhost 2000
```

## Features

### Game Modes
The server asks the clients to choose a game mode (classic or against a robot). If playing against a robot, the client can select its level.

### Game Grid
The game grid is displayed and updated after each move.

### Win Detection
The game automatically checks for winning conditions after each move.

### Robot Mode
A client can choose to play against a robot. The robot uses the Minimax algorithm to make decisions. The search depth of this algorithm controls the difficulty of the game.

### Client/Server Application
The game is launched via a server terminal and played with two client terminals.

### Multithreading
Multiple games can run simultaneously.

## Key Files and Functions
### server.c

- `main`: Initializes the server, manages client connections, and orchestrates the games.
- `changerModeJeu`: Asks the clients to choose the game mode and robot level if necessary.
- `sessionClient`: Manages a game session between two clients.
- `handleClient`: Handles client connections, pairing two clients for a game.

### client.c

- `main`: Initializes the client, connects to the server, and manages the interaction with the server.
- `choisirModeDeJeu`: Allows the client to choose the game mode.
- `jouer`: Manages the gameplay for the client.

### jeu.c

- `afficherGrille`: Displays the game grid.
- `initialiserGrille`: Initializes the game grid.
- `ajouterPion`: Adds a disc to the grid.
- `verifierVictoire`: Checks the winning conditions.
- `grillePleine`: Checks if the grid is full.
  Other functions are used for local testing of the game.

### ordinateur.c

- `meilleurCoup`: Uses the Minimax algorithm to choose the best move for the robot.
- `minimax`: Minimax algorithm to evaluate the moves.
- `evaluerPosition`: Evaluates all possible moves.
- `evaluerScore`: Scores the current grid state.
- `jeuTermine`: Checks if the game is over.
- `jouerBot`: Makes the bot play, using Minimax depth search.
- `enleverBot`: Removes the bot's moves during depth search to simulate further gameplay.
- `estPleine`: Checks if a column is full.
- `jouerJoueur`: Simulates an opponent's move to challenge the bot.
- `enleverJoueur`: Removes the simulated player's moves during depth search.
- `verifierLigne`: Checks if a player has completed a line of 4, used by `jeuTermine`.

## Authors
School project for the Mines of Saint-Etienne.
[Martin RABIER](https://github.com/MartinRabier) @MartinRabier
[Tristan Panhelleux](https://github.com/tristanplx) @tristanplx
# ProjetP4pse

## <a name="version-française"></a> Version Française

## Projet Puissance 4

Ce projet implémente un jeu de Puissance 4 en utilisant des sockets pour permettre la communication entre un serveur et plusieurs clients. Le jeu supporte les modes de jeu Humain vs Humain, Humain vs Robot et Robot vs Robot. Le niveau des robots est choisi par l'utilisateur.

## Structure du Projet

```
.
├── client
│   ├── client
│   ├── client.c
│   ├── client.h
│   └── Makefile
├── game
│   ├── jeu.c
│   └── jeu.h
├── include
│   ├── dataspec.h
│   ├── datathread.h
│   ├── erreur.h
│   ├── ligne.h
│   ├── msgbox.h
│   ├── msg.h
│   ├── pse.h
│   └── resolv.h
├── lib
│   └── libpse.a
├── Makefile.inc
├── modules
│   ├── datathread.c
│   ├── erreur.c
│   ├── ligne.c
│   ├── Makefile
│   ├── msgbox.c
│   ├── msg.c
│   └── resolv.c
├── ordinateur
│   ├── ordinateur.c
│   └── ordinateur.h
├── packages.microsoft.gpg
├── README.md
└── serveur
    ├── Makefile
    ├── serveur.c
    └── serveur.h
```

## Compilation

Pour compiler ce projet, utilisez `gcc` :

1. Dans un premier terminal serveur, se placer dans le dossier serveur. Pour exécuter le fichier, utilisez :

    ```sh
    make
    ```

2. Dans un premier terminal client, puis un second, se placer dans le dossier client. Pour exécuter le fichier, utilisez:

    ```sh
    make
    ```
3. L'application gère plusieurs partie simultanément, répéter l'étape 2 pour lancer d'autres parties répéter l'étape 2 dans de nouveaux terminaux.

### Démarrage du serveur

Pour démarrer le serveur, exécutez la commande suivante :

```sh
./serveur <port>
```

Où `<port>` est le numéro de port sur lequel le serveur écoutera les connexions des clients.

### Démarrage du client

Pour démarrer un client, exécutez la commande suivante :

```sh
./client localhost <port>
```

Où `<port>` est le numéro de port sur lequel le serveur est en écoute.

## Exemple

Démarrez le serveur :

```sh
make
./serveur 2000
```

Démarrez deux clients (dans deux terminaux différents) :

```sh
make
./client localhost 2000
```

## Fonctionnalités

### Mode de Jeu

Le serveur demande aux clients de choisir un mode de jeu (classique ou contre un robot). Et si mode robot, choisir le niveau de ce dernier.

### Grille de Jeu

La grille de jeu est affichée et mise à jour après chaque coup.

### Vérification de Victoire

Le jeu vérifie automatiquement les conditions de victoire après chaque coup.

### Mode Robot

Un client peut choisir de jouer contre un robot. Le robot utilise l'algorithme Minimax pour choisir ses coups. La profondeur de parcours de cet algorithme régit la difficulté du jeu.

### Application client/serveur
Le jeu est lancé via un terminal serveur serveur et se joue avec deux terinaux clients.

### Multithread
On peut lancer plusieurs parties en simultanée.

## Fichiers et Fonctions Clés

### serveur.c

- `main` : Initialisation du serveur, gestion des connexions des clients, et orchestration des parties.
- `changerModeJeu` : Demande aux clients de choisir le mode de jeu et le niveau du robot si applicable.
- `sessionClient` : Gère une session de jeu entre deux clients.
- `handleClient` : Permet de gérer la connection de clients, les attribuant deux à deux à des parties.

### client.c

- `main` : Initialise le client, se connecte au serveur et gère l'interaction avec le serveur.
- `choisirModeDeJeu` : Permet au client de choisir le mode de jeu.
- `jouer` : Gère le déroulement d'une partie pour le client.

### jeu.c

- `afficherGrille` : Affiche la grille de jeu.
- `initialiserGrille` : Initialise la grille de jeu.
- `ajouterPion` : Ajoute un pion dans la grille.
- `verifierVictoire` : Vérifie les conditions de victoire.
- `grillePleine` : Vérifie si la grille est pleine.
  Les autres fonctions permettent de tester le jeu en local.

### ordinateur.c

- `meilleurCoup` : Utilise l'algorithme Minimax pour choisir le meilleur coup pour le robot.
- `minimax` : Algorithme Minimax pour évaluer les coups.
- `evaluerPosition` : Parcours l'ensemble des coups possibles.
- `evaluerScore` : Évalue le score de la grille actuelle.
- `jeuTermine` : Vérifie si le jeu est terminé.
- `jouerBot` : Fait jouer le bot, utiliser pour le parcours en profondeur Minimax.
- `enleverBot` : Enlève les cases jouées par le bot dans le parcours en profondeur pour simuler la suite de la partie.
- `estPleine` : Vérifie si une colonne est pleine.
- `jouerJoueur` : Place un pion en tant que joueur pour simuler l'adversaire du Bot.
- `enleverJoueur` : Enlève les cases simulées pour le joueur dans le parcours en profondeur.
- `verifierLigne` : Vérifie si un joueur a complété une ligne de 4, utilisée par `jeuTermine`.

## Auteur

Projet scolaire pour l'école des Mines de Saint-Etienne.  
[Martin RABIER](https://github.com/MartinRabier) @MartinRabier
[Tristan Panhelleux](https://github.com/tristanplx) @tristanplx


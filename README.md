# ProjetP4pse
##Projet Puissance 4
Ce projet implémente un jeu de Puissance 4 en utilisant des sockets pour permettre la communication entre un serveur et plusieurs clients. Le jeu supporte les modes de jeu Humain vs Humain, Humain vs Robot et Robot vs Robot. Le niveaux des robots est choisie par l'utilisateur.

##Structure du Projet
Le projet est composé des fichiers suivants :

serveur.c : Contient le code du serveur qui gère les connexions des clients et orchestre les parties.
client.c : Contient le code du client qui permet à un utilisateur de se connecter au serveur et de jouer au jeu.
jeu.c : Contient les fonctions liées à la logique du jeu (initialisation de la grille, vérification des victoires, etc.).
ordinateur.c : Contient les fonctions utilisées pour le jeu contre un bot, y compris l'algorithme Minimax pour choisir les meilleurs coups.


##Compilation

Pour compiler ce projet, utilisez gcc :
1. Dans un premier terminal serveur, se placer dans le dossier serveur. Pour éxécuter le fichier utiliser:
   '''
   make
   '''

Démarrer le serveur
Pour démarrer le serveur, exécutez la commande suivante :

bash
Copier le code
./serveur <port>
Où <port> est le numéro de port sur lequel le serveur écoutera les connexions des clients.

Démarrer un client
Pour démarrer un client, exécutez la commande suivante :

bash
Copier le code
./client <adresse_serveur> <port>
Où <adresse_serveur> est l'adresse IP du serveur et <port> est le numéro de port sur lequel le serveur est en écoute.

Exemple
Démarrez le serveur :
bash
Copier le code
./serveur 12345
Démarrez deux clients (dans deux terminaux différents) :
bash
Copier le code
./client 127.0.0.1 12345
Fonctionnalités
Mode de Jeu : Le serveur demande aux clients de choisir un mode de jeu (classique ou contre un robot).
Grille de Jeu : La grille de jeu est affichée et mise à jour après chaque coup.
Vérification de Victoire : Le jeu vérifie automatiquement les conditions de victoire après chaque coup.
Mode Robot : Un client peut choisir de jouer contre un robot. Le robot utilise l'algorithme Minimax pour choisir ses coups.
Fichiers et Fonctions Clés
serveur.c
main : Initialisation du serveur, gestion des connexions des clients, et orchestration des parties.
changerModeJeu : Demande aux clients de choisir le mode de jeu et le niveau du robot si applicable.
sessionClient : Gère une session de jeu entre deux clients.
client.c
main : Initialise le client, se connecte au serveur et gère l'interaction avec le serveur.
choisirModeDeJeu : Permet au client de choisir le mode de jeu.
jouer : Gère le déroulement d'une partie pour le client.
jeu.c
afficherGrille : Affiche la grille de jeu.
initialiserGrille : Initialise la grille de jeu.
ajouterPion : Ajoute un pion dans la grille.
verifierVictoire : Vérifie les conditions de victoire.
grillePleine : Vérifie si la grille est pleine.
ordinateur.c
meilleurCoup : Utilise l'algorithme Minimax pour choisir le meilleur coup pour le robot.
minimax : Algorithme Minimax pour évaluer les coups.
evaluerScore : Évalue le score de la grille actuelle.
jeuTermine : Vérifie si le jeu est terminé.
Auteur
Ce projet a été développé par [Votre Nom].

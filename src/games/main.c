#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include <piece.h>
#include <game.h>
#include "displayV1.h"
#include "rush-hour.h"
#include "anerouge.h"
#include "utils.h"
#include "strategies.h"

int rules = -1; // determine le type du jeu en cours pour des fonctions qui en dépendents (comme display)

int main(int argc, char* argv[]) {
	char 	cmd[20]; // contiendra l'input de l'utilisateur
	int 	cmd_target;
	int 	cmd_direction;
	int 	cmd_distance;
	game	currentGame;
	void	(*display)(game);
	game	(*getGame)();
	bool	(*game_over)(cgame);
	bool	use_solveur;

	for (int j = 0; j < 20; j++) cmd[j] = '\0';
	
	use_solveur = false;
	display = NULL;
	getGame = NULL;
	for (int i = 1; i < argc;i++) {
		if (streq(argv[i],"-nocolor")) {
			printf("#Affichage simplifie sans couleur\n");
			display = &simpleDisplay;
		} else if (streq(argv[i],"-text")) {
			printf("#Affichage minimaliste\n");
			display = &textDisplay;
		} else if (streq(argv[i],"-anerouge")){
			printf("Lancement du jeu de l\'Ane rouge\n");
			getGame = &AR_getGame;
			game_over = &game_over_ar;
			rules = 1;
		} else if (streq(argv[i],"-rushhour")){
			printf("Lancement du jeu Rush-Hour\n");
			getGame = &RH_getGame;
			game_over = &game_over_hr;
			rules = 0;
		} else if (streq(argv[i],"-solveur")){
			printf("Utilisation du solveur\n");
			use_solveur = true;
		}
	}
	
	if (getGame == NULL) {
		printf("Liste des arguments possibles :\n-anerouge : Ane rouge\n-rushhour : Rush-Hour\n");
		exit(0);
	}
	
	if (display == NULL) {
		printf("#Si votre terminal ne permet pas l'utilisation de code ANSI, utilisez l'argument \"-nocolor\" ou \"-text\"\n");
		display = &gridDisplay;
	}
	srand((unsigned)time(NULL));
	
	newGame: // Point de retour pour recommencer une partie
	
	currentGame = (getGame)();
	
	// Debut du jeu
	while (!streq(cmd,"q")) { // tant qu'on n'entre pas "exit", boucle le programme
		// Affichage de la grille
		(*display)(currentGame);
		// attente de la demande de l'utilisateur
		for (int j = 0; j < 20; j++) cmd[j] = '\0'; // vidage de cmp (inutile?)
		printf("Entrez votre commande : ");
		if (!use_solveur) fgets(cmd, 20, stdin);
		
		if ((use_solveur && brutStrategy(currentGame, game_over, &cmd_target, &cmd_direction, &cmd_distance))|| readCommand(cmd, &cmd_target, &cmd_direction, &cmd_distance)) { //si la commande est correcte
			printf("Commande : deplacer la piece %d de %d case(s) dans la direction %i\n", cmd_target, cmd_distance, cmd_direction);
			/*Déroulement d'un tour du jeu*/
			if (play_move(currentGame, cmd_target, cmd_direction, cmd_distance)) {	
				if ((*game_over)(currentGame)) {
					(*display)(currentGame); // on affiche la partie terminé
					printf("%sPartie finie en %d mouvement%s !%s\n Appuyer sur entree pour rejouer ! ",KGRN2 ,game_nb_moves(currentGame), ((game_nb_moves(currentGame)<2)?"":"s"), KNRM);
					fgets(cmd, 20, stdin);
					delete_game(currentGame);
					goto newGame;
				}
			} else {
				//Si l'action ne peut pas être réalisé par le play_move
				printf("\t%sAction impossible%s\n", KRED, KNRM);
			}
			/*Fin du tour*/
		} else if (cmd[0] != '\0' && !streq(cmd,"r") && !streq(cmd,"q")) { //usage si la commande est incorrecte et qu'elle n'est pas un "exit"
			printf("usage : <numeros piece> <up/left/down/right> <distance>\nAttention certaines touches, commes les fleches, peuvent changer la commande envoyee\n");
		} else if (streq(cmd,"r")) { //Si la commande est "r" on relance une partie
			printf("\n\nNouvelle partie\n");
			delete_game(currentGame);
			goto newGame;
		}
	}
	delete_game(currentGame);
	return EXIT_SUCCESS;
}

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include <piece.h>
#include <game.h>
#include <displayV1.h>
#include <rush-hour.h>
#include "anerouge.h"
#include <utils.h>

int main(int argc, char* argv[]) {
	char 	cmd[20]; // contiendra l'input de l'utilisateur
	int 	cmd_target;
	int 	cmd_direction;
	int 	cmd_distance;
	game	currentGame;
	void	(*display)(game);
	game	(*getGame)();
	
	printf("#Si votre terminal ne permet pas l'utilisation de code ANSI, utilisez l'argument \"-nocolor\" ou \"-text\"\n");
	display = &GridDisplay;
	getGame = &RH_getGame;
	for (int i = 1; i < argc;i++) {
		if (streq(argv[i],"-nocolor")) {
			printf("#Affichage simplifié sans couleur\n");
			display = &SimpleDisplay;
		} else if (streq(argv[i],"-text")) {
			printf("#Affichage minimaliste\n");
			display = &TextDisplay;
		} else if (streq(argv[i],"-anerouge")){
			getGame = &AR_getGame;
		}
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
		fgets(cmd, 20, stdin);
		//cmd[0] = 'r';
		if (readCommand(cmd, &cmd_target, &cmd_direction, &cmd_distance)) { //si la commande est correcte
			printf("Commande : deplacer la piece %d de %d case(s) dans la direction %i\n", cmd_target, cmd_distance, cmd_direction);
			/*Déroulement d'un tour du jeu*/
			if (play_move(currentGame, cmd_target, cmd_direction, cmd_distance)) {	
				if (game_over_hr(currentGame)) {
					(*display)(currentGame); // on affiche la partie terminé
					printf("%sPartie finie en %d mouvement%s !%s\n Appuyer sur entrée pour rejouer ! ",KGRN2 ,game_nb_moves(currentGame), ((game_nb_moves(currentGame)<2)?"":"s"), KNRM);
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
			printf("usage : <numeros piece> <up/left/down/right> <distance>\nAttention certaines touches, commes les flèches, peuvent changer la commande envoyée\n");
		} else if (streq(cmd,"r")) { //Si la commande est "r" on relance une partie
			printf("\n\nNouvelle partie\n");
			delete_game(currentGame);
			goto newGame;
		}
	}
	delete_game(currentGame);
	return EXIT_SUCCESS;
}

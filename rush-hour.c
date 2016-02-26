#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "piece.h"
#include "game.h"

char *dir_c[] = {"up", "left", "down", "right"}; //Uniquement utile pour comparer avec l'input

/*
Retourne true si les 2 chaines sont exactement identiques.
*/
bool streq(char* s1, char* s2) {
	int i = 1;
	if (s1[0] != s2[0]) return false;
	while (s1[i] != '\0' && s2[i] != '\0' && i < 20) {
		if (s1[i] != s2[i]) return false;
		i++;
	}
	return true;
}

/*
décompose le char* cmd pour y retrouver les 3 arguments utiles :
la piece ciblé, la direction du mouvement et la distance a parcourir.
Renvoie vrai si elle trouve les 3 arguments correctement, faux sinon.
*/
bool readCommand(char *cmd, int* target, int* direction, int* distance) {
	char str[3][20]; // char** pour stocker les 3 aguments en string
	for (int i = 0; i < 3; i++) { 		// initialisation à '\0' sur tout les char
		for (int j = 0; j < 10; j++) {	// |
			str[i][j] = '\0';			// |
		}								// |
	}									// -
	int i = 0, j = 0, k = 0;
	while (cmd[i] != '\0' && i < 20 && j < 3) { // parcours cmd et le stock dans str[j]. A chaque espace j++ donc nouvel argument
		if (cmd[i] == ' ') {					// |
			j++;								// |
			k = -1;//car k incrémenté plus bas	// |
		} else {								// |
			str[j][k] = cmd[i];					// |
		}										// |
		k++;									// |
		i++;									// |
	}											// -
	if (j != 2) return false;// si il n'y a pas 2 espaces retourne faux
	*target = atoi(str[0]);
	*distance = atoi(str[2]);
	*direction = -1;
	for (int i = 0; i < 4; i++) {
		if (streq(str[1], dir_c[i])) *direction = i;
	}
	if (*direction == -1 || *distance == 0) return false; // si la direction ou le mouvement ne sont pas trouvé (ou distance = 0) renvoie faux
	return true;
}

void DEBUG_display(game currentGame, int nb_pieces) {
	printf("Pieces :\n");
	for (int i = 0; i < nb_pieces; ++i) {
		printf("piece %d : x:%d y:%d\n",i ,get_x(game_piece(currentGame, i)), get_y(game_piece(currentGame, i)));
	}
}

int main(int argc, char* argv[]) {
	char 	cmd[20]; // contiendra l'input de l'utilisateur
	int 	cmd_target;
	int 	cmd_direction;
	int 	cmd_distance;
	int 	nb_pieces;
	game	currentGame;
	piece*	pieces;

	newGame:
	// Generation du niveaux 
			/// genere juste une grille de test pour l'instant !
	nb_pieces = 6;
	pieces = malloc(nb_pieces*(sizeof(piece)));
	for (int i = 0; i < nb_pieces; ++i) {
		pieces[i] = new_piece_rh(i,3,true,true);
	}
	currentGame = new_game_hr(nb_pieces, pieces);
	
	// Debut du jeu
	while (!streq(cmd,"exit")) { // tant qu'on n'entre pas "exit", boucle le programme
		// Affichage de la grille
		DEBUG_display(currentGame, nb_pieces); // Fonction d'affichage sommaire uniquement pour vérifier que le programme fonctionne
		
		// attente de la demande de l'utilisateur
		for (int j = 0; j < 20; j++) cmd[j] = '\0'; // vidage de cmp (inutile?)
		printf("Entrez votre commande : ");
		fgets(cmd, 20, stdin);
		//
		//printf("%c[2J", 0x1B); A revoir, pour rafraichir la console a chaque affichage
		if (readCommand(cmd, &cmd_target, &cmd_direction, &cmd_distance)) { //si la commande est correcte
			printf("Commande : deplacer la piece %d de %d case(s) dans la direction %i\n", cmd_target, cmd_distance, cmd_direction);
			/*Déroulement d'un tour du jeu*/
			if (play_move(currentGame, cmd_target, cmd_direction, cmd_distance)) {	
				if (game_over_hr(currentGame)) {
					printf("Partie finie !\n"); // peut-etre ajouter un timer ou une action avant de relancer une partie
					goto newGame;
				}
			} else {
				printf("Action impossible\n");
			}
			/*Fin du tour*/
		} else if (cmd[0] != '\0' && !streq(cmd,"exit")) { //usage si la commande est incorrecte et qu'elle n'est pas un "exit"
			printf("usage : <numeros piece> <up/left/down/right> <distance>\nAttention certaines touches, commes les flèches, peuvent changer la commande envoyée\n");
		}
	}
	return EXIT_SUCCESS;
}
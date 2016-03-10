#include <piece.h>
#include <game.h>
#include "utils.h"
#include "displayV1.h"

game AR_getGame() {
	game	currentGame;
	piece*	pieces;
	int 	nb_pieces;
	/*Code a enlever,creer un jeu vide uniquement pour que ça compile sans erreur*/
	nb_pieces = 3;
	pieces = malloc(nb_pieces*(sizeof(piece)));
	
	currentGame = new_game(5,5,0, pieces);
	
	return currentGame;
}
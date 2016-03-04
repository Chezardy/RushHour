#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "piece.h"
#include "game.h"


int main(int argc, char *argv[]){

	//TEST INEFFICACE POUR L'INSTANT
	
	piece pieces[5];
	pieces[0] = new_piece_rh(0,0,true,true);
	pieces[1] =	new_piece_rh(3,0,true,false);
	pieces[2] =	new_piece_rh(3,4,true,true);
	pieces[3] =	new_piece_rh(3,0,false,true);

	game g = new_game_hr (4, pieces);

	//une boucle serait beaucoup mieux et permettrai de faire plus de tests
 	if(!play_move(g,0,0,1)) return EXIT_FAILURE;
 	if(!play_move(g,3,1,1)) return EXIT_FAILURE;
 	if(!play_move(g,2,2,1)) return EXIT_FAILURE;
 	if(!play_move(g,1,0,1)) return EXIT_FAILURE;

 	delete_game(g);

	return EXIT_SUCCESS;
}
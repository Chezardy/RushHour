#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "piece.h"
#include "game.h"


int main(int argc, char *argv[]){

/*
.....1
...331
.00..1
......
......
22....
*/

	int nb = 4;
	piece pieces[nb];
	pieces[0] = new_piece(1,3,2,1,true,false);
	pieces[1] =	new_piece(5,3,1,3,false,true);
	pieces[2] =	new_piece(0,0,2,1,true,false);
	pieces[3] =	new_piece(3,4,2,1,true,false);

	game g = new_game(6,6,nb, pieces);

 	if(play_move(g,1,1,1)) return EXIT_FAILURE;
 	if(play_move(g,3,3,1)) return EXIT_FAILURE;
 	if(play_move(g,2,1,1)) return EXIT_FAILURE;
 	if(!play_move(g,0,3,2)) return EXIT_FAILURE;

 	delete_game(g);
 	for(int i=0;i<nb;i++)
 		delete_piece(pieces[i]);

	return EXIT_SUCCESS;
}
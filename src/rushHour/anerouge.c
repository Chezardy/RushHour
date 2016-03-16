#include <piece.h>
#include <game.h>
#include "utils.h"
#include "displayV1.h"

game AR_getGame() {
	game	currentGame;
	piece*	pieces;
	int 	nb_pieces;
	nb_pieces = 10;
	pieces = malloc(nb_pieces*(sizeof(piece)));
	pieces[0]=new_piece(1, 3, 2, 2, true, true);
	pieces[1]=new_piece(0, 3, 1, 2, true, true);
	pieces[2]=new_piece(3, 3, 1, 2, true, true);
	pieces[3]=new_piece(0, 1, 1, 2, true, true);
	pieces[4]=new_piece(1, 2, 2, 1, true, true);
	pieces[5]=new_piece(3, 1, 1, 2, true, true);
	pieces[6]=new_piece(1, 1, 1, 1, true, true);
	pieces[7]=new_piece(2, 1, 1, 1, true, true);
	pieces[8]=new_piece(0, 0, 1, 1, true, true);
	pieces[9]=new_piece(3, 0, 1, 1, true, true);
//new_piece (int x, int y, int width, int height, bool move_x, bool move_y)
	
	
	
	currentGame = new_game(4,5,10, pieces);
	
	for (int i=0;i<10;++i) delete_piece(pieces[i]);
	free(pieces);
	
	return currentGame;
}


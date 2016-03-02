#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "piece.h"
#include "game.h"





 int main(int argc, char const *argv[])
{
	piece pieces[5];
	pieces[0]=new_piece_rh(0,0 , true, true);
			pieces[1]	=	new_piece_rh(3, 0, true, false);
				pieces[2]=	new_piece_rh(3, 4, true, true);
				pieces[3]=	new_piece_rh(3, 0, false, true);

					game g =new_game_hr (4, pieces);
//int dir=0;
 if(play_move(g, 0, 0, 1) ){printf("mouvment possible\n");}else{printf("Mouvment impossble\n");}
 if(play_move(g, 3, 1, 1) ){printf("mouvment possible\n");}else{printf("Mouvment impossble\n");}
 if(play_move(g, 2, 2, 1) ){printf("mouvment possible\n");}else{printf("Mouvment impossble\n");}
 if(play_move(g, 1, 0, 1) ){printf("mouvment possible\n");}else{printf("Mouvment impossble\n");}
   printf("*********test intersect************\n");
   if(intersect(pieces[2],pieces[0])){printf("pas d'intersection\n");}else{printf("intersection\n");}
   	if(intersect(pieces[1],pieces[3])){printf("pas d'intersection\n");}else{printf("intersection\n");}
   		if(intersect(pieces[2],pieces[1])){printf("pas d'intersection\n");}else{printf("intersection\n");}
   			if(intersect(pieces[3],pieces[0])){printf("pas d'intersection\n");}else{printf("intersection\n");}

 printf("OK:\n");
return EXIT_SUCCESS;

}
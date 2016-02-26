#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


#include "piece.h"
#include "game.h"
#define SIZE_GAME 6

/*game new_game_hr (int nb_pieces, piece *pieces){
	game g = malloc(SIZE_GAME*sizeof(struct game_s));
	g->tab = malloc(nb_pieces*sizeof(struct piece_s*));
	for(int i=0;i<nb_pieces;i++)
		g->tab[i] = pieces[i];
	g->nb_mouv = 0;
	return g;
}

*/
   void rmpl(piece *pieces,char** tab){
         
     //int** tab=malloc(nb_pieces*sizeof(int*));
	int k=0;
	for(int i=0;i<SIZE_GAME;i++){	
		for(int j=0;j<SIZE_GAME;j++){

			if(get_x(pieces[i])==i && get_y(pieces[i])==j){
				//tab[i]=malloc(nb_pieces*sizeof(int));
			 	if(is_horizontal(pieces[i])){
				 if(is_small(pieces[i])){
				
					tab[i][j]='k';
					tab[i+1][j]='k';
					}else{
					tab[i][j]='k';
					tab[i+1][j]='k';	
					tab[i+2][j]='k';						
					}					
				}
				if(!is_horizontal(pieces[i])){
				 if(is_small(pieces[i])){
					tab[i][j]=k;
					tab[i][j+1]='k';
					}else{
					tab[i][j]='k';
					tab[i+1][j]='k';	
					tab[i+2][j]='k';
					tab[i+3][j]='k';						
					}



			}




		         }
                }
    k++;
    }
	//return tab;
}
void afficherG(int** tab){
	//printf("------------------------------------------------------------\n");
	printf("*************************************************************************************************\n");
	for(int i=0;i<6;i++){
		for(int j=0;j<6;j++){
		if(i==3&&j==3)("*		*		*		*		*		*		* →]\n");
		if(j==3)printf("*		*		*		*		*		*		*\n");
	printf("*		*		*		*		*		*		*\n");
		}	
			
        printf("*************************************************************************************************\n");
	
	}
	
}
 int main (){

int tab[6][6];
  piece pieces[5];
  pieces[0] = new_piece_rh(3, 3, true, true);
  pieces[1] = new_piece_rh(3, 0, true, false);
  pieces[2] = new_piece_rh(4, 1, true, true);
  pieces[3] = new_piece_rh(5, 3, false, false);
  pieces[4] = new_piece_rh(1, 1, false, false);
	 rmpl(pieces,tab);
	afficherG(tab);
	/*for(int i=0;i<6;i++)
		free(tab[i]);	

	free(tab);*/
return EXIT_SUCCESS;
}

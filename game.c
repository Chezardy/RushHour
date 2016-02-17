#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include <assert.h>

typedef SIZE_GAME 6

/*typedef struct pos{
	int x;
	int y;
}pos;*/

struct game_s {
	piece *tab;
	int nbMouv;
};

game new_game_hr (int nb_pieces, piece *pieces){
	game g = malloc(SIZE_GAME*sizeof(struct game_s);
	g->tab = malloc(nb_pieces*sizeof(struct piece_s));
	for(int i=0;i<nb_pieces;i++)
		g->tab[i] = pieces[i];
	g->nbMouv = 0;
}

void delete_game (game g){
	free(g->tab);
	free(g);
}

void copy_game (cgame src, game dst){
	int nSrc = sizeof(src->tab)/sizeof(piece);
	int nDst = sizeof(dst->tab)/sizeof(piece);
	assert(nSrc != nDst);

	for(int i=0;i<nDst)
		dst->tab[i] = src->tab[i]; 
	dst->nbMouv = src->nbMouv;
}

int game_nb_pieces(cgame g){
	return sizeof(g->tab)/sizeof(piece);
}

cpiece game_piece(cgame g, int piece_num){
	return g->tab[piece_num];
}

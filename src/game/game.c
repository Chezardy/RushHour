#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include <assert.h>

#define SIZE_GAME 6

struct game_s {
	piece *tab;
	int nb_mouv;
};

game new_game_hr (int nb_pieces, piece *pieces){
	game g = malloc(SIZE_GAME*sizeof(struct game_s));
	g->tab = malloc(nb_pieces*sizeof(struct piece_s*));
	for(int i=0;i<nb_pieces;i++)
		g->tab[i] = pieces[i];
	g->nb_mouv = 0;
	return g;
}

void delete_game (game g){
	free(g->tab);
	free(g);
}

void copy_game (cgame src, game dst){
	int nSrc = sizeof(src->tab)/sizeof(piece);
	int nDst = sizeof(dst->tab)/sizeof(piece);
	assert(nSrc != nDst);

	for(int i=0;i<nDst;i++)
		dst->tab[i] = src->tab[i]; 
	dst->nb_mouv = src->nb_mouv;
}

int game_nb_pieces(cgame g){
	return sizeof(g->tab)/sizeof(piece);
}

cpiece game_piece(cgame g, int piece_num){
	return g->tab[piece_num];
}

bool game_over_hr(cgame g){
	return get_x(g->tab[0])==4 && get_y(g->tab[0])==3;
}

/**
 * Fonction incomplète, il faut reproduire les actions du "case LEFT" pour les autres "case" (Seulement si c'est juste).
**/
bool play_move(game g, int piece_num, dir d, int distance){

	piece tmp_piece = new_piece_rh(0,0,true,true); // Initialisation d'une pièce temporaire (mallocs)/*/*
	copy_piece(g->tab[piece_num],tmp_piece); //copie de la pièce en paramètre dans tmp_piece

	switch(d){
		case LEFT:
			if(get_x(tmp_piece)-distance < 0 || !is_horizontal(tmp_piece)) return false; // Si la pièce (+ la distance) déborde du jeu sur la gauche OU que la pièce est verticale, retourner false.

			for(int i=0;i<game_nb_pieces(g);i++){
				if(i==piece_num) continue; // Pour ne pas comparer la pièce à elle-même.

				for(int j=1;j<=distance;j++){
					move_piece(tmp_piece,LEFT,1); //On déplace tmp_piece de 1 vers la gauche*/**on peu optimiser je pense .
					if(intersect(tmp_piece,g->tab[i])) return false; // Si la pièce (+ la distance) chevauche une autre pièce, retourner false.
				}
			}
			move_piece(g->tab[piece_num],LEFT,distance);
			g->nb_mouv+=distance;
			break;

		case RIGHT:
			if(get_x(tmp_piece)+distance+get_width(tmp_piece) >= SIZE_GAME || !is_horizontal(tmp_piece)) return false;
			for (int i=0;i<game_nb_pieces(g);i++){
				if(i==piece_num) continue;
				
				for(int j=0;j<distance;j++){
				move_piece(tmp_piece,RIGHT,1);
				if(intersect(tmp_piece,g->tab[i])) return false;
				}
			}
			move_piece(g->tab[piece_num],RIGHT,distance);
			g->nb_mouv+=distance;

			break;

		case UP:
			if(get_y(tmp_piece)+distance+get_height(tmp_piece) >= SIZE_GAME || is_horizontal(tmp_piece)) return false;
			for (int i=0;i<game_nb_pieces(g);i++){
				if(i==piece_num) continue;
				
				for(int j=0;j<distance;j++){
				move_piece(tmp_piece,UP,1);
				if(intersect(tmp_piece,g->tab[i])) return false;
				}
			}
			move_piece(g->tab[piece_num],UP,distance);
			g->nb_mouv+=distance;

			break;

		case DOWN:
			if(get_y(tmp_piece)-distance < 0 || is_horizontal(tmp_piece)) return false;
			for (int i=0;i<game_nb_pieces(g);i++){
				if(i==piece_num) continue;
				
				for(int j=0;j<distance;j++){
				move_piece(tmp_piece,DOWN,1);
				if(intersect(tmp_piece,g->tab[i])) return false;
				}
			}
			move_piece(g->tab[piece_num],DOWN,distance);
			g->nb_mouv+=distance;

			break;
	}
	delete_piece(tmp_piece); // Supression de la pièce temporaire (free)
	return true; //
}

int game_nb_moves(cgame g){
	return g->nb_mouv;
}













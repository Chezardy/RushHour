#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include <assert.h>

struct game_s {
	piece *pieces;
	int nb_mouv;
	int nb_pieces;
};

game new_game_hr (int nb_pieces, piece *pieces){
	game g = malloc(SIZE_GAME*sizeof(struct game_s));
	g->pieces = malloc(nb_pieces*sizeof(struct piece_s*));
	for(int i=0;i<nb_pieces;i++)
		g->pieces[i] = pieces[i];
	g->nb_mouv = 0;
	g->nb_pieces = nb_pieces;
	return g;
}

void delete_game (game g){
	for(int i=0;i<g->nb_pieces;i++)
		delete_piece(g->pieces[i]);
	free(g->pieces);
	free(g);
}

void copy_game (cgame src, game dst){
	int nSrc = sizeof(src->pieces)/sizeof(piece);
	int nDst = sizeof(dst->pieces)/sizeof(piece);
	assert(nSrc != nDst);

	for(int i=0;i<nDst;i++)
		dst->pieces[i] = src->pieces[i]; 
	dst->nb_mouv = src->nb_mouv;
}

int game_nb_pieces(cgame g){
	return g->nb_pieces;
}

cpiece game_piece(cgame g, int piece_num){
	return g->pieces[piece_num];
}

bool game_over_hr(cgame g){
	return get_x(g->pieces[0])==4 && get_y(g->pieces[0])==3;
}

bool play_move(game g, int piece_num, dir d, int distance){
	if ((is_horizontal(g->pieces[piece_num]) && (d == 0 || d == 2))
			|| ((!is_horizontal(g->pieces[piece_num])) && (d == 1 || d == 3))) return false;
	bool move_isAllowed = true;
	piece tmp_piece = new_piece_rh(0,0,true,true); // Initialisation d'une pièce temporaire (mallocs)
	copy_piece(g->pieces[piece_num],tmp_piece); 
	
	for (int i = 0; i < distance; i++) { // On decompose le mouvement en déplacement de une case
		move_piece(g->pieces[piece_num], d, 1);
		if ((get_x(g->pieces[piece_num])+get_width(g->pieces[piece_num])-1 >= SIZE_GAME || get_x(g->pieces[piece_num]) < 0)
				|| (get_y(g->pieces[piece_num])+get_height(g->pieces[piece_num])-1 >= SIZE_GAME || get_y(g->pieces[piece_num]) < 0)) move_isAllowed = false;
		for(int p = 0; p < game_nb_pieces(g);++p) { // On verifie si le mouvement est valide (intersect+depassement grille)
			if (piece_num != p && intersect(g->pieces[piece_num], g->pieces[p])) move_isAllowed = false;
		}
	}
	if (move_isAllowed) {
		for(int p = 0; p < game_nb_pieces(g);++p) {
			if (piece_num != p && intersect(g->pieces[piece_num], g->pieces[p])) printf("Erreur\n");
		}
		g->nb_mouv += distance;
		delete_piece(tmp_piece);
		return true;
	}
	// si le mouvement n'est pas valide on remets la piece a sa place initiale
	copy_piece(tmp_piece, g->pieces[piece_num]);
	delete_piece(tmp_piece);
	return false;
}

/*bool play_move(game g, int piece_num, dir d, int distance){

	piece tmp_piece = new_piece_rh(0,0,true,true); // Initialisation d'une pièce temporaire (mallocs)
	copy_piece(g->pieces[piece_num],tmp_piece); //copie de la pièce en paramètre dans tmp_piece

	switch(d){
		case LEFT:
			if(get_x(tmp_piece)-distance < 0 || !is_horizontal(tmp_piece)) return false; // Si la pièce (+ la distance) déborde du jeu sur la gauche OU que la pièce est verticale, retourner false.

			for(int i=0;i<game_nb_pieces(g);i++){
				if(i==piece_num) continue; // Pour ne pas comparer la pièce à elle-même.

				for(int j=1;j<=distance;j++){
					move_piece(tmp_piece,LEFT,1); //On déplace tmp_piece de 1 vers la gauche.
					if(intersect(tmp_piece,g->pieces[i])) return false; // Si la pièce (+ la distance) chevauche une autre pièce, retourner false.
				}
			}
			move_piece(g->pieces[piece_num],LEFT,distance);
			g->nb_mouv+=distance;
			break;

		case RIGHT:
			if(get_x(tmp_piece)+distance+get_width(tmp_piece) >= SIZE_GAME || !is_horizontal(tmp_piece)) return false;
			for (int i=0;i<game_nb_pieces(g);i++){
				if(i==piece_num) continue;
				
				for(int j=0;j<distance;j++){
				move_piece(tmp_piece,RIGHT,1);
				if(intersect(tmp_piece,g->pieces[i])) return false;
				}
			}
			move_piece(g->pieces[piece_num],RIGHT,distance);
			g->nb_mouv+=distance;

			break;

		case UP:
			if(get_y(tmp_piece)+distance+get_height(tmp_piece) >= SIZE_GAME || is_horizontal(tmp_piece)) return false;
			for (int i=0;i<game_nb_pieces(g);i++){
				if(i==piece_num) continue;
				
				for(int j=0;j<distance;j++){
				move_piece(tmp_piece,UP,1);
				if(intersect(tmp_piece,g->pieces[i])) return false;
				}
			}
			move_piece(g->pieces[piece_num],UP,distance);
			g->nb_mouv+=distance;

			break;

		case DOWN:
			if(get_y(tmp_piece)-distance < 0 || is_horizontal(tmp_piece)) return false;
			for (int i=0;i<game_nb_pieces(g);i++){
				if(i==piece_num) continue;
				
				for(int j=0;j<distance;j++){
				move_piece(tmp_piece,DOWN,1);
				if(intersect(tmp_piece,g->pieces[i])) return false;
				}
			}
			move_piece(g->pieces[piece_num],DOWN,distance);
			g->nb_mouv+=distance;

			break;
	}
	delete_piece(tmp_piece); // Supression de la pièce temporaire (free)
	return true; //
}*/

int game_nb_moves(cgame g){
	return g->nb_mouv;
}

void set_nb_moves(game g, int nb){
	g->nb_mouv = nb;
}














#include <stdio.h>
#include <stdlib.h>
#include "game.h"

game new_game_hr (int nb_pieces, piece *pieces){
	game g = malloc(sizeof(struct game_s));
	if (g != NULL) {
		g->pieces = malloc(nb_pieces*sizeof(piece));
		if (g->pieces != NULL) {
			for(int i=0;i<nb_pieces;i++)
				g->pieces[i] = pieces[i];
			g->nb_mouv = 0;
			g->nb_pieces = nb_pieces;
			g->w = 6;
			g->h = 6;
			return g;
		} else {
			exit(-1);
		}
	} else {
		exit(-1);
	}
}

void delete_game (game g){
	for(int i=0;i<g->nb_pieces;i++)
		delete_piece(g->pieces[i]);
	free(g->pieces);
	free(g);
}

void copy_game (cgame src, game dst){
	for(int i=0;i < src->nb_pieces;i++) copy_piece(src->pieces[i],dst->pieces[i]); 
	dst->nb_mouv = src->nb_mouv;
	dst->nb_pieces = src->nb_pieces;
	dst->w = src->w;
	dst->h = src->h;
}

int game_nb_pieces(cgame g){
	return g->nb_pieces;
}

cpiece game_piece(cgame g, int piece_num){
	
	int a = g->nb_pieces;
	a = a*1;
	if(a < piece_num) exit(-1);
	return g->pieces[piece_num];
}

bool play_move(game g, int piece_num, dir d, int distance){
	if ((!can_move_y(g->pieces[piece_num]) && (d == 0 || d == 2))
			|| ((!can_move_x(g->pieces[piece_num])) && (d == 1 || d == 3))) return false;
	bool move_isAllowed = true;
	piece tmp_piece = new_piece(0,0,0,0,true,true); // Initialisation d'une pièce temporaire (mallocs)
	copy_piece(g->pieces[piece_num],tmp_piece); 
	
	for (int i = 0; i < distance; i++) { // On decompose le mouvement en déplacement de une case
		move_piece(g->pieces[piece_num], d, 1);
		if ((get_x(g->pieces[piece_num])+get_width(g->pieces[piece_num])-1 >= game_width(g) || get_x(g->pieces[piece_num]) < 0)
				|| (get_y(g->pieces[piece_num])+get_height(g->pieces[piece_num])-1 >= game_height(g) || get_y(g->pieces[piece_num]) < 0)) move_isAllowed = false;
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

int game_nb_moves(cgame g){
	return g->nb_mouv;
}

game new_game (int width, int height, int nb_pieces, piece *pieces){
	game g = malloc(sizeof(struct game_s));
	g->pieces = malloc(nb_pieces*sizeof(struct piece_s*));

	for(int i=0;i<nb_pieces;i++)
		g->pieces[i]= new_piece(get_x(pieces[i]),get_y(pieces[i]),get_width(pieces[i]),get_height(pieces[i]),can_move_x(pieces[i]), can_move_y(pieces[i]));

	g->nb_mouv = 0;
	g->nb_pieces = nb_pieces;
	g->w = width;
	g->h = height;
	return g;
}

int game_width(cgame g){
	return g->w;
}

int game_height(cgame g){
	return g->h;
}

int game_square_piece (game g, int x, int y){
	for (int p = 0; p < game_nb_pieces(g); ++p) {
		for(int i = 0; i < get_height(g->pieces[p]); ++i) {
			for(int j = 0; j < get_width(g->pieces[p]); ++j) { 
				if (get_x(g->pieces[p])+i == x && get_y(g->pieces[p])+j == y) return p;
			}
		}
	}
	return -1;
}
















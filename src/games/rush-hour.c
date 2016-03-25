#include <piece.h>
#include <game.h>
#include "utils.h"

#define NB_RANDOMIZES 80 
#define RH_SIZE_GAME 6

bool randomizePiece(piece pieces[], int n, int size_x , int size_y) {
	bool 	finished = false;
	int 	x;
	int 	y;
	bool	small;
	bool	hori;
	int		try;
	try = 0;
	while (!finished) { 
		finished = true;
		//On détermine les coordonées et la taille de la pièce aléatoirement
		x = rand_ab(0,size_x-1);
		y = rand_ab(0,size_y-1);
		small = rand_ab(0,1);

		//On vérifie que ses coordonées sont valides
		if ((x == size_y-1 && y == size_y-1) || (!small && x >= size_y-2 && y >= size_y-2)) finished = false;

		//On vérifie si sa position implique une orientation obligatoire (si trop près d'un bord), sinon elle est déterminée aléatoirement
		if (x == size_x-1) hori = false;
		else if (x == size_x-2 && !small) hori = false;
		else if (y == size_y-1) hori = true;
		else if (y == size_y-2 && !small) hori = true;
		else hori = rand_ab(0,1);
		pieces[n] = new_piece_rh(x,y,small,hori);

		for (int i = 0; i < n; ++i) {
			if (intersect(pieces[n], pieces[i])) finished = false; //Si cette pièce en chevauche une autre déjà placée, on recommence
		}

		//Si la pièce n'est pas valide pour une quelconque raison on la supprime
		if (!finished) {
			delete_piece(pieces[n]);
		}
		if (!finished && try++>100) return false; //Timeout pour éviter que le programme ne boucle à l'infini
	}
	return true;
}

game RH_getGame() {
	game	currentGame;
	piece*	pieces;
	bool	level_isCorrect;
	int		difficulty;
	int 	nb_pieces;
	int		ref_toDelete;
	bool	ref_gameToDelete;

	//Génération du niveau
	currentGame = NULL;
	pieces = NULL;
	ref_gameToDelete = false;
	level_isCorrect = false;
	nb_pieces = 0;
	while (!level_isCorrect) {
		level_isCorrect = true;
		if (ref_gameToDelete) {
			delete_game(currentGame);
			ref_gameToDelete = false;
		}

		//On génère aléatoirement le nombre de pièces
		nb_pieces = rand_ab(7,14);
		pieces = malloc(nb_pieces*(sizeof(piece)));

		pieces[0] = new_piece_rh(4,3,true,true); //On génère la 1ère pièce à l'arrivée (en position de partie finie)
		ref_toDelete = 1;

		//On génère les autres pièces aléatoirement
		for (int i = 1; i < nb_pieces; ++i) {
			if (level_isCorrect) level_isCorrect = randomizePiece(pieces, i, RH_SIZE_GAME, RH_SIZE_GAME);
			if (level_isCorrect) ref_toDelete++;
		}
		
		//Si une pièce n'a pas réussi à se placer,on arrête la génération et on recommence
		if (level_isCorrect) {
			level_isCorrect = false;
			currentGame = new_game(RH_SIZE_GAME,RH_SIZE_GAME,nb_pieces, pieces);
			ref_gameToDelete = true;
			//Le niveau est créé avec un certain nombre de pièces et en position de partie finie
			//On mélange donc la partie en exécutant un grand nombre de play_move aléatoires pour chaque pièce
			for (int r = 0; r < NB_RANDOMIZES; ++r) { 
				for (int i = 0; i < nb_pieces; ++i) {
					if (i == 0) play_move(currentGame, i, 1, 1);//La 1ère pièce ne bouge que vers la gauche
					//On effectue les play_move dans des direction que la pièce peut suivre
					else if (is_horizontal(game_piece(currentGame, i))) play_move(currentGame, i, (rand_ab(0,1)?1:3), rand_ab(0,4));
					else play_move(currentGame, i, (rand_ab(0,1)?0:2), rand_ab(0,4));
				}
			}
			//On vérifie qu'il y ai au moins deux pièces qui bloquent la pièce 0 pour ne pas que la partie soit trop simple
			difficulty = 0;
			for (int i = 1; i < nb_pieces; ++i) {
				for (int y = get_y(game_piece(currentGame, i)); y < get_y(game_piece(currentGame, i))+get_height(game_piece(currentGame, i));++y){
					if (y == 3 && get_x(game_piece(currentGame, 0))+get_width(game_piece(currentGame, 0)) < get_x(game_piece(currentGame, i))+get_width(game_piece(currentGame, i)) ) {
						if (++difficulty >= 2) level_isCorrect = true;
					}
				}
			}
		}
		//Supression du tableau de pièces
		for (int i = 0; i < ref_toDelete; ++i) {
			delete_piece(pieces[i]);
		}
		free(pieces);
	}
	//La création de la partie étant terminée, on remet le compteur de mouvements à 0
	piece* copy_pieces = malloc(sizeof(piece)*nb_pieces);
	for(int i=0;i<nb_pieces;i++){
		copy_pieces[i] = new_piece(0,0,0,0,0,0);
		copy_piece(game_piece(currentGame,i),copy_pieces[i]);
	}

	game copy_game = new_game(RH_SIZE_GAME,RH_SIZE_GAME,nb_pieces,copy_pieces);

	//Supression du tableau de pièces
	for (int i = 0; i < nb_pieces; ++i) {
		delete_piece(copy_pieces[i]);
	}
	free(copy_pieces);
	delete_game(currentGame);
	return copy_game;

}

bool game_over_hr(cgame g){
	return get_x(game_piece(g,0))==4 && get_y(game_piece(g,0))==3;
}
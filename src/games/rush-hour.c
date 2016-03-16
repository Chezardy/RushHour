#include <piece.h>
#include <game.h>
#include "utils.h"

#define RANDOMIZE 80

/*
genere une piece placé aléatoirement sur la grille, qui ne dépasse pas de la grille et qui ne chevauche pas d'autres pieces
Attention, generer trop de pieces sur une grille trop petite peut faire boucler cette fonction !
*/
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
		//On determine ses coordonées et sa taille aléatoirement
		x = rand_ab(0,size_x-1);
		y = rand_ab(0,size_y-1);
		small = rand_ab(0,1);
		// On verifie que ses coordonées soit valides
		if ((x == size_y-1 && y == size_y-1) || (!small && x >= size_y-2 && y >= size_y-2)) finished = false;
		// On verifie si sa position implique une orientation obligatoire (si trop près d'un bord), sinon elle est determiné aléatoirement
		if (x == size_x-1) hori = false;
		else if (x == size_x-2 && !small) hori = false;
		else if (y == size_y-1) hori = true;
		else if (y == size_y-2 && !small) hori = true;
		else hori = rand_ab(0,1);
		pieces[n] = new_piece_rh(x,y,small,hori);
		for (int i = 0; i < n; ++i) { // si cette piece en chevauche une autre déja placé, on recommence
			if (intersect(pieces[n], pieces[i])) finished = false; 
		}
		// si la piece n'est pas valide pour une quelconque raison on la supprime
		if (!finished) {
			delete_piece(pieces[n]);
		}
		if (!finished && try++>100) return false; // timeout pour eviter que le programme ne boucle à l'infini
	}
	return true;
}

game RH_getGame() {
	game	currentGame;
	piece*	pieces;
	bool	level_isCorrect;
	int		difficulty;
	int 	nb_pieces;
	
	// Generation du niveaux 
	level_isCorrect = false;
	nb_pieces = 0;
	while (!level_isCorrect) {
		level_isCorrect = true;
		// Si des pieces sont déjà existantes on les delete
		if (nb_pieces != 0) {
			nb_pieces = 0;
			for (int i = 0; i < nb_pieces; ++i) {
				delete_piece(pieces[i]);
			}
			free(pieces);
		}
		//On genere aléatoirement le nombre de pieces
		nb_pieces = rand_ab(7,14);
		pieces = malloc(nb_pieces*(sizeof(piece)));

		pieces[0] = new_piece_rh(4,3,true,true); // la 1ere piece est à l'arrivé, en position de partie finie
		for (int i = 1; i < nb_pieces; ++i) { // on genere les autres pieces aléatoirement
			if (level_isCorrect) level_isCorrect = randomizePiece(pieces, i, 6, 6);
		}
		// si une piece n'a pas réussi à se placer,on arrete la generation et on recommence
		if (level_isCorrect) {
			level_isCorrect = false;
			currentGame = new_game_hr(nb_pieces, pieces);
			//Le niveaux est créé avec un certain nombre de pieces et en position de partie finie
			// On melange donc la partie en executant un grand nombre de play_move aléatoires pour chaques pieces
			for (int r = 0; r < RANDOMIZE; ++r) { 
				for (int i = 0; i < nb_pieces; ++i) {
					if (i == 0) play_move(currentGame, i, 1, 1);//La 1ere piece ne bouge que vers la gauche, semble améliorer la complexité moyenne des parties
					// on effectue les play_move dans des direction que la piece peut suivre
					else if (is_horizontal(game_piece(currentGame, i))) play_move(currentGame, i, (rand_ab(0,1)?1:3), rand_ab(0,4));
					else play_move(currentGame, i, (rand_ab(0,1)?0:2), rand_ab(0,4));
				}
			}
			// On verifie qu'il y ai au moins deux pieces qui bloque la piece rouge pour ne pas que la partie soit trop simple
			difficulty = 0;
			for (int i = 1; i < nb_pieces; ++i) {
				for (int y = get_y(game_piece(currentGame, i)); y < get_y(game_piece(currentGame, i))+get_height(game_piece(currentGame, i));++y){
					if (y == 3 && get_x(game_piece(currentGame, 0))+get_width(game_piece(currentGame, 0)) < get_x(game_piece(currentGame, i))+get_width(game_piece(currentGame, i)) ) {
						if (++difficulty >= 2) level_isCorrect = true;
					}
				}
			}
		}
	}
	//creation de la partie terminé, on remet le compteur de mouvement à 0
	set_nb_moves(currentGame, 0);
	
	return currentGame;
}
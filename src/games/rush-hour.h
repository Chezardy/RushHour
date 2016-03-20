#ifndef _RH_
#define _RH_

#define RANDOMIZE 80

/*
Modifie le nombre de mouvements de la partie qui ont été comptés automatiquement.
Paramètre nb_moves: nombre de mouvements. 
*/
void set_nb_moves(game g, int nb_moves);

/*
Génère une piece placée aléatoirement sur la grille, qui ne dépasse pas de la grille et qui ne chevauche pas d'autres pièces.
Attention, générer trop de pièces sur une grille trop petite peut faire boucler cette fonction !
*/
bool RH_randomizePiece(piece pieces[], int n, int size_x, int size_y);

/*
Génère une partie correspondant aux critères du jeu rush hour.
*/
game RH_getGame();

/*
Retourne vrai si la pièce 0 du jeu g est à la position finale.
*/
bool game_over_hr(cgame g);

#endif
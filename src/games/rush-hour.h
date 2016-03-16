#ifndef _RH_
#define _RH_

#define RANDOMIZE 80

/*
genere une piece placé aléatoirement sur la grille, qui ne dépasse pas de la grille et qui ne chevauche pas d'autres pieces
Attention, generer trop de pieces sur une grille trop petite peut faire boucler cette fonction !
*/
bool RH_randomizePiece(piece pieces[], int n, int size_x, int size_y);

game RH_getGame();

#endif
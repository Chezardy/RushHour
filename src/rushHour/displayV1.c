#include <piece.h>
#include <game.h>
#include <display.h>

/*
Fonction d'affichage en mode console, dessine une grille représentant le jeu en couleurs.
La grille affiché a une taille 2 fois supérieur à la grille de jeu.
*/
void GridDisplay(game g, int nb_pieces){
	int 	y_scaled;
	int 	x_scaled;
	int 	grid[SIZE_GAME*2][SIZE_GAME*2];
	bool 	nb_displayed[14]; // Utile pour n'afficher le numeros d'une piece qu'une seule fois
	char* 	color[] = {KYEL,KBLU,KMAG,KCYN,KYEL2,KBLU2,KMAG2,KCYN2,KGRN2}; //tableau des couleurs disponibles pour les pieces

	for (int i = 0; i < 14; ++i) nb_displayed[i] = false;
	
	// initialiser le tableau à -1
	for(int x = 0; x < SIZE_GAME*2; ++x){
		for(int y = 0; y < SIZE_GAME*2; ++y){
			grid[y][x] = -1;
		}
	}
	//Remplissage de la grille avec les pieces, a l'echelle 2:1
	for (int i = 0; i < nb_pieces; i++) {
		for (int x = 0; x < get_width(game_piece(g, i)); x++) {
			for (int y = 0; y < get_height(game_piece(g, i)); y++) {
				x_scaled = (get_x(game_piece(g, i))+x)*2;
				y_scaled = (get_y(game_piece(g, i))+y)*2;
				grid[y_scaled][x_scaled] = i;
				grid[y_scaled+1][x_scaled] = i;
				grid[y_scaled][x_scaled+1] = i;
				grid[y_scaled+1][x_scaled+1] = i;
			}
		}
	}
	printf("%sNombre de mouvements joué%s : %d\n",KNRM, ((game_nb_moves(g)<2)?"":"s"), game_nb_moves(g));
	//affichage bord superieur
	printf("%s############################%s\n", KWHT, KNRM);
	for(int y = (SIZE_GAME*2)-1; y >= 0; --y){
		//affichage bord gauche
		printf("%s##%s",KWHT, KNRM);
		//Puis pour chaques cases en largeur
		for(int x = 0; x < (SIZE_GAME*2); ++x){
			//Si c'est une case vide, affichage en noir
			if (grid[y][x] == - 1) printf("%s  ", KNRM);
			//Si c'est la piece 0, affichage en rouge, et si c'est la 1ere case de la piece on affiche son numeros
			else if (grid[y][x] == 0 && !nb_displayed[0]) { printf("%s 0", KRED); nb_displayed[0] = true; }
			else if (grid[y][x] == 0) printf("%s  ", KRED);
			//Si c'est une autre piece, affichage en couleur selon son numeros, 
			//				et si c'est la 1ere case de la piece on affiche son numeros			
			else if (!nb_displayed[grid[y][x]]) {printf("%s%2d", color[grid[y][x]%9], grid[y][x]); nb_displayed[grid[y][x]] = true;}
			else printf("%s  ", color[grid[y][x]%9]);
		}
		//Affichage bord droit (En vert pour la case d'arrivé)
		if (y/2 == 3) printf("%s##%s", KGRN, KNRM);
			else printf("%s##%s", KWHT, KNRM);
		if (y == 7) printf("\tr : Relancer");
			else if (y == 4) printf("\tq : Quitter");
		
		printf("\n");
	}
	//affichage bord inferieur
	printf("%s############################%s\n", KWHT, KNRM);
}

/*
Affichage simplifié, plus petit et sans couleur pour les terminaux ne supportant pas les escape code ANSI
Fonctionnement similaire a DiplayGrid
*/
void SimpleDisplay(game g, int nb_pieces){
	int grid[SIZE_GAME][SIZE_GAME];
	for(int x = 0; x < SIZE_GAME; ++x){
		for(int y = 0; y < SIZE_GAME; ++y){
			grid[y][x] = -1;
		}
	}
	for (int i = 0; i < nb_pieces; i++) {
		for (int x = 0; x < get_width(game_piece(g, i)); x++) {
			for (int y = 0; y < get_height(game_piece(g, i)); y++) {
				grid[get_y(game_piece(g, i))+y][get_x(game_piece(g, i))+x] = i;
			}
		}
	}
	printf("\n");
	printf("###############\n");
	for(int y = SIZE_GAME-1; y >= 0; --y){
		printf("%s#", KNRM);
		for(int x = 0; x < SIZE_GAME; ++x){
			if (grid[y][x] == -1) printf(" -");
			else printf("%2d", grid[y][x]);
		}
		if (y == 3) printf(" =\n");
		else printf(" #\n");
	}
	printf("###############\n");
}

/*
Fontion d'affichage tres simplifié, a priori uniquement utile pour le débuggage
Affiche les coordonnées et les infos de chaques pieces
*/
void TextDisplay(game currentGame, int nb_pieces) {
	printf("Pieces :\n");
	for (int i = 0; i < nb_pieces; ++i) {
		printf("piece %d : x:%d y:%d small:%d hori:%d\n",i ,get_x(game_piece(currentGame, i)), get_y(game_piece(currentGame, i)), 
			is_small(game_piece(currentGame, i)), is_horizontal(game_piece(currentGame, i)));
	}
}

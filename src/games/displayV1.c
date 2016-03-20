#include <piece.h>
#include <game.h>
#include "utils.h"
#include "displayV1.h"

void gridDisplay(game g){
	int 	y_scaled;
	int 	x_scaled;
	int		size_x = game_width(g);
	int		size_y = game_height(g);
	int		nb_pieces = game_nb_pieces(g);

	int **grid = malloc(sizeof(int*)*size_y*2);
	for (int i = 0; i < size_y*2; ++i){
		grid[i] = malloc(sizeof(int)*size_x*2);
	}

	bool nb_displayed[14]; // Utile pour n'afficher le numero d'une pièce qu'une seule fois
	char* color[] = {KYEL,KBLU,KMAG,KCYN,KYEL2,KBLU2,KMAG2,KCYN2,KGRN2}; //Tableau des couleurs disponibles pour les pieces

	for (int i = 0; i < 14; ++i) nb_displayed[i] = false;
	
	// initialiser le tableau à -1
	for(int x = 0; x < size_x*2; ++x){
		for(int y = 0; y < size_y*2; ++y){
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

	//affichage bord superieur
	for(int i=0;i<game_width(g)+1;i++)printf("%s####%s", KWHT, KNRM);
	printf("\n");

	for(int y = (size_y*2)-1; y >= 0; --y){
		//affichage bord gauche
		printf("%s##%s",KWHT, KNRM);

		//Puis pour chaques cases en largeur
		for(int x = 0; x < (size_x*2); ++x){
			//Si c'est une case vide, affichage en noir
			if (grid[y][x] == - 1) printf("%s  ", KNRM);
			//Si c'est la piece 0, affichage en rouge, et si c'est la 1ere case de la piece on affiche son numero
			else if (grid[y][x] == 0 && !nb_displayed[0]) { printf("%s 0", KRED); nb_displayed[0] = true; }
			else if (grid[y][x] == 0) printf("%s  ", KRED);
			//Si c'est une autre piece, affichage en couleur selon son numero, 
			//et si c'est la 1ere case de la piece on affiche son numero			
			else if (!nb_displayed[grid[y][x]]) {printf("%s%2d", color[grid[y][x]%9], grid[y][x]); nb_displayed[grid[y][x]] = true;}
			else printf("%s  ", color[grid[y][x]%9]);
		}
		//Affichage bord droit (En vert pour la case d'arrivée)
		if (y/2 == 3 && rules == 0) printf("%s##%s", KGRN, KNRM);
			else printf("%s##%s", KWHT, KNRM);
		if (y == 6) printf("\tr : Relancer");
			else if (y == 3) printf("\tq : Quitter");
			else if (y == 9) printf("\t%sMouvement%s : %d",KNRM, ((game_nb_moves(g)<2)?"":"s"), game_nb_moves(g));
		
		printf("\n");
	}

	//affichage bord inferieur
	for(int i=0;i<game_width(g)+1;i++){
		if(rules == 1 && i==1){
			printf("%s##%s##%s",KWHT, KGRN, KNRM);
		}else if(rules == 1 && i==2){
			printf("%s####%s", KGRN, KNRM);
		} else if(rules == 1 && i==3){
			printf("%s##%s##%s", KGRN, KWHT,KNRM);
		} else {
			printf("%s####%s", KWHT, KNRM);
		}
	}	
	printf("\n");
	for (int i = 0; i < size_y*2; ++i){
		free(grid[i]);
	}
	free(grid);
}

void simpleDisplay(game g){
	int		size_x = game_width(g);
	int		size_y = game_height(g);
	int		nb_pieces = game_nb_pieces(g);
	int 	**grid = malloc(sizeof(int*)*size_y);
	for (int i = 0; i < size_y; ++i){
		grid[i] = malloc(sizeof(int)*size_x);
	}
	for(int x = 0; x < size_x; ++x){
		for(int y = 0; y < size_y; ++y){
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
	for(int i=0;i<game_width(g)+1;i++) printf("##");
	printf("#\n");
	for(int y = size_y-1; y >= 0; --y){
		printf("#");
		for(int x = 0; x < size_x; ++x){
			if (grid[y][x] == -1) printf(" -");
			else printf("%2d", grid[y][x]);
		}
		if (y == 3 && rules == 0) printf(" =\n");
		else printf(" #\n");
	}
	for(int i=0;i<game_width(g)+1;i++){
		if (rules == 1 &&(i == 2 || i == 3)) printf("||");
		else printf("##");
	}
	printf("#\n");
	for (int i = 0; i < size_y; ++i){
		free(grid[i]);
	}
	free(grid);
}

void textDisplay(game g) {
	int		nb_pieces = game_nb_pieces(g);
	printf("Pieces :\n");
	for (int i = 0; i < nb_pieces; ++i) {
		printf("piece %d : x:%d y:%d small:%d hori:%d\n",i ,get_x(game_piece(g, i)), get_y(game_piece(g, i)), 
			is_small(game_piece(g, i)), is_horizontal(game_piece(g, i)));
	}
}

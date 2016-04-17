#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <piece.h>
#include <game.h>
#include "strategies.h"
#include "rush-hour.h"
#include "anerouge.h"

#define MAX_STATES 	1000000
#define MAX_TRY 	10000

#define DEBUG 0

bool streq(char* s1, char* s2) {
	int 	i = 1;
	
	if (s1[0] != s2[0]) return false;
	while (s1[i] != '\0' && s2[i] != '\0' && i < 20) {
		if (s1[i] != s2[i]) return false;
		i++;
	}
	return true;
}

int rand_ab(int a, int b) {
	return (rand()%((b+1)-a)) + a;
}

void usage(){
	printf("usage : solveur <a|r> <filename>\n");
	exit(1);
}

bool game_equals(game g1, game g2){
	for (int x = 0; x < game_width(g1); ++x){
		for (int y = 0; y < game_height(g1); ++y){
			if (game_square_piece(g1,x,y) != game_square_piece(g2,x,y)) return false;
		}
	}
	return true;
}

int solve(game g, int size_x, int size_y, int nb_pieces, piece* pieces, int rules){
	//On creer 2 tableau de game, de taille MAX_STATES
	game *state1;
	game *state2;
	state1 = malloc(MAX_STATES*(sizeof(game)));
	for (int i = 0; i < MAX_STATES; i++){
		state1[i] = new_game(size_x, size_y, nb_pieces, pieces);
	}
	state2 = malloc(MAX_STATES*(sizeof(game)));
	for (int i = 0; i < MAX_STATES; i++){
		state2[i] = new_game(size_x, size_y, nb_pieces, pieces);
	}
	// Et un tableau de int qui comprend la dernière direction utilisée sur un game pour chaques pieces
	int *prevDir = malloc(MAX_STATES*(sizeof(int))*nb_pieces);
	int nb_states = 1;
	int tmp_nb_states = 0;
	int skip = 1; // pour alterner les tableaux stateX
	int minMove; // Varialbe pour determiner quels game à été finie avec le moins de mouvements possibles
	bool over = false;
	int try = 0;
	game *prevState;
	game *currState;
	while (try++ < MAX_TRY && !over){
		if (DEBUG == 1) printf("nb_states : %d", nb_states);
		//On alterne l'utilisation des tableau, une fois sur deux avec le -1/1
		skip = -skip;
		if (skip == -1) {
			prevState = state1;
			currState = state2;
		} else {
			prevState = state2;
			currState = state1;
		}
		tmp_nb_states = 0;
		//Pour chaques états précedent, pour chaques pièces, pour chaques direction
		for (int i = 0; i < nb_states; ++i){
			for (int p = 0; p < game_nb_pieces(g); ++p){
				for (int d = 0; d < 4; ++d){
					//On verifie que la direction n'est pas l'opposé de celle utilisé précedement sur la piece
					if (nb_states == 1 || (!(prevDir[tmp_nb_states%MAX_STATES+p] == 0 && d == 2)
										&& !(prevDir[tmp_nb_states%MAX_STATES+p] == 1 && d == 3)
										&& !(prevDir[tmp_nb_states%MAX_STATES+p] == 2 && d == 0)
										&& !(prevDir[tmp_nb_states%MAX_STATES+p] == 3 && d == 1))){
						copy_game(prevState[i],currState[tmp_nb_states%MAX_STATES]);
						if (play_move(currState[tmp_nb_states%MAX_STATES],p,d,1)) {
							//Si le mouvement est valide on passe au suivant dans le tableau
							prevDir[tmp_nb_states%MAX_STATES+p] = d;
							tmp_nb_states++;
						}
					}
				}
			}
		}
		if (DEBUG == 1) printf(" (%d potential new states)\n", tmp_nb_states);
		//On vérifie que l'on a pas dépassé MAX_STATES
		if (tmp_nb_states >= MAX_STATES) tmp_nb_states = MAX_STATES-1;
		nb_states = tmp_nb_states;
		minMove = -1;
		//On vérifie pour chaques game si l'une ou plusieurs ne sont pas finie
		for (int i = 0; i < nb_states; ++i){
			if (rules == 0 && game_over_hr(currState[i]) && (minMove > game_nb_moves(g) || minMove == -1)){
				copy_game(currState[i], g);
				over = true;
			} else if (rules == 1 && game_over_ar(currState[i]) && (minMove > game_nb_moves(g) || minMove == -1)){
				copy_game(currState[i], g);
				over = true;
			}
		}
	}
	if (over) return 0;
	else return -1;
}

int main(int argc, char* argv[]){
	int size_x, size_y, nb_pieces;
	piece*	pieces;
	game g;
	int rules;
	//Récuperation des arguments
	if (argc != 3) usage();
	if (streq(argv[1],"a")) { 
		if (DEBUG == 1) printf("Ane-rouge\n"); 
		rules = 1;
	} else if (streq(argv[1],"r")) { 
		if (DEBUG == 1) printf("Rushhour\n"); 
		rules = 0; 
	} else {
		usage();
	} 
	//Lecture du fichier config
	if (DEBUG == 1) printf("File : %s\n",argv[2]); 
	FILE* config = NULL;
    config = fopen(argv[2], "r");
    if (config != NULL) {
		char line[128];
		int count = 0;
		while ( fgets ( line, sizeof line, config ) != NULL )
		{
			++count;
			if (DEBUG == 1) printf("%d : %s", count, line);
			if (count == 1){
				if (line[1] == ' '){
					size_x = line[0]-'0';
					size_y = line[2]-'0';
				}
			} else if (count == 2){
				nb_pieces = atoi(line);
				pieces = malloc(nb_pieces*(sizeof(piece)));
			} else {
				if (nb_pieces > 0){
					pieces[count-3] = new_piece(line[0]-'0',line[2]-'0',line[4]-'0',line[6]-'0',line[8]-'0',line[10]-'0');
				}
			}
		}
		fclose ( config );
    } else {
        printf("Impossible d'ouvrir %s", argv[2]);
    }
	g = new_game(size_x, size_y, nb_pieces, pieces);
	if (solve(g, size_x, size_y, nb_pieces, pieces, rules) == 0) printf("%d\n",game_nb_moves(g));
	else printf("-1");
	return EXIT_SUCCESS;
}

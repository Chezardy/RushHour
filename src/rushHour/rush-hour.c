#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "piece.h"
#include "game.h"

#define RANDOMIZE 80

#define SIZE_GAME 6 // A enlever, doit être présent dans game.h à la place

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "piece.h"
#include "game.h"
#define SIZE_GAME 6

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[41;30m"
#define KGRN  "\x1B[42;32m"
#define KWHT  "\x1B[47;37m"

#define KYEL  "\x1B[43;30m"
#define KBLU  "\x1B[44;30m"
#define KMAG  "\x1B[45;30m"
#define KCYN  "\x1B[46;30m"
#define KRED2  "\x1B[101;30m"
#define KGRN2  "\x1B[102;30m"
#define KYEL2  "\x1B[103;30m"
#define KBLU2 "\x1B[104;30m"
#define KMAG2  "\x1B[105;30m"
#define KCYN2  "\x1B[106;30m"

void displayGame(game g, int nb_pieces){
	int grid[SIZE_GAME][SIZE_GAME];
	char* color[] = {KYEL,KBLU,KMAG,KCYN,KYEL2,KBLU2,KMAG2,KCYN2,KGRN2};
	//int nb_tour = game_nb_moves();
	//int colorIndice = 0;
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
	printf("%sNombre de mouvements joué%s : %d\n",KNRM, ((game_nb_moves(g)<2)?"":"s"), game_nb_moves(g));
	printf("%s################%s\n", KWHT, KNRM);
	for(int y = SIZE_GAME-1; y >= 0; --y){
		printf("%s #%s",KWHT, KNRM);
		for(int x = 0; x < SIZE_GAME; ++x){
			if (grid[y][x] == -1) printf("%s -", KNRM);
			else if (grid[y][x] == 0) printf("%s 0", KRED);
			else printf("%s%2d", color[grid[y][x]%9], grid[y][x]);
		}
		if (y == 3) printf("%s #%s", KGRN, KNRM);
		else printf("%s #%s", KWHT, KNRM);
		if (y == 3) printf("\tr : Relancer");
		else if (y == 1) printf("\tq : Quitter");
		printf("\n");
	}
	printf("%s################%s\n", KWHT, KNRM);
}

char *dir_c[] = {"up", "left", "down", "right"}; //Uniquement utile pour comparer avec l'input

/*
Retourne une nombre aléatoire en a et b (compris)
*/
int rand_ab(int a, int b) {
	return (rand()%((b+1)-a)) + a;
}

/*
Retourne true si les 2 chaines sont exactement identiques.
*/
bool streq(char* s1, char* s2) {
	int i = 1;
	if (s1[0] != s2[0]) return false;
	while (s1[i] != '\0' && s2[i] != '\0' && i < 20) {
		if (s1[i] != s2[i]) return false;
		i++;
	}
	return true;
}

/*
décompose le char* cmd pour y retrouver les 3 arguments utiles :
la piece ciblé, la direction du mouvement et la distance a parcourir.
Renvoie vrai si elle trouve les 3 arguments correctement, faux sinon.
*/
bool readCommand(char *cmd, int* target, int* direction, int* distance) {
	char str[3][20]; // char** pour stocker les 3 aguments en string
	for (int i = 0; i < 3; i++) { 		// initialisation à '\0' sur tout les char
		for (int j = 0; j < 10; j++) {	// |
			str[i][j] = '\0';			// |
		}								// |
	}									// -
	int i = 0, j = 0, k = 0;
	while (cmd[i] != '\0' && i < 20 && j < 3) { // parcours cmd et le stock dans str[j]. A chaque espace j++ donc nouvel argument
		if (cmd[i] == ' ') {					// |
			j++;								// |
			k = -1;//car k incrémenté plus bas	// |
		} else {								// |
			str[j][k] = cmd[i];					// |
		}										// |
		k++;									// |
		i++;									// |
	}											// -
	if (j != 2) return false;// si il n'y a pas 2 espaces retourne faux
	*target = atoi(str[0]);
	*distance = atoi(str[2]);
	*direction = -1;
	for (int i = 0; i < 4; i++) {
		if (streq(str[1], dir_c[i])) *direction = i;
	}
	if (*direction == -1 || *distance == 0) return false; // si la direction ou le mouvement ne sont pas trouvé (ou distance = 0) renvoie faux
	return true;
}

void DEBUG_display(game currentGame, int nb_pieces) {
	printf("Pieces :\n");
	for (int i = 0; i < nb_pieces; ++i) {
		printf("piece %d : x:%d y:%d small:%d hori:%d\n",i ,get_x(game_piece(currentGame, i)), get_y(game_piece(currentGame, i)), 
			is_small(game_piece(currentGame, i)), is_horizontal(game_piece(currentGame, i)));
	}
}
/*
genere une piece placé aléatoirement sur la grille, qui ne dépasse pas de la grille et qui ne chevauche pas d'autres pieces
Attention, generer trop de pieces sur une grille trop petite peut faire boucler cette fonction !
*/
void randomizePiece(piece pieces[], int n, int m) {
	bool 	finished = false;
	int 	x;
	int 	y;
	bool	small;
	bool	hori;
	int		try;
	try = 0;
	while (try++>100 || !finished) {
		finished = true;
		x = rand_ab(0,SIZE_GAME-1);
		y = rand_ab(0,SIZE_GAME-1);
		small = rand_ab(0,1);
		if (x == SIZE_GAME-1) hori = false;
		else if (x == SIZE_GAME-2 && !small) hori = false;
		else if (y == SIZE_GAME-1) hori = true;
		else if (y == SIZE_GAME-2 && !small) hori = true;
		else hori = rand_ab(0,1);
		if ((x == 5 && y == 5) || (!small && x >= 4 && y >= 4)) finished = false;
		pieces[n] = new_piece_rh(x,y,small,hori);
		for (int i = 0; i < n; ++i) { // si cette piece en chevauche une autre déja placé, on recommence
			if (intersect(pieces[n], pieces[i])) finished = false; 
		}
		//if ((get_x(pieces[n])+get_width(pieces[n])-1 >= SIZE_GAME || get_x(pieces[n]) < 0)
			//	|| (get_y(pieces[n])+get_height(pieces[n])-1 >= SIZE_GAME || get_y(pieces[n]) < 0)) finished = false;
	
		if (!finished) {
			delete_piece(pieces[n]);
		}
	}
}

int main(int argc, char* argv[]) {
	char 	cmd[20]; // contiendra l'input de l'utilisateur
	int 	cmd_target;
	int 	cmd_direction;
	int 	cmd_distance;
	int 	nb_pieces;
	game	currentGame;
	piece*	pieces;
	bool	level_isCorrect;
	int		difficulty;
	srand((unsigned)time(NULL)); 
	newGame:
	// Generation du niveaux 
			/// Certaine piece semble se chevaucher dans certain cas (Après les play_move ?), il faudra faire des tests lorsque la fonction d'affichage sera finie
	level_isCorrect = false;
	nb_pieces = 0;

	while (!level_isCorrect) { 
		if (nb_pieces == 0) {
			nb_pieces = rand_ab(7,11);
			pieces = malloc(nb_pieces*(sizeof(piece)));
		} else {
			for (int i = 0; i < nb_pieces; ++i) { // on genere les autres pieces aléatoirement
				delete_piece(pieces[i]);
			}
		}
		pieces[0] = new_piece_rh(4,3,true,true); // la 1ere piece est à l'arrivé, en position de partie finie
		for (int i = 1; i < nb_pieces; ++i) { // on genere les autres pieces aléatoirement
			randomizePiece(pieces, i, nb_pieces);
		}
		level_isCorrect = false;
		currentGame = new_game_hr(nb_pieces, pieces);
		for (int r = 0; r < RANDOMIZE; ++r) { // et pour finir on fait faire a chaque piece un certain nombre de mouvements aléatoires pour mélanger la grille
			for (int i = 0; i < nb_pieces; ++i) {
				if (i == 0) play_move(currentGame, i, 1, 1);
				else if (is_horizontal(game_piece(currentGame, i))) play_move(currentGame, i, (rand_ab(0,1)?1:3), rand_ab(0,5));
				else play_move(currentGame, i, (rand_ab(0,1)?0:2), rand_ab(0,5));
			}
		}
		difficulty = 0;
		for (int i = 1; i < nb_pieces; ++i) { // verification si il y a au moins une piece devant la rouge
			for (int y = get_y(game_piece(currentGame, i)); y < get_y(game_piece(currentGame, i))+get_height(game_piece(currentGame, i));++y){
				if (y == 3 && get_x(game_piece(currentGame, 0))+get_width(game_piece(currentGame, 0)) < get_x(game_piece(currentGame, i))+get_width(game_piece(currentGame, i)) ) {
					if (++difficulty >= 2) level_isCorrect = true;
				}
			}
		}
	}
	set_nb_moves(currentGame, 0);
	// Debut du jeu
	while (!streq(cmd,"q")) { // tant qu'on n'entre pas "exit", boucle le programme
		// Affichage de la grille
		//DEBUG_display(currentGame, nb_pieces); // Fonction d'affichage sommaire uniquement pour vérifier que le programme fonctionne
		displayGame(currentGame, nb_pieces);
		// attente de la demande de l'utilisateur
		for (int j = 0; j < 20; j++) cmd[j] = '\0'; // vidage de cmp (inutile?)
		printf("Entrez votre commande : ");
		fgets(cmd, 20, stdin);
		//
		//printf("%c[2J", 0x1B); A revoir, pour rafraichir la console a chaque affichage
		if (readCommand(cmd, &cmd_target, &cmd_direction, &cmd_distance)) { //si la commande est correcte
			printf("Commande : deplacer la piece %d de %d case(s) dans la direction %i\n", cmd_target, cmd_distance, cmd_direction);
			/*Déroulement d'un tour du jeu*/
			if (play_move(currentGame, cmd_target, cmd_direction, cmd_distance)) {	
				if (game_over_hr(currentGame)) {
					//printf("Partie finie !\n"); // peut-etre ajouter un timer ou une action avant de relancer une partie
					printf("Partie finie en %d mouvement%s !\n Appuyer sur entrée pour rejouer", game_nb_moves(currentGame), ((game_nb_moves(currentGame)<2)?"":"s"));
					fgets(cmd, 20, stdin);
					goto newGame;
				}
			} else {
				printf("\t%sAction impossible%s\n", KRED, KNRM);
			}
			/*Fin du tour*/
		} else if (cmd[0] != '\0' && !streq(cmd,"r") && !streq(cmd,"q")) { //usage si la commande est incorrecte et qu'elle n'est pas un "exit"
			printf("usage : <numeros piece> <up/left/down/right> <distance>\nAttention certaines touches, commes les flèches, peuvent changer la commande envoyée\n");
		} else if (streq(cmd,"r")) {
			printf("\n\nNouvelle partie\n");
			goto newGame;
		}
	}
	return EXIT_SUCCESS;
}
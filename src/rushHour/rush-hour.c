#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include <piece.h>
#include <game.h>
#include "displayV1.h"

#define RANDOMIZE 80


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
	int 	i = 1;
	
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
	char 	str[3][20]; // char** pour stocker les 3 aguments en string
	int 	i = 0, j = 0, k = 0;

	for (int i = 0; i < 3; i++) { // initialisation à '\0' sur tout les char
		for (int j = 0; j < 10; j++) {
			str[i][j] = '\0';
		}
	}
	while (cmd[i] != '\0' && i < 20 && j < 3) { // parcours cmd et le stock dans str[j]. A chaque espace j++ donc nouvel argument
		if (cmd[i] == ' ') {
			j++;
			k = -1;//car k incrémenté plus bas
		} else {
			str[j][k] = cmd[i];
		}
		k++;
		i++;
	}
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

/*
genere une piece placé aléatoirement sur la grille, qui ne dépasse pas de la grille et qui ne chevauche pas d'autres pieces
Attention, generer trop de pieces sur une grille trop petite peut faire boucler cette fonction !
*/
bool randomizePiece(piece pieces[], int n, int m) {
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
		x = rand_ab(0,SIZE_GAME-1);
		y = rand_ab(0,SIZE_GAME-1);
		small = rand_ab(0,1);
		// On verifie que ses coordonées soit valides
		if ((x == 5 && y == 5) || (!small && x >= 4 && y >= 4)) finished = false;
		// On verifie si sa position implique une orientation obligatoire (si trop près d'un bord), sinon elle est determiné aléatoirement
		if (x == SIZE_GAME-1) hori = false;
		else if (x == SIZE_GAME-2 && !small) hori = false;
		else if (y == SIZE_GAME-1) hori = true;
		else if (y == SIZE_GAME-2 && !small) hori = true;
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
	void	(*display)(game,int);

	if (argc > 1 && streq(argv[1],"-nocolor")) {
		printf("#Affichage simplifié sans couleur\n");
		display = &SimpleDisplay;
	} else if (argc > 1 && streq(argv[1],"-text")) {
		printf("#Affichage minimaliste\n");
		display = &TextDisplay;
	} else {
		printf("#Si votre terminal ne permet pas l'utilisation de code ANSI, utilisez l'argument \"-nocolor\" ou \"-text\"\n");
		display = &GridDisplay;
	} 
	
	srand((unsigned)time(NULL));
	
	newGame: // Point de retour pour recommencer une partie
	
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
			if (level_isCorrect) level_isCorrect = randomizePiece(pieces, i, nb_pieces);
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
	
	// Debut du jeu
	while (!streq(cmd,"q")) { // tant qu'on n'entre pas "exit", boucle le programme
		// Affichage de la grille
		(*display)(currentGame, nb_pieces);
		// attente de la demande de l'utilisateur
		for (int j = 0; j < 20; j++) cmd[j] = '\0'; // vidage de cmp (inutile?)
		printf("Entrez votre commande : ");
		fgets(cmd, 20, stdin);
		if (readCommand(cmd, &cmd_target, &cmd_direction, &cmd_distance)) { //si la commande est correcte
			printf("Commande : deplacer la piece %d de %d case(s) dans la direction %i\n", cmd_target, cmd_distance, cmd_direction);
			/*Déroulement d'un tour du jeu*/
			if (play_move(currentGame, cmd_target, cmd_direction, cmd_distance)) {	
				if (game_over_hr(currentGame)) {
					(*display)(currentGame, nb_pieces); // on affiche la partie terminé
					printf("%sPartie finie en %d mouvement%s !%s\n Appuyer sur entrée pour rejouer ! ",KGRN2 ,game_nb_moves(currentGame), ((game_nb_moves(currentGame)<2)?"":"s"), KNRM);
					fgets(cmd, 20, stdin);
					delete_game(currentGame);
					goto newGame;
				}
			} else {
				//Si l'action ne peut pas être réalisé par le play_move
				printf("\t%sAction impossible%s\n", KRED, KNRM);
			}
			/*Fin du tour*/
		} else if (cmd[0] != '\0' && !streq(cmd,"r") && !streq(cmd,"q")) { //usage si la commande est incorrecte et qu'elle n'est pas un "exit"
			printf("usage : <numeros piece> <up/left/down/right> <distance>\nAttention certaines touches, commes les flèches, peuvent changer la commande envoyée\n");
		} else if (streq(cmd,"r")) { //Si la commande est "r" on relance une partie
			printf("\n\nNouvelle partie\n");
			delete_game(currentGame);
			goto newGame;
		}
	}
	delete_game(currentGame);
	for(int i=0;i<nb_pieces;i++) {
		delete_piece(pieces[i]);
	}
	free(pieces);
	return EXIT_SUCCESS;
}

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include <SDL2/SDL.h>

#include <piece.h>
#include <game.h>
#include "displayV2.h"
#include "rush-hour.h"
#include "anerouge.h"
#include "utils.h"
#include "strategies.h"


int rules = -1; // determine le type du jeu en cours pour les fonctions qui en dépendent (comme display)

typedef void (*funcptr)(void);

int main(int argc, char* argv[]) {
	game			currentGame;
	game			(*getGame)();
	bool			(*game_over)(cgame);
	bool			use_solveur;
	SDL_Window* 	win;
	SDL_Renderer* 	rdr;
	Input 			input;
	unsigned int 	sync; //représente le temps à attendre entre chaque rafraichissement d'affichage
	bool 			quit;
	int				wait_conf;//1:reset, 2:quitter, 3:Fin de partie
	int				target; //représente le numero de la piece sélectionnée
	TTF_Font*		font;
	
	sync = 64;
	wait_conf = 0;
	target = 0;
	//Initialisation des commandes à 0 (Non appuyées)
	input.left = 0;
	input.right = 0;
	input.up = 0;
	input.down = 0;
	input.enter = 0;
	input.erase = 0;
	input.pause = 0;
	input.newGame = 0;
	input.escape = 0;
	input.quit = 0;
	input.mouse_x = 0;
	input.mouse_y = 0;
	input.mouse = 0;
	quit = false;
	use_solveur = false;
	currentGame = NULL;
	getGame = NULL;
	win = NULL;
	rdr = NULL;
	
	srand((unsigned)time(NULL));
	
	//Lecture des arguments
	for (int i = 1; i < argc;i++) {
		if (streq(argv[i],"-anerouge")){
			printf("Lancement du jeu Ane Rouge ");
			getGame = &AR_getGame;
			game_over = &game_over_ar;
			rules = 1;
			win = initWindow("Ane Rouge");
			rdr = initRenderer(win);
		} else if (streq(argv[i],"-rushhour")){
			printf("Lancement du jeu Rush Hour ");
			getGame = &RH_getGame;
			game_over = &game_over_hr;
			rules = 0;
			win = initWindow("Rush Hour");
			rdr = initRenderer(win);
		} if (streq(argv[i],"-solveur")){
			printf("avec le solveur");
			use_solveur = true;
		}
	}
	printf("\n");
	
	if (getGame == NULL) {
		printf("Liste des arguments possibles :\n-anerouge : Ane rouge\n-rushhour : Rush Hour\n");
		exit(0);
	}
	//Initialisation Police de caractère.
	font = TTF_OpenFont("OpenSans-Regular.ttf", 40);
	if (font == NULL) {
		printf("Erreur SDL_ttf : %s\n", TTF_GetError());
		exit(1);
	}
	
	// Boucle principale du jeu 
	while (!quit){
		if (currentGame == NULL) currentGame = (getGame)();
		
		gestionInputs(&input);
		
		SDL_Display(currentGame, rdr, font, wait_conf);
		
		//Commandes ULDR (fonctionne si pas de popup à l'écran)
		if (!use_solveur){
			if (input.left == 1 && wait_conf == 0) {
				play_move(currentGame,target,LEFT,1);
			}
			if (input.right == 1 && wait_conf == 0) {
				play_move(currentGame,target,RIGHT,1);
			}
			if (input.up == 1 && wait_conf == 0) {
				play_move(currentGame,target,UP,1);
			}
			if (input.down == 1 && wait_conf == 0) {
				play_move(currentGame,target,DOWN,1);
			}
		} else {
			if (wait_conf == 0) 
				brutStrategy(currentGame, game_over);
		}
		//Click souris
		if (input.mouse == 1){
			int tmp_x = input.mouse_x/(SCREEN_Y/game_height(currentGame)), tmp_y = (SCREEN_Y-input.mouse_y)/(SCREEN_Y/game_height(currentGame));
			if (tmp_y < game_height(currentGame) && tmp_x < game_width(currentGame) && game_square_piece(currentGame, tmp_x,tmp_y) != -1) 
					target = game_square_piece(currentGame,  input.mouse_x/(SCREEN_Y/game_height(currentGame)),(SCREEN_Y-input.mouse_y)/(SCREEN_Y/game_height(currentGame)));
		}
		//Quitter Partie
		if (wait_conf == 2 && input.quit == 0 && input.enter == 1){
			quit = true;
		}
		if (input.quit == 1 && wait_conf == 0) wait_conf = 2;
		//Reset partie
		if (input.newGame == 1 && wait_conf == 0) wait_conf = 1;
		if (wait_conf == 1 && input.newGame == 0 && input.enter == 1){
			delete_game(currentGame);
			currentGame = NULL;
			wait_conf = 0;
		}
		//Nouvelle Partie
		if  (currentGame != NULL && (*game_over)(currentGame)){
			wait_conf = 3;
		}
		if (wait_conf == 3 && input.enter == 1) {
			delete_game(currentGame);
			currentGame = NULL;
			wait_conf = 0;
		}
		//Quitter popup
		if (input.escape == 1 && wait_conf == 3) quit = true;
		if (input.escape == 1 && wait_conf != 0) wait_conf = 0;
		if (!use_solveur || wait_conf != 0){
			delay(sync);
			sync = SDL_GetTicks() + 64;
		}
	}
	TTF_CloseFont(font);
	SDL_Free(win,rdr);
	delete_game(currentGame);
	
	return EXIT_SUCCESS;
}

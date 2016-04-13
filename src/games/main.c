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
	unsigned int 	sync;
    bool 			quit;
	int				wait_conf;//1:reset, 2:quitter, 3:Fin de partie
	int				target;
	TTF_Font*		font;
	
	sync = 64;
	wait_conf = 0;
	target = 0;
	input.down = 0; // à faire pour tout l'input ?
	input.enter = 0;
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
			printf("avec le solveur\n");
			use_solveur = true;
		}
	}
	if (getGame == NULL) {
		printf("Liste des arguments possibles :\n-anerouge : Ane rouge\n-rushhour : Rush Hour\n");
		exit(0);
	}
	//Initialisation Police de caractère.
	font = TTF_OpenFont("OpenSans-Regular.ttf", 40);
	//printf("font main : %p\n", font); //sert au débuggage
	if (font == NULL) {
		printf("Erreur SDL_ttf : %s\n", TTF_GetError());
		exit(1);
	}
	
    // Boucle principale du jeu 
    while (!quit){
		if (currentGame == NULL) currentGame = (getGame)();
		
        gestionInputs(&input);
        
		SDL_Display(currentGame, rdr, font, wait_conf);
		
		//Commandes ULDR
		if (!use_solveur){
			if (input.left == 1) {
				play_move(currentGame,target,LEFT,1);
				//printf("LEFT\n");
			}
			if (input.right == 1) {
				play_move(currentGame,target,RIGHT,1);
				//printf("RIGHT\n");
			}
			if (input.up == 1) {
				play_move(currentGame,target,UP,1);
				//printf("UP\n");
			}
			if (input.down == 1) {
				play_move(currentGame,target,DOWN,1);
				//printf("DOWN\n");
			}
		} else {
			if (wait_conf == 0) 
				brutStrategy(currentGame, game_over);
		}
		//Click souris
		/*int coord_X = input.mouse_x/(SCREEN_Y/game_height(currentGame));			//Pour le printf qui sert à débugguer
		int coord_Y = (SCREEN_Y-input.mouse_y)/(SCREEN_Y/game_height(currentGame));	//De même
		*/
		if (input.mouse == 1){
			if (game_square_piece(currentGame, input.mouse_x/(SCREEN_Y/game_height(currentGame)),(SCREEN_Y-input.mouse_y)/(SCREEN_Y/game_height(currentGame))) != -1) 
					target = game_square_piece(currentGame,  input.mouse_x/(SCREEN_Y/game_height(currentGame)),(SCREEN_Y-input.mouse_y)/(SCREEN_Y/game_height(currentGame)));
			//printf("%d : %d, p%d\n",coord_X,coord_Y, target);
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

	
	SDL_Free(win,rdr);
	delete_game(currentGame);
	
	return EXIT_SUCCESS;
}

#include <piece.h>
#include <game.h>
#include "utils.h"
#include "displayV2.h"


SDL_Window* initWindow(char* title){
	SDL_Window* win;
	 
		win = SDL_CreateWindow(title,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			SCREEN_X, SCREEN_Y+10,
			SDL_WINDOW_SHOWN);
	
	
 
    if (win == NULL){
        printf("Erreur SDL : Initialisation de la fenetre SDL");
        exit(1);
    }
	return win;
}

SDL_Renderer* initRenderer(SDL_Window* win){
	SDL_Renderer* rdr = NULL;
    rdr = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	//printf("Renderer : %p\n", rdr); //sert au débuggage
    if (rdr == NULL) {
        printf("Erreur SDL : Initialisation du renderer SDL\n");
        exit(1);
    }
	
	if(TTF_Init() < 0) {
		printf("Erreur SDL : %s\n", TTF_GetError());
		exit(1);
	}
	
	return rdr;
}

void SDL_Free(SDL_Window* win, SDL_Renderer* rdr){
	TTF_Quit();
	
    SDL_DestroyRenderer(rdr);
    rdr = NULL;
    SDL_DestroyWindow(win);
    win = NULL;
    SDL_Quit();
}

int color[14][3] = {
	{242,38,19},
	{103,65,114},
	{68,108,179},
	{129,207,224},
	{38,166,91},
	{247,202,24},
	{211,84,0},
	{158, 14 ,64},
	{249,156,18},
	{30,130,76},
	{200,247,197},
	{58,83,155},
	{226,106,106},
	{239,72,54},
};

void drawText(SDL_Renderer* rdr, TTF_Font* font, SDL_Color color, int x, int y, char* txt){
	SDL_Rect rect;
	SDL_Surface* text;
	SDL_Texture *texFont;
	text = TTF_RenderText_Blended(font, txt, color);
	rect.x = x;//(SCREEN_Y/game_height(g))*game_nb_pieces(g);
	rect.y = y;//SCREEN_Y/game_height(g);
	texFont = SDL_CreateTextureFromSurface(rdr, text);
	SDL_QueryTexture(texFont, NULL, NULL, &rect.w, &rect.h);
	rect.x -= rect.w/2;
	rect.y -= rect.h/2;
	SDL_RenderCopy(rdr, texFont, NULL, &rect);
}

void SDL_Display(game g, SDL_Renderer* rdr, TTF_Font* font, int popup){
	SDL_Rect rect;
	double px = SCREEN_X/100, py = SCREEN_Y/100;
	SDL_Color fontColor = {255, 255, 255};

	rect.w = (SCREEN_Y/game_height(g));
	rect.h = (SCREEN_Y/game_height(g));

	SDL_SetRenderDrawColor(rdr, 192,192,192, 255);
	SDL_RenderClear(rdr);
	SDL_SetRenderDrawColor(rdr, 0,255,127, 255);

	if(rules==0){//pour la Sortie des piece de Rush hour 
		rect.y = (SCREEN_Y/game_height(g))*2;
		rect.x = (SCREEN_Y/game_height(g))*game_width(g);
		rect.h = (SCREEN_Y/game_height(g));
		rect.w = 10;
		SDL_RenderFillRect(rdr, &rect);
		SDL_SetRenderDrawColor(rdr, 105,105,105, 255);
		rect.y = 0;
		rect.x = (SCREEN_Y/game_height(g))*game_width(g);
		rect.w = 10;
		rect.h = ((SCREEN_Y/game_height(g))*2);
		SDL_RenderFillRect(rdr, &rect);
		rect.y = ((SCREEN_Y/game_height(g))*3);
		rect.x = (SCREEN_Y/game_height(g))*game_width(g);
		rect.w = 10;
		rect.h = ((SCREEN_Y/game_height(g))*3);
		SDL_RenderFillRect(rdr, &rect);
		rect.y = (SCREEN_Y);
		rect.x = 0;
		rect.w = SCREEN_X ;
		rect.h = 10;
		SDL_RenderFillRect(rdr, &rect);
	}

	else if(rules==1){ //pour la Sortie des piece de Ane rouge 

		rect.y = SCREEN_Y;
		rect.x = (SCREEN_Y/game_height(g));
		rect.h = 10;
		rect.w = (SCREEN_Y/game_height(g))*2;
		SDL_RenderFillRect(rdr, &rect);
		SDL_SetRenderDrawColor(rdr, 105,105,105, 255);
		rect.y = 0;
		rect.x = (SCREEN_Y/game_height(g))*game_width(g);
		rect.w = 10;
		rect.h = SCREEN_Y;
		SDL_RenderFillRect(rdr, &rect);
		rect.y = SCREEN_Y;
		rect.x = 0;
		rect.w = (SCREEN_Y/game_height(g));
		rect.h = 10;
		SDL_RenderFillRect(rdr, &rect);
		rect.y = SCREEN_Y;
		rect.x = ((SCREEN_Y/game_height(g))*3);
		rect.w = ((SCREEN_Y/game_height(g))*6);
		rect.h = 10;
		SDL_RenderFillRect(rdr, &rect);
	}
	
	//Affichage des pièces
	for(int i = 0; i < game_nb_pieces(g); ++i){
		SDL_SetRenderDrawColor(rdr, color[i][0],color[i][1],color[i][2], 255);
		rect.x = get_x(game_piece(g,i))*(SCREEN_Y/game_height(g));
		rect.y = (SCREEN_Y - (get_y(game_piece(g,i))*(SCREEN_Y/game_height(g))));
		rect.w = get_width(game_piece(g,i))*(SCREEN_Y/game_height(g));
		rect.h = get_height(game_piece(g,i))*(SCREEN_Y/game_height(g));
		rect.y -= rect.h;
		SDL_RenderFillRect(rdr, &rect);
	}
	
	//Affichage du nombre de mouvements
	char disp_moves[20]; //contiendra l'affichage du nombre de mouvements
	char end_msg[30]; //contiendra le message de fin de partie
	
	sprintf(disp_moves," Mouvements : %d ",game_nb_moves(g));// Convertie le nb_mouv en caractère 
	drawText(rdr, font, fontColor,90*px ,5*py ,disp_moves); //affichage nombre de mouvements 

	//Affichage des règles
	//SCREEN_Y/game_height(g))*game_width(g)+py*10
	drawText(rdr, font, fontColor, 90*px,85*py ,"R : Relancer");
	drawText(rdr, font, fontColor, 90*px ,95*py ,"Q : Quitter");

	if (popup != 0){
		SDL_SetRenderDrawColor(rdr, 50, 50, 50, 170);
		rect.x = 0;
		rect.y = 25*py;
		rect.w = SCREEN_X;
		rect.h = 50*py;
		SDL_RenderFillRect(rdr, &rect);
		if (popup == 1){
			drawText(rdr, font, fontColor,50*px ,50*py-SCREEN_Y/8 ,"Voulez-vous lancer une nouvelle partie ?");
		} else if (popup == 2){
			drawText(rdr, font, fontColor,50*px ,50*py-SCREEN_Y/8 ,"Voulez-vous quitter le jeu en cours ?");
		} else if (popup == 3){

			sprintf(end_msg,"Partie finie en %d mouvements",game_nb_moves(g));
			drawText(rdr, font, fontColor,50*px, 50*py-SCREEN_Y/8, end_msg);
			drawText(rdr, font, fontColor,50*px, 50*py-SCREEN_Y/17, "Voulez vous rejouer ?");
		}
		drawText(rdr, font, fontColor,16.6*px ,50*py+SCREEN_Y/8 ,"Echap : Non");
		drawText(rdr, font, fontColor,SCREEN_X-16.6*px ,50*py+SCREEN_Y/8 ,"Entree : Oui");
	}
	/*if (popup != 0){
		SDL_SetRenderDrawColor(rdr, 50, 50, 50, 170);
		rect.x = 0;
		rect.y = 25*py;
		rect.w = 100*px;
		rect.h = 50*py;
		SDL_RenderFillRect(rdr, &rect);
		if (popup == 1){
			drawText(rdr, font, fontColor,50*px ,37.5*py ,"Voulez-vous lancer une nouvelle partie ?");
		} else if (popup == 2){
			drawText(rdr, font, fontColor,50*px ,37.5*py ,"Voulez-vous quitter le jeu en cours ?");
		} else if (popup == 3){
			drawText(rdr, font, fontColor,50*px ,37.5*py ,"Partie Finie !");
		}
		if (popup != 3){
			drawText(rdr, font, fontColor,33*px ,62.5*py ,"Echap : Non");
			drawText(rdr, font, fontColor,66*px ,62.5*py ,"Entree : Oui");
		} else {
			drawText(rdr, font, fontColor,33*px ,62.5*py ,"Echap : Quitter");
			drawText(rdr, font, fontColor,66*px ,62.5*py ,"Entree : Continuer");
		}
	}*/
	SDL_RenderPresent(rdr);
	SDL_Delay(50);
}

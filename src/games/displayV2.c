#include <piece.h>
#include <game.h>
#include "utils.h"
#include "displayV2.h"

SDL_Window* initWindow(char* title){
	SDL_Window* win;
	win = SDL_CreateWindow(title,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_X, SCREEN_Y,
		SDL_WINDOW_SHOWN);
 
    if (win == NULL)
    {
        printf("Error SDL : Initializing SDL window");
        exit(1);
    }
	return win;
}

SDL_Renderer* initRenderer(SDL_Window* win){
	SDL_Renderer* rdr = NULL;
    rdr = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	printf("Renderer : %p\n", rdr);
    if (rdr == NULL) {
        printf("Error SDL : Initializing SDL renderer\n");
        exit(1);
    }
	
	if(TTF_Init() < 0) {
		printf("Error SDL : %s\n", TTF_GetError());
		exit(1);
	}
	
	return rdr;
}

void SDL_Free(SDL_Window* win, SDL_Renderer* rdr){
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
	{108,122,137},
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
	SDL_Color fontColor = {255, 255, 255};

	rect.w = (SCREEN_Y/game_height(g));
	rect.h = (SCREEN_Y/game_height(g));

	SDL_SetRenderDrawColor(rdr, 200,200,200, 255);
	SDL_RenderClear(rdr);
	SDL_SetRenderDrawColor(rdr, 0,200,0, 255);
	rect.y = (SCREEN_Y/game_height(g))*2;
	rect.x = (SCREEN_Y/game_height(g))*game_width(g);
	rect.h = (SCREEN_Y/game_height(g));
	rect.w = 10;
	SDL_RenderFillRect(rdr, &rect);
	for(int i = 0; i < game_nb_pieces(g); ++i){
		SDL_SetRenderDrawColor(rdr, color[i][0],color[i][1],color[i][2], 255);
		rect.x = get_x(game_piece(g,i))*(SCREEN_Y/game_height(g));
		rect.y = (SCREEN_Y - (get_y(game_piece(g,i))*(SCREEN_Y/game_height(g))));
		rect.w = get_width(game_piece(g,i))*(SCREEN_Y/game_height(g));
		rect.h = get_height(game_piece(g,i))*(SCREEN_Y/game_height(g));
		rect.y -= rect.h;
		SDL_RenderFillRect(rdr, &rect);
	}
	if (popup != 0){
		SDL_SetRenderDrawColor(rdr, 50, 50, 50, 170);
		rect.x = 0;
		rect.y = SCREEN_Y/4;
		rect.w = SCREEN_X;
		rect.h = SCREEN_Y/2;
		SDL_RenderFillRect(rdr, &rect);
		if (popup == 1){
			drawText(rdr, font, fontColor,SCREEN_X/2 ,SCREEN_Y/2-SCREEN_Y/8 ,"Voulez-vous lancer une nouvelle partie ?");
		} else if (popup == 2){
			drawText(rdr, font, fontColor,SCREEN_X/2 ,SCREEN_Y/2-SCREEN_Y/8 ,"Voulez-vous quitter le jeu en cours ?");
		} else if (popup == 1){
			drawText(rdr, font, fontColor,SCREEN_X/2 ,SCREEN_Y/2-SCREEN_Y/8 ,"Partie Finie !");
		}
		drawText(rdr, font, fontColor,SCREEN_X/6 ,SCREEN_Y/2+SCREEN_Y/8 ,"Echap : Non");
		drawText(rdr, font, fontColor,SCREEN_X-SCREEN_X/6 ,SCREEN_Y/2+SCREEN_Y/8 ,"Entree : Oui");
	}
	SDL_RenderPresent(rdr);
	SDL_Delay(50);
}

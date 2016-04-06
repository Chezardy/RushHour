#ifndef DISP2
#define DISP2
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define SCREEN_X 900
#define SCREEN_Y 600

SDL_Window* initWindow(char* title);

SDL_Renderer* initRenderer(SDL_Window* win);

void SDL_Free(SDL_Window* win, SDL_Renderer* rdr);

void SDL_Display(game g, SDL_Renderer* rdr, TTF_Font* font, int popup);

#endif
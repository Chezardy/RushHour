#ifndef DISP2
#define DISP2
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include <strings.h>

#define CONST_S 10
#define SCREEN_X 1280
#define SCREEN_Y 720

/*
Initialise la fenêtre SDL en fonction du jeu demandé.
Parametre title, le titre de la fenêtre.
Retourne un pointeur sur la fenêtre créée.
*/
SDL_Window* initWindow(char* title);

/*
Initialise l'espace utilisé pour y dessiner.
Parametre win, la fenêtre SDL.
Retourne un pointeur sur l'espace créé.
*/
SDL_Renderer* initRenderer(SDL_Window* win);

/*
Détruit l'espace et la fenêtre.
Réinitialise les deux pointeurs (=NULL).
*/
void SDL_Free(SDL_Window* win, SDL_Renderer* rdr);

/*
Permet de dessiner le texte que l'on veut dans l'espace de dessin.
Parametres:
	*rdr, l'espace de dessin
	*font, la police de caractère du texte
	*color, la couleur du texte
	*x,y, la position du texte
	*txt, le texte de notre choix
*/
void drawText(SDL_Renderer* rdr, TTF_Font* font, SDL_Color color, int x, int y, char* txt);

/*
Permet l'affichage du jeu en cours.
Parametres:
	*g, le jeu (rush hour ou ane rouge)
	*rdr, l'espace de dessin
	*font, la police de caractère du texte
	*popup, entier qui sert à distinguer quel message on fait apparaitre
	lors d'une interaction quelconque
*/
void SDL_Display(game g, SDL_Renderer* rdr, TTF_Font* font, int popup);

#endif

#include <piece.h>
#include <game.h>
#include "rush-hour.h"
#include "utils.h"

char *dir_c[] = {"up", "left", "down", "right"}; //Uniquement utile pour comparer avec l'input.

int rand_ab(int a, int b) {
	return (rand()%((b+1)-a)) + a;
}

bool streq(char* s1, char* s2) {
	int 	i = 1;
	
	if (s1[0] != s2[0]) return false;
	while (s1[i] != '\0' && s2[i] != '\0' && i < 20) {
		if (s1[i] != s2[i]) return false;
		i++;
	}
	return true;
}

bool readCommand(char *cmd, game g, bool (*game_over)(cgame), int* target, int* direction, int* distance) {
	(void)(game_over);
	char 	str[3][20]; //char** pour stocker les 3 aguments en 3 chaines de caractères
	int 	i = 0, j = 0, k = 0;

	//Initialisation à '\0' sur tous les caractères
	for (int i = 0; i < 3; i++) { 
		for (int j = 0; j < 10; j++) {
			str[i][j] = '\0';
		}
	}

	 //Parcours cmd et le stock dans str[j]
	while (cmd[i] != '\0' && i < 20 && j < 3) {
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
	if (*direction == -1 || *distance <= 0 || *target < 0 || *target >= game_nb_pieces(g)) return false; // si la direction ou le mouvement ne sont pas trouvés (ou distance = 0) renvoie faux
	return true;
}

void gestionInputs(Input *input)
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
 
			case SDL_QUIT:
				exit(0);
			break;
 
			case SDL_MOUSEBUTTONDOWN:
				switch(event.button.button){
					case SDL_BUTTON_LEFT:
						input->mouse = 1;
					break;
				}
			break;
			
			case SDL_MOUSEBUTTONUP:
				switch(event.button.button){
					case SDL_BUTTON_LEFT:
						input->mouse = 0;
					break;
				}
			break;
			
			case SDL_MOUSEMOTION:
				input->mouse_x = event.motion.x;
				input->mouse_y = event.motion.y;
			break;
 
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						input->escape = 1;
					break;
 
					case SDLK_DELETE:
						input->erase = 1;
					break;
 
					case SDLK_r:
						input->newGame = 1;
					break;
					
					case SDLK_q:
						input->quit = 1;
					break;
 
					case SDLK_LEFT:
						input->left = 1;
					break;
 
					case SDLK_RIGHT:
						input->right = 1;
					break;
 
					case SDLK_DOWN:
						input->down = 1;
					break;
 
					case SDLK_UP:
						input->up = 1;
					break;
 
 
					case SDLK_RETURN:
						input->enter = 1;
					break;
 
					default:
					break;
				}
			break;
 
			case SDL_KEYUP:
				switch (event.key.keysym.sym)
				{
					case SDLK_DELETE:
						input->erase = 0;
					break;
					
					case SDLK_ESCAPE:
						input->escape = 0;
					break;
					
					case SDLK_r:
						input->newGame = 0;
					break;
					
					case SDLK_q:
						input->quit = 0;
					break;
					
					case SDLK_LEFT:
						input->left = 0;
					break;
 
					case SDLK_RIGHT:
						input->right = 0;
					break;
 
					case SDLK_DOWN:
						input->down = 0;
					break;
 
					case SDLK_UP:
						input->up = 0;
					break;
 
					case SDLK_RETURN:
						input->enter = 0;
					break;
 
					default:
					break;
				}
			break;
 
		}
 
	}
}

void delay(unsigned int frameLimit)
{
	unsigned int ticks = SDL_GetTicks();
 
	if (frameLimit < ticks)
	{
		return;
	}
 
	if (frameLimit > ticks + 64)
	{
		SDL_Delay(64);
	}
 
	else
	{
		SDL_Delay(frameLimit - ticks);
	}
}

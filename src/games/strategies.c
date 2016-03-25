#include <piece.h>
#include <game.h>
#include "utils.h"
#include "strategies.h"
#include "displayV1.h"

bool brutStrategy(char* cmd, game g, bool (*game_over)(cgame), int *cmd_target, int *cmd_direction, int *cmd_distance) {
	(void)(cmd);
	*cmd_target = rand_ab(0,game_nb_pieces(g)-1);
	if (is_horizontal(game_piece(g, *cmd_target))) *cmd_direction =  (rand_ab(0,1)?1:3);
	else *cmd_direction =  (rand_ab(0,1)?0:2);
	*cmd_distance = 0;
	while (!(*game_over)(g)) {
		play_move(g,rand_ab(0,game_nb_pieces(g)-1), rand_ab(0,3), 1);
	}
	return true;
}

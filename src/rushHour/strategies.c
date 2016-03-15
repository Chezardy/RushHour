#include <piece.h>
#include <game.h>
#include "utils.h"
#include "strategies.h"
#include "displayV1.h"

bool brutStrategy(game g, int *cmd_target, int *cmd_direction, int *cmd_distance) {
	*cmd_target = rand_ab(0,game_nb_pieces(g)-1);
	if (is_horizontal(game_piece(g, *cmd_target))) *cmd_direction =  (rand_ab(0,1)?1:3);
	else *cmd_direction =  (rand_ab(0,1)?0:2);
	*cmd_distance = 1;
	return true;
}

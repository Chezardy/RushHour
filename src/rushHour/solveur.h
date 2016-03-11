#ifndef _SOLV_
#define _SOLV_

typedef struct s_cmd* cmd;

bool solveur(game g, int *cmd_target, int *cmd_direction, int *cmd_distance);

#endif
#ifndef _STRATEGIES_H_
#define _STRATEGIES_H_

/*
Solveur brut de rush hour et de l'âne rouge.
Fait des mouvements aléatoires tant que le jeu n'est pas terminé.
*/
bool brutStrategy(game g, bool (*game_over)(cgame));

#endif
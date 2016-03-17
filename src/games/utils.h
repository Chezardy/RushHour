#ifndef _UTILS_
#define _UTILS_

extern int rules;

char *dir_c[4]; //Uniquement utile pour comparer avec l'input

/*
Retourne un nombre aléatoire en a et b (compris)
*/
int rand_ab(int a, int b);

/*
Retourne true si les 2 chaines sont exactement identiques.
*/
bool streq(char* s1, char* s2);

/*
décompose le char* cmd pour y retrouver les 3 arguments utiles :
la piece ciblé, la direction du mouvement et la distance a parcourir.
Renvoie vrai si elle trouve les 3 arguments correctement, faux sinon.
*/
bool readCommand(char *cmd, int* target, int* direction, int* distance);

#endif
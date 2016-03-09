#include <piece.h>
#include <game.h>
#include <displayV1.h>
#include <rush-hour.h>
#include <utils.h>

char *dir_c[] = {"up", "left", "down", "right"}; //Uniquement utile pour comparer avec l'input

/*
Retourne un nombre aléatoire en a et b (compris)
*/
int rand_ab(int a, int b) {
	return (rand()%((b+1)-a)) + a;
}

/*
Retourne true si les 2 chaines sont exactement identiques.
*/
bool streq(char* s1, char* s2) {
	int 	i = 1;
	
	if (s1[0] != s2[0]) return false;
	while (s1[i] != '\0' && s2[i] != '\0' && i < 20) {
		if (s1[i] != s2[i]) return false;
		i++;
	}
	return true;
}

/*
décompose le char* cmd pour y retrouver les 3 arguments utiles :
la piece ciblé, la direction du mouvement et la distance a parcourir.
Renvoie vrai si elle trouve les 3 arguments correctement, faux sinon.
*/
bool readCommand(char *cmd, int* target, int* direction, int* distance) {
	char 	str[3][20]; // char** pour stocker les 3 aguments en string
	int 	i = 0, j = 0, k = 0;

	for (int i = 0; i < 3; i++) { // initialisation à '\0' sur tout les char
		for (int j = 0; j < 10; j++) {
			str[i][j] = '\0';
		}
	}
	while (cmd[i] != '\0' && i < 20 && j < 3) { // parcours cmd et le stock dans str[j]. A chaque espace j++ donc nouvel argument
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
	if (*direction == -1 || *distance == 0) return false; // si la direction ou le mouvement ne sont pas trouvé (ou distance = 0) renvoie faux
	return true;
}
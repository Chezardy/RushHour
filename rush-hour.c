#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "piece.h"
#include "game.h"

bool streq(char* s1, char* s2) {
	int i = 1;
	if (s1[0] != s2[0]) return false;
	while (s1[i] != '\0' && s2[i] != '\0' && i < 20) {
		if (s1[i] != s2[i]) return false;
		i++;
	}
	return true;
}

char *dir_c[] = {"up", "left", "down", "right"};

bool readCommand(char *cmd, int* target, int* direction, int* distance) {
	char str[3][10];
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 10; j++) {
			str[i][j] = '\0';
		}
	}
	int i = 0, j = 0, k = 0;
	while (cmd[i] != '\0' && i < 20 && j < 3) {
		if (cmd[i] == ' ') {
			j++;
			k = -1;
		} else {
			//printf("str %i %i : %c\n", j , k, cmd[i]);
			str[j][k] = cmd[i];
		}
		k++;
		i++;
	}
	if (j != 2) return false;
	//printf ("decoupage : -%s-%s-%s-\n", str[0], str[1], str[2]);
	*target = atoi(str[0]);
	*distance = atoi(str[2]);
	*direction = -1;
	for (int i = 0; i < 4; i++) {
		if (streq(str[1], dir_c[i])) *direction = i;
	}
	if (*direction == -1 || *distance == 0) return false;
	/*if (j != 2)return false;
	*target = atoi(str[0]);
	*direction = -1;
	if (str[1][0] == 'r') *direction = 3;
	if (*direction == -1) return false;
	*distance = atoi(str[2]);
	return true;*/
	
	return true;
}

int main(int argc, char* argv[]) {
	char 	cmd[80];
	//bool	cmd_isValid;
	int 	cmd_target;
	int 	cmd_direction;
	int 	cmd_distance;

	while (!streq(cmd,"exit")) {
		printf("Entrez votre commande : ");
		for (int j = 0; j < 80; j++) cmd[j] = '\0';
		fgets(cmd, 10, stdin);

		if (readCommand(cmd, &cmd_target, &cmd_direction, &cmd_distance)) {
			printf("Commande : deplacer la piece %d de %d case(s) dans la direction %i\n", cmd_target, cmd_distance, cmd_direction);
			
		} else if (cmd[0] != '\0' && !streq(cmd,"exit")) {
			printf("usage : <numeros piece> <up/left/down/right> <distance>\n");
		}
	}
	return EXIT_SUCCESS;
}
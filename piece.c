#include "piece.h"

struct piece_s {
	int x;
	int y;
	bool is_horizontal;
	bool small;
};

piece new_piece_rh (int x, int y, bool small, bool horizontal) {
	piece output = malloc(sizeof(struct piece_s));
	if (output == NULL) {
		printf("Erreur allocation piece\n");
		exit(0);
	}
	output->x = x;
	output->y = y;
	output->is_horizontal = horizontal;
	output->small = small;
	return output;
}

void delete_piece (piece p) {
	free(p);
}

void copy_piece (cpiece src, piece dst){
	dst->x = src->x;
	dst->y = src->y;
	dst->is_horizontal = src->is_horizontal;
	dst->small = src->small;
}

void move_piece (piece p, dir d, int distance){
	if (!p->is_horizontal) {
		if (d == UP) p->y += distance;
		else if (d == DOWN) p->y -= distance;
	} else {
		if (d == LEFT) p->x -= distance;
		if (d == RIGHT) p->x += distance;
	}
	/*if (p->y < 0) p->y = 0;
	else if (p->x < 0) p->x = 0;
	else if (p->y+get_height(p)-1 >= GAME_SIZE) p->y = GAME_SIZE-get_height(p);
	else if (p->x+get_width(p)-1 >= GAME_SIZE) p->x = GAME_SIZE-get_width(p);*/
}

bool intersect(cpiece p1, cpiece p2) {
	for(int i = 0; i < get_height(p1); ++i) {
		for(int j = 0; j < get_width(p1); ++j) {
			for(int i2 = 0; i2 < get_height(p2); ++i2) {
				for(int j2 = 0; j2 < get_width(p2); ++j2) {
					if (get_y(p1)+i == get_y(p2)+i2 && get_x(p1)+j == get_x(p2)+j2) return true;
				}
			}
		}
	}
	return false;
}

int get_x(cpiece p){
	return p->x;
}

int get_y(cpiece p){
	return p->y;
}

int get_height(cpiece p){
	if (p->is_horizontal) return 1;
	if (p->small) return 2;
	return 3;
}

int get_width(cpiece p){
	if (!p->is_horizontal) return 1;
	if (p->small) return 2;
	return 3;
}

bool is_horizontal(cpiece p){
	return p->is_horizontal;
}

/*int main() {
	piece p1 = new_piece_rh(1,2,true, false);
	piece p2 = new_piece_rh(1,0,false,true);
	if (intersect(p1, p2)) printf("p1 et p2 partage une meme case\n");
	return 0;
}*/
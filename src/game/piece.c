#include "piece.h"

struct piece_s {
	int x;
	int y;
	//bool is_horizontal;
	//bool small;
	int h;
	int w;
	bool move_h;
	bool move_v;

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
	if (!p->is_horizontal) { // si la piece est autorisé à bouger verticalement
		if (d == UP) p->y += distance;
		else if (d == DOWN) p->y -= distance;
	} else { // si elle est autorisé à bouger horizontalement
		if (d == LEFT) p->x -= distance;
		if (d == RIGHT) p->x += distance;
	}
}

bool intersect(cpiece p1, cpiece p2) { //Peut surement être amélioré
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
bool is_small(cpiece p){
	return p->small;
}
//////////////////////////////////V2/////////////////////////////////////////////////////

bool can_move_x(cpiece p){
	return move_v;
}
bool can_move_y(cpiece p){
	return move_h;
}

piece new_piece (int x, int y, int width, int height, bool move_x, bool move_y){
	piece output = malloc(sizeof(struct piece_s));
	if (output == NULL) {
		printf("Erreur allocation piece\n");
		exit(0);
	}
	output->x = x;
	output->y = y;
	output->w =width ;
	output->h = height
	output->move_h = move_x;
	output->move_v = move_y;
	return output;
}






}

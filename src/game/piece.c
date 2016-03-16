#include "piece.h"

struct piece_s {
	int x;
	int y;
	///bool is_horizontal;
	///bool small;
	int w;
	int h;
	bool move_x;
	bool move_y;
};
//position, its shape and its ability to move vertically or horizontally
piece new_piece_rh (int x, int y, bool small, bool horizontal) {
	piece output = malloc(sizeof(struct piece_s));
	if (output == NULL) {
		printf("Erreur allocation piece\n");
		exit(0);
	}
	output->x = x;
	output->y = y;
	
	if (horizontal) {
		output->h = 1;
		output->move_x = true;
		output->move_y = false;
		if(small) output->w = 2;
		else output->w = 3;
	} else {
		output->w = 1;
		output->move_x = false;
		output->move_y = true;
		if(small) output->h = 2;
		else output->h = 3;
	}

	return output;
}

void delete_piece (piece p) {
	free(p);
}

void copy_piece (cpiece src, piece dst){
	dst->x = src->x;
	dst->y = src->y;
	dst->h = src->h;
	dst->w = src->w;
	dst->move_x = src->move_x;
	dst->move_y = src->move_y;
}

void move_piece (piece p, dir d, int distance){
	if (p->move_y) { // si la piece est autorisé à bouger verticalement
		if (d == UP) p->y += distance;
		else if (d == DOWN) p->y -= distance;
	}
	if (p->move_x) { // si elle est autorisé à bouger horizontalement
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
	return p->h;
}

int get_width(cpiece p){
	return p->w;
}

bool is_horizontal(cpiece p){
	return (p->move_y);
}

bool is_small(cpiece p){
	return (p->w < 3 && p->h < 3);
}

bool can_move_x(cpiece p) {
	return p->move_x;
}
bool can_move_y(cpiece p){
	return p->move_y;
}
/**
 * @brief Initialized piece structure
 * @param x,y: coordinates of the bottom left corner of the piece
 * @param move_x: indicates if the piece is allowed to move horizontally
 * @param move_y: indicates if the piece is allowed to move vertically
 * @return created piece at a given position
 */
piece new_piece (int x, int y, int width, int height, bool move_x, bool move_y){
	piece output = malloc(sizeof(struct piece_s));
	if (output == NULL) {
		printf("Erreur allocation piece\n");
		exit(0);
	}
	output->x = x;
	output->y = y;
	output->w = width;
	output->h = height;//
	output->move_x = move_x;//
	output->move_y = move_y;//
	
	return output;
}


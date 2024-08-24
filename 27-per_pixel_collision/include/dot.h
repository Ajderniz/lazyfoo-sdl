#ifndef DOT_H
#define DOT_H

#include <SDL2/SDL_rect.h>

#define DOT_VEL 2

typedef struct {
	int pos_x, pos_y;
	int vel_x, vel_y;
	SDL_Rect rects[7];
} Dot;

void DOT_init(Dot*, int x, int y);
void DOT_move(Dot*);

#endif

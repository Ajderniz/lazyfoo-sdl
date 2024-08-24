#ifndef DOT_H
#define DOT_H

#include <SDL2/SDL_rect.h>

#define DOT_VEL 10

typedef struct {
	SDL_Rect rect;
	int vel_x, vel_y;
} Dot;

void DOT_move(Dot*);

#endif

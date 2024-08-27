#ifndef DOT_H
#define DOT_H

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>

#include "../include/geom.h"

#define DOT_VEL 2

typedef struct {
	int vel_x, vel_y;
	GEOM_Circle circle;
} Dot;

void DOT_move(Dot*);
void DOT_handle_event(Dot*, SDL_Event*);

#endif

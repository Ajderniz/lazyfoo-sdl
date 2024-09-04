#ifndef GEOM_H
#define GEOM_H

#include <stdbool.h>

#include <SDL2/SDL_rect.h>

typedef struct {
	int x, y;
	int r;
} GEOM_Circle;

bool GEOM_rect2rect_collision(SDL_Rect, SDL_Rect);
bool GEOM_circle2circle_collision(GEOM_Circle, GEOM_Circle);
bool GEOM_circle2rect_collision(GEOM_Circle, SDL_Rect);

#endif

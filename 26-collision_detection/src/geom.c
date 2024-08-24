/*
 * Included at header:
 * ===================
 * stdbool.h
 * SDL_rect.h
 */
#include "../include/geom.h"

bool GEOM_check_collision(SDL_Rect a, SDL_Rect b)
{
	return !((a.x + a.w) <= b.x || (b.x + b.w) <= a.x ||
			(a.y + a.h) <= b.y || (b.y + b.h) <= a.y);
}

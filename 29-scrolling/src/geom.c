#include "../include/geom.h"
/*
 * Included at header:
 * ===================
 * stdbool.h
 * SDL_rect.h
 */

#include "../include/screen.h"

double distance_squared(int x1, int y1, int x2, int y2)
{
	int delta_x = x2 - x1;
	int delta_y = y2 - y1;
	return (delta_x * delta_x) + (delta_y * delta_y);
}

bool GEOM_rect2rect_collision(SDL_Rect a, SDL_Rect b)
{
	return !((a.x + a.w) <= b.x || (b.x + b.w) <= a.x ||
		 (a.y + a.h) <= b.y || (b.y + b.h) <= a.y);
}

bool GEOM_circle2circle_collision(GEOM_Circle a, GEOM_Circle b)
{
	int total_radius_squared = a.r + b.r;
	total_radius_squared *= total_radius_squared;

	return (distance_squared(a.x, a.y, b.x, b.y) < total_radius_squared);
}

bool GEOM_circle2rect_collision(GEOM_Circle a, SDL_Rect b)
{
	int collision_x, collision_y;

	if(a.x < b.x) {
		collision_x = b.x;
	} else if((b.x + b.w) < a.x) {
		collision_x = b.x + b.w;
	} else {
		collision_x = a.x;
	}
	if (a.y < b.y) {
		collision_y = b.y;
	} else if ((b.y + b.h) < a.y) {
		collision_y = b.y + b.h;
	} else {
		collision_y = a.y;
	}

	return distance_squared(a.x, a.y, collision_x, collision_y)
		< (a.r * a.r);
}

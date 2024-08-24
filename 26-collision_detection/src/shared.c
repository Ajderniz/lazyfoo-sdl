#include "../include/shared.h"

extern struct Shared shared;

void SHARED_load(void)
{
	shared.dot.vel_x = shared.dot.vel_y = 0;
	shared.dot.rect.x = shared.dot.rect.y = 0;
	shared.dot.rect.w = shared.dot.rect.h = 20;

	shared.wall.x = shared.wall.y = 100;
	shared.wall.w = 20;
	shared.wall.h = 100;
}

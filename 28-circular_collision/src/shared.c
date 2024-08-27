#include "../include/dot.h"
#include "../include/shared.h"

extern struct Shared shared;

void SHARED_load(void)
{
	shared.dot.circle.r = 10;
	shared.dot.circle.x = shared.dot.circle.y = 0 + shared.dot.circle.r;
	shared.dot.vel_x = shared.dot.vel_y = 0;

	shared.other_dot.circle.r = 10;
	shared.other_dot.circle.x = shared.other_dot.circle.y = 100;
	shared.other_dot.vel_x = shared.other_dot.vel_y = 0;

	shared.wall.x = 250;
	shared.wall.y = 50;
	shared.wall.w = 30;
	shared.wall.h = 200;
}

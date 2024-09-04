#include "../include/shared.h"
/*
 * Included at header:
 * ===================
 * dot.h
 */

extern struct Shared shared;

void SHARED_load(void)
{
	shared.dot.rect.x = shared.dot.rect.y = 0;
	shared.dot.vel_x = shared.dot.vel_y = 0;
}

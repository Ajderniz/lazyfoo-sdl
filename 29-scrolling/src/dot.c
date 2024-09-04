#include "../include/dot.h"
/* 
 * Included at header:
 * ===================
 * SDL_rect.h
 */
#include <SDL2/SDL_render.h>

#include "../include/screen.h"
#include "../include/shared.h"

extern struct Shared shared;

void DOT_move(Dot *this)
{
	this->rect.x += this->vel_x;
	if (this->rect.x < 0 || LEVEL_WIDTH < (this->rect.x + this->rect.w)) {
		this->rect.x -= this->vel_x;
	}
	this->rect.y += this->vel_y;
	if (this->rect.y < 0 || LEVEL_HEIGHT < (this->rect.y + this->rect.h)) {
		this->rect.y -= this->vel_y;
	}
}

#include "../include/dot.h"
/* 
 * Included at header:
 * ===================
 * SDL_rect.h
 */
#include "../include/screen.h"

void DOT_move(Dot *this)
{
	this->rect.x += this->vel_x;
	if (this->rect.x < 0 || SCREEN_WIDTH < (this->rect.x + this->rect.w)) {
		this->rect.x -= this->vel_x;
	}
	this->rect.y += this->vel_y;
	if (this->rect.y < 0 || SCREEN_HEIGHT < (this->rect.y + this->rect.h)) {
		this->rect.y -= this->vel_y;
	}
}

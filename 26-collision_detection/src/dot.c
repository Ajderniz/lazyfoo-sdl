#include "../include/dot.h"
#include "../include/geom.h"
#include "../include/shared.h"
#include "../include/screen.h"

extern struct Shared shared;

void DOT_move(Dot *this)
{
	this->rect.x += this->vel_x;
	if (this->rect.x < 0 || SCREEN_WIDTH < (this->rect.x + this->rect.w) ||
			GEOM_check_collision(this->rect, shared.wall)) {
		this->rect.x -= this->vel_x;
	}
	this->rect.y += this->vel_y;
	if (this->rect.y < 0 || SCREEN_HEIGHT < (this->rect.y + this->rect.h) ||
			GEOM_check_collision(this->rect, shared.wall)) {
		this->rect.y -= this->vel_y;
	}
}

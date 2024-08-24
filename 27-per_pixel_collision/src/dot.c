#include <SDL2/SDL_render.h>

#include "../include/dot.h"
#include "../include/geom.h"
#include "../include/shared.h"
#include "../include/screen.h"

extern struct Shared shared;

void DOT_init(Dot *this, int x, int y)
{
	this->pos_x = x;
	this->pos_y = y;

	this->vel_x = this->vel_y = 0;

	this->rects[0].x = x + 7;
	this->rects[0].y = y + 0;
	this->rects[0].w = 6;
	this->rects[0].h = 20;

	this->rects[1].x = x + 5;
	this->rects[1].y = y + 1;
	this->rects[1].w = 10;
	this->rects[1].h = 18;

	this->rects[2].x = x + 4;
	this->rects[2].y = y + 2;
	this->rects[2].w = 12;
	this->rects[2].h = 16;

	this->rects[3].x = x + 3;
	this->rects[3].y = y + 3;
	this->rects[3].w = 14;
	this->rects[3].h = 14;

	this->rects[4].x = x + 2;
	this->rects[4].y = y + 4;
	this->rects[4].w = 16;
	this->rects[4].h = 12;

	this->rects[5].x = x + 1;
	this->rects[5].y = y + 5;
	this->rects[5].w = 18;
	this->rects[5].h = 10;

	this->rects[6].x = x + 0;
	this->rects[6].y = y + 7;
	this->rects[6].w = 20;
	this->rects[6].h = 6;
}

void set_pos(Dot *this, int x, int y)
{
	unsigned int i;
	for (i = 0; i < (sizeof(this->rects) / sizeof(SDL_Rect)); i++) {
		this->rects[i].x = x + (this->rects[i].x - this->pos_x);
		this->rects[i].y = y + (this->rects[i].y - this->pos_y);
	}
	this->pos_x = x;
	this->pos_y = y;
}

void DOT_move(Dot *this)
{
	unsigned int i;
	set_pos(this, this->pos_x + this->vel_x, this->pos_y);
	for (i = 0; i < (sizeof(this->rects) / sizeof(SDL_Rect)); i++) {
		if (this->rects[i].x < 0 ||
			SCREEN_WIDTH < (this->rects[i].x + this->rects[i].w) ||
			GEOM_check_collision
			(this->rects[i], shared.other_dot.rects[i])) {

			set_pos(this, this->pos_x - this->vel_x, this->pos_y);
		}
	}
	set_pos(this, this->pos_x, this->pos_y + this->vel_y);
	for (i = 0; i < (sizeof(this->rects) / sizeof(SDL_Rect)); i++) {
		if (this->rects[i].y < 0 ||
			SCREEN_HEIGHT < (this->rects[i].y + this->rects[i].h) ||
			GEOM_check_collision
			(this->rects[i], shared.other_dot.rects[i])) {

			set_pos(this, this->pos_x, this->pos_y - this->vel_y);
		}
	}
}

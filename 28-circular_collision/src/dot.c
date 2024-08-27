/* 
 * Included at header:
 * ===================
 * SDL_rect.h
 * SDL_event.h
 */
#include <SDL2/SDL_render.h>

#include "../include/dot.h"
#include "../include/geom.h"
#include "../include/screen.h"
#include "../include/shared.h"

extern struct Shared shared;

void DOT_move(Dot *this)
{
	this->circle.x += this->vel_x;
	if ((this->circle.x - this->circle.r) < 0 ||
		SCREEN_WIDTH < (this->circle.x + this->circle.r) ||
		GEOM_circle2circle_collision
			(this->circle, shared.other_dot.circle) ||
		GEOM_circle2rect_collision(this->circle, shared.wall)) {

		this->circle.x -= this->vel_x;
	}

	this->circle.y += this->vel_y;
	if ((this->circle.y - this->circle.r) < 0 ||
		SCREEN_HEIGHT < (this->circle.y + this->circle.r) ||
		GEOM_circle2circle_collision
			(this->circle, shared.other_dot.circle) ||
		GEOM_circle2rect_collision(this->circle, shared.wall)) {

		this->circle.y -= this->vel_y;
	}
}

void DOT_handle_event(Dot *this, SDL_Event *event)
{
	if (SDL_KEYDOWN == event->type) {
		switch(event->key.keysym.scancode) {
		case SDL_SCANCODE_UP:
			this->vel_y = -DOT_VEL;
			break;
		case SDL_SCANCODE_DOWN:
			this->vel_y = +DOT_VEL;
			break;
		case SDL_SCANCODE_LEFT:
			this->vel_x = -DOT_VEL;
			break;
		case SDL_SCANCODE_RIGHT:
			this->vel_x = +DOT_VEL;
			break;
		default: break;
		}
	} else if (SDL_KEYUP == event->type) {
		switch (event->key.keysym.scancode) {
		case SDL_SCANCODE_UP:
		case SDL_SCANCODE_DOWN:
			this->vel_y = 0;
			break;
		case SDL_SCANCODE_LEFT:
		case SDL_SCANCODE_RIGHT:
			this->vel_x = 0;
			break;
		default: break;
		}
	}
}

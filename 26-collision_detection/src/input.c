#include <SDL2/SDL_events.h>

#include "../include/input.h"
#include "../include/shared.h"

extern struct Shared shared;

enum Continue INPUT_handle(void)
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			return INPUT_QUIT;
			break;
		case SDL_KEYDOWN:
			if (event.key.repeat != 0) {
				break;
			}
			switch (event.key.keysym.scancode) {
			case SDL_SCANCODE_UP:
				shared.dot.vel_y -= DOT_VEL;
				break;
			case SDL_SCANCODE_DOWN:
				shared.dot.vel_y += DOT_VEL;
				break;
			case SDL_SCANCODE_LEFT:
				shared.dot.vel_x -= DOT_VEL;
				break;
			case SDL_SCANCODE_RIGHT:
				shared.dot.vel_x += DOT_VEL;
				break;
			default: break;
			}
			break;
		case SDL_KEYUP:
			if (event.key.repeat != 0) {
				break;
			}
			switch (event.key.keysym.scancode) {
			case SDL_SCANCODE_UP:
				shared.dot.vel_y += DOT_VEL;
				break;
			case SDL_SCANCODE_DOWN:
				shared.dot.vel_y -= DOT_VEL;
				break;
			case SDL_SCANCODE_LEFT:
				shared.dot.vel_x += DOT_VEL;
				break;
			case SDL_SCANCODE_RIGHT:
				shared.dot.vel_x -= DOT_VEL;
				break;
			default: break;
			}
			break;
		default:
			break;
		}
	}
	return INPUT_CONTINUE;
}

#include "../include/input.h"

#include <SDL2/SDL_events.h>

#include "../include/shared.h"

extern struct Shared shared;

enum Continue INPUT_handle(void)
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (SDL_QUIT == event.type) {
			return INPUT_QUIT;
		}
		if (SDL_KEYDOWN == event.type && 0 == event.key.repeat) {
			switch(event.key.keysym.scancode) {
			case SDL_SCANCODE_UP:
				shared.dot.vel_y = -DOT_VEL;
				break;
			case SDL_SCANCODE_DOWN:
				shared.dot.vel_y = +DOT_VEL;
				break;
			case SDL_SCANCODE_LEFT:
				shared.dot.vel_x = -DOT_VEL;
				break;
			case SDL_SCANCODE_RIGHT:
				shared.dot.vel_x = +DOT_VEL;
				break;
			default: break;
			}
		} else if (SDL_KEYUP == event.type && 0 == event.key.repeat) {
			switch (event.key.keysym.scancode) {
			case SDL_SCANCODE_UP:
			case SDL_SCANCODE_DOWN:
				shared.dot.vel_y = 0;
				break;
			case SDL_SCANCODE_LEFT:
			case SDL_SCANCODE_RIGHT:
				shared.dot.vel_x = 0;
				break;
			default: break;
			}
		}
	}
	return INPUT_CONTINUE;
}

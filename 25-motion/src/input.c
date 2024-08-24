#include <SDL2/SDL_events.h>

#include "../include/input.h"
#include "../include/res.h"

extern struct Res res;

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
				res.dot.vel_y -= res.dot.rect.h;
				break;
			case SDL_SCANCODE_DOWN:
				res.dot.vel_y += res.dot.rect.h;
				break;
			case SDL_SCANCODE_LEFT:
				res.dot.vel_x -= res.dot.rect.w;
				break;
			case SDL_SCANCODE_RIGHT:
				res.dot.vel_x += res.dot.rect.w;
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
				res.dot.vel_y += res.dot.rect.h;
				break;
			case SDL_SCANCODE_DOWN:
				res.dot.vel_y -= res.dot.rect.h;
				break;
			case SDL_SCANCODE_LEFT:
				res.dot.vel_x += res.dot.rect.w;
				break;
			case SDL_SCANCODE_RIGHT:
				res.dot.vel_x -= res.dot.rect.w;
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

/*
 * Included at header:
 * ===================
 * stdbool.h
 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>

#include "../include/game.h"
#include "../include/graphics.h"

bool GAME_init(void)
{
	if (false == GRAPHICS_init()) {
		return false;
	}
	if (false == GRAPHICS_load_media()) {
		return false;
	}
	return true;
}

void GAME_fini(void)
{
	GRAPHICS_destroy();
}

void GAME_loop(void)
{
	bool running;
	SDL_Event event;

	running = true;
	while (true == running) {
		while (SDL_PollEvent(&event)) {
			if (SDL_QUIT == event.type) {
				running = false;
			} else if (SDL_KEYDOWN == event.type &&
					SDL_SCANCODE_RETURN ==
					event.key.keysym.scancode) {
				GRAPHICS_reset_timer();
			}
		}
		GRAPHICS_update();
	}
}

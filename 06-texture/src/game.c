/*
 * Included at header:
 * ===================
 * stdbool.h
 */
#include <SDL2/SDL.h>

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
			}
		}
		GRAPHICS_update();
	}
}

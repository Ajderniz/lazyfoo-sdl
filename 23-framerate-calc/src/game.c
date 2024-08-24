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
#include "../include/interface.h"

bool GAME_init(void)
{
	if (false == INTERFACE_init()) {
		return false;
	}
	if (false == INTERFACE_load_media()) {
		return false;
	}
	return true;
}

void GAME_fini(void)
{
	INTERFACE_destroy();
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
		INTERFACE_update();
	}
}

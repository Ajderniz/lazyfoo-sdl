/*
 * Included at header:
 * ===================
 * stdbool.h
 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_render.h>

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
	bool running, pressed;
	SDL_Event event;

	pressed = false;
	running = true;
	while (true == running) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				running = false;
				break;
			case SDL_JOYBUTTONDOWN:
				pressed = true;
				break;
			case SDL_JOYBUTTONUP:
				pressed = false;
			}
		}
		if (true == pressed) {
			GRAPHICS_vibrate();
		}
		GRAPHICS_update();
	}
}

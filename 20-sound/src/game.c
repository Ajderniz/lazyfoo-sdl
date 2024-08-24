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
			} else if (SDL_KEYDOWN == event.type) {
				switch(event.key.keysym.scancode) {
				case SDL_SCANCODE_1:
					GRAPHICS_play_sound();
					break;
				case SDL_SCANCODE_2:
					GRAPHICS_play_music();
					break;
				case SDL_SCANCODE_SPACE:
					GRAPHICS_stop_music();
					break;
				default:
					break;
				}
			}
		}
		GRAPHICS_update();
	}
}

/*
 * Included at header:
 * ===================
 * stdbool.h
 */
#include <stdlib.h> /* malloc, free */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include "../include/log.h"
#include "../include/shared.h"
#include "../include/screen.h"
#include "../include/timer.h"

extern struct Shared shared;

SDL_Window *g_window = NULL;
SDL_Renderer *g_renderer = NULL;

SDL_Texture *g_texture = NULL;

bool SCREEN_init(void)
{
	LOG_DEBUG(("Initializing screen\n"));

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		LOG_ERROR(("Could not initialize SDL: %s\n", SDL_GetError()));
		return false;
	}

	if (0 == IMG_Init(IMG_INIT_PNG)) {
		LOG_ERROR(("Could not initialize IMG: %s\n", SDL_GetError()));
		return false;
	}

	g_window = SDL_CreateWindow("SDL TUTORIAL",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
	if (NULL == g_window) {
		LOG_ERROR(("Could not create window: %s\n", SDL_GetError()));
		return false;
	}

	g_renderer = SDL_CreateRenderer(g_window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (NULL == g_renderer) {
		LOG_ERROR(("Could not create renderer: %s\n", SDL_GetError()));
		return false;
	}

	return true;
}

void SCREEN_destroy(void)
{
	LOG_DEBUG(("Destroying screen\n"));
	if (g_renderer != NULL) {
		SDL_DestroyRenderer(g_renderer);
		g_renderer = NULL;
	}
	if (g_window != NULL) {
		SDL_DestroyWindow(g_window);
		g_window = NULL;
	}
	LOG_DEBUG(("Quitting SDL\n"));
	SDL_Quit();
}

bool SCREEN_load_media(void)
{
	SHARED_load();
	return true;
}

void SCREEN_update(void)
{
	int frame_ticks;
	Timer cap_timer;
	TIMER_start(&cap_timer);

	SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
	SDL_RenderClear(g_renderer);

	DOT_move(&shared.dot);
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderFillRects(g_renderer, shared.dot.rects, 7);
	SDL_RenderFillRects(g_renderer, shared.other_dot.rects, 7);

	SDL_RenderPresent(g_renderer);

	frame_ticks = TIMER_get_ticks(&cap_timer);
	if (frame_ticks < TICKS_A_FRAME) {
		SDL_Delay(TICKS_A_FRAME - frame_ticks);
	}
}

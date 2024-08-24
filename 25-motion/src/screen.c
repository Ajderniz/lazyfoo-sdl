/*
 * Included at header:
 * ===================
 * stdbool.h
 */
#include <stdlib.h> /* malloc, free */

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include "../include/res.h"
#include "../include/screen.h"
#include "../include/timer.h"

extern struct Res res;

SDL_Window *g_window = NULL;
SDL_Renderer *g_renderer = NULL;

bool SCREEN_init(void)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		return false;
	}

	g_window = SDL_CreateWindow("SDL TUTORIAL",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
	if (NULL == g_window) {
		return false;
	}

	g_renderer = SDL_CreateRenderer(g_window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (NULL == g_renderer) {
		return false;
	}

	return true;
}

void SCREEN_destroy(void)
{
	if (g_renderer != NULL) {
		SDL_DestroyRenderer(g_renderer);
		g_renderer = NULL;
	}
	if (g_window != NULL) {
		SDL_DestroyWindow(g_window);
		g_window = NULL;
	}
	SDL_Quit();
}

bool SCREEN_load_media(void)
{
	res.dot.rect.w = res.dot.rect.h = 20;
	res.dot.rect.x = res.dot.rect.y = 0;
	res.dot.vel_x = res.dot.vel_y = 0;
	return true;
}

void SCREEN_update(void)
{
	int frame_ticks;
	Timer cap_timer;
	TIMER_start(&cap_timer);

	SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
	SDL_RenderClear(g_renderer);

	DOT_move(&res.dot);
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(g_renderer, &res.dot.rect);

	SDL_RenderPresent(g_renderer);

	frame_ticks = TIMER_get_ticks(&cap_timer);
	if (frame_ticks < TICKS_A_FRAME) {
		SDL_Delay(TICKS_A_FRAME - frame_ticks);
	}
}

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
SDL_Rect g_dst_rect;

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
	if (g_texture != NULL) {
		SDL_DestroyTexture(g_texture);
		g_texture = NULL;
	}
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
	g_texture = IMG_LoadTexture(g_renderer, IMG_DIR"/texture.png");
	if (NULL == g_texture) {
		LOG_ERROR(("Could not load texture: %s\n", SDL_GetError()));
		return false;
	}
	SDL_QueryTexture(g_texture, NULL, NULL, &g_dst_rect.w, &g_dst_rect.h);
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

	g_dst_rect.x = shared.dot.circle.x - shared.dot.circle.r;
	g_dst_rect.y = shared.dot.circle.y - shared.dot.circle.r;
	SDL_RenderCopy(g_renderer, g_texture, NULL, &g_dst_rect);

	g_dst_rect.x = shared.other_dot.circle.x - shared.dot.circle.r;
	g_dst_rect.y = shared.other_dot.circle.y - shared.dot.circle.r;
	SDL_RenderCopy(g_renderer, g_texture, NULL, &g_dst_rect);

	SDL_RenderFillRect(g_renderer, &shared.wall);

	SDL_RenderPresent(g_renderer);

	frame_ticks = TIMER_get_ticks(&cap_timer);
	if (frame_ticks < TICKS_A_FRAME) {
		SDL_Delay(TICKS_A_FRAME - frame_ticks);
	}
}

void SCREEN_line(int x1, int y1, int x2, int y2)
{
	SDL_SetRenderDrawColor(g_renderer, 0, 0, 255, 255);
	SDL_RenderDrawLine(g_renderer, x1, y1, x2, y2);
}

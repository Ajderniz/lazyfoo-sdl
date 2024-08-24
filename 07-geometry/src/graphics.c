/*
 * Included at header:
 * ===================
 * stdbool.h
 */
#include <stdlib.h> /* malloc, free */

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include "../include/graphics.h"

SDL_Window *g_window = NULL;
SDL_Renderer *g_renderer = NULL;

bool GRAPHICS_init(void)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		return false;
	}

	g_window = SDL_CreateWindow("SDL TUTORIAL",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			GRAPHICS_SCR_W, GRAPHICS_SCR_H,
			SDL_WINDOW_SHOWN);
	if (NULL == g_window) {
		return false;
	}

	g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
	if (NULL == g_renderer) {
		return false;
	}
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);

	return true;
}

void GRAPHICS_destroy(void)
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

void GRAPHICS_update(void)
{
	int x;
	SDL_Rect fill_rect, outline_rect;

	SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
	SDL_RenderClear(g_renderer);

	fill_rect.x = GRAPHICS_SCR_W / 4;
	fill_rect.y = GRAPHICS_SCR_H / 4;
	fill_rect.w = GRAPHICS_SCR_W / 2;
	fill_rect.h = GRAPHICS_SCR_H / 2;
	SDL_SetRenderDrawColor(g_renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(g_renderer, &fill_rect);

	outline_rect.x = GRAPHICS_SCR_W / 6;
	outline_rect.y = GRAPHICS_SCR_H / 6;
	outline_rect.w = (GRAPHICS_SCR_W * 2) / 3;
	outline_rect.h = (GRAPHICS_SCR_H * 2) / 3;
	SDL_SetRenderDrawColor(g_renderer, 0, 255, 0, 255);
	SDL_RenderDrawRect(g_renderer, &outline_rect);

	SDL_SetRenderDrawColor(g_renderer, 0, 0, 255, 255);
	SDL_RenderDrawLine(g_renderer,
			0, 		GRAPHICS_SCR_H / 2,
			GRAPHICS_SCR_W, GRAPHICS_SCR_H / 2);

	SDL_SetRenderDrawColor(g_renderer, 255, 255, 0, 255);
	for (x = 0; x < GRAPHICS_SCR_H; x += 4) {
		SDL_RenderDrawPoint(g_renderer, GRAPHICS_SCR_W / 2, x);
	}

	SDL_RenderPresent(g_renderer);
}

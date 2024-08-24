/*
 * Included at header:
 * ===================
 * stdbool.h
 */
#include <stdlib.h> /* malloc, free */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>

#include "../include/graphics.h"

SDL_Window *g_window = NULL;
SDL_Renderer *g_renderer = NULL;
SDL_Texture *g_texture = NULL;
SDL_Rect g_dst_rect;
SDL_RendererFlip g_flip_type = SDL_FLIP_NONE;
int g_angle = 0;

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

	g_renderer = SDL_CreateRenderer(g_window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (NULL == g_renderer) {
		return false;
	}
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);

	if (0 == (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))  {
		return false;
	}

	return true;
}

void GRAPHICS_destroy(void)
{
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
	IMG_Quit();
	SDL_Quit();
}

bool GRAPHICS_load_media(void)
{
	g_texture = IMG_LoadTexture(g_renderer, GRAPHICS_IMG_DIR"/texture.png");
	if (NULL == g_texture) {
		return false;
	}
	SDL_QueryTexture(g_texture, NULL, NULL, &g_dst_rect.w, &g_dst_rect.h);
	g_dst_rect.x = (GRAPHICS_SCR_W - g_dst_rect.w) / 2;
	g_dst_rect.y = (GRAPHICS_SCR_H - g_dst_rect.h) / 2;

	return true;
}

void GRAPHICS_update(void)
{
	SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
	SDL_RenderClear(g_renderer);

	SDL_RenderCopyEx(g_renderer, g_texture, NULL, &g_dst_rect, g_angle,
			NULL, g_flip_type);

	SDL_RenderPresent(g_renderer);
	SDL_Delay(100);
}

void GRAPHICS_set_flip(SDL_RendererFlip flip_type)
{
	g_flip_type = flip_type;
}

void GRAPHICS_modify_angle(int degrees)
{
	g_angle += degrees;
}

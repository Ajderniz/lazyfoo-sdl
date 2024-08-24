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
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>

#include "../include/graphics.h"

SDL_Window *g_window = NULL;
SDL_Renderer *g_renderer = NULL;
SDL_Texture *g_texture = NULL;
TTF_Font *g_font;
SDL_Rect g_dst_rect;

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

	if (-1 == TTF_Init()) {
		return false;
	}

	return true;
}

void GRAPHICS_destroy(void)
{
	if (g_font != NULL) {
		TTF_CloseFont(g_font);
		g_font = NULL;
	}
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
	TTF_Quit();
	SDL_Quit();
}

bool GRAPHICS_load_media(void)
{
	SDL_Color color;
	SDL_Surface *ttf_surface = NULL;

	g_font = TTF_OpenFont(GRAPHICS_TTF_DIR"/font.ttf", 32);

	color.r = color.g = color.b = color.a = 255;
	ttf_surface = TTF_RenderText_Solid
		(g_font, "DEHUMANIZE YOURSELF AND ETC.", color);
	if (NULL == ttf_surface) {
		return false;
	}
	g_dst_rect.w = ttf_surface->w;
	g_dst_rect.h = ttf_surface->h;
	
	g_texture = SDL_CreateTextureFromSurface(g_renderer, ttf_surface);
	SDL_FreeSurface(ttf_surface);
	if (NULL == g_texture) {
		return false;
	}

	return true;
}

void GRAPHICS_update(void)
{
	SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
	SDL_RenderClear(g_renderer);

	g_dst_rect.x = (GRAPHICS_SCR_W - g_dst_rect.w) / 2;
	g_dst_rect.y = (GRAPHICS_SCR_H - g_dst_rect.h) / 2;
	SDL_RenderCopy(g_renderer, g_texture, NULL, &g_dst_rect);

	SDL_RenderPresent(g_renderer);
	SDL_Delay(100);
}

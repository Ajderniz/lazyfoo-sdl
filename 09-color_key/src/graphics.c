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
#include "../include/ltexture.h"

SDL_Window *g_window = NULL;
SDL_Renderer *g_renderer = NULL;
LTexture *g_bg_texture = NULL;
LTexture *g_foo_texture = NULL;

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

	g_bg_texture = LTEXTURE_init();
	if (NULL == g_bg_texture) {
		return false;
	}
	g_foo_texture = LTEXTURE_init();
	if (NULL == g_foo_texture) {
		return false;
	}

	if (0 == (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))  {
		return false;
	}

	return true;
}

void GRAPHICS_destroy(void)
{
	if (g_bg_texture != NULL) {
		LTEXTURE_destroy(g_bg_texture);
		g_bg_texture = NULL;
	}
	if (g_foo_texture != NULL) {
		LTEXTURE_destroy(g_foo_texture);
		g_foo_texture = NULL;
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
	if(false == LTEXTURE_load(
			g_bg_texture, 
			g_renderer, 
			GRAPHICS_IMG_DIR"/bg.png")) {
		return false;
	}
	if(false == LTEXTURE_load(
			g_foo_texture, 
			g_renderer, 
			GRAPHICS_IMG_DIR"/foo.png")) {
		return false;
	}
	return true;
}

void GRAPHICS_update(void)
{
	SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
	SDL_RenderClear(g_renderer);

	LTEXTURE_render(g_bg_texture, g_renderer, 0, 0);
	LTEXTURE_render(g_foo_texture, g_renderer, 240, 190);

	SDL_RenderPresent(g_renderer);
	SDL_Delay(30);
}

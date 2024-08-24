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
LTexture *g_fg_ltexture = NULL;
LTexture *g_bg_ltexture = NULL;
Uint8 g_alpha = 255;

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

	if (0 == (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))  {
		return false;
	}

	return true;
}

void GRAPHICS_destroy(void)
{
	if (g_fg_ltexture != NULL) {
		LTEXTURE_destroy(g_fg_ltexture);
		g_fg_ltexture = NULL;
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
	g_fg_ltexture = LTEXTURE_load(g_renderer, GRAPHICS_IMG_DIR"/fg.png");
	g_bg_ltexture = LTEXTURE_load(g_renderer, GRAPHICS_IMG_DIR"/bg.png");
	if (NULL == g_fg_ltexture || NULL == g_bg_ltexture) {
		return false;
	}
	SDL_SetTextureBlendMode(g_fg_ltexture->texture, SDL_BLENDMODE_BLEND);
	return true;
}

void GRAPHICS_update(void)
{
	SDL_Rect clip_rect;
	clip_rect.x = clip_rect.y = 0;
	clip_rect.w = GRAPHICS_SCR_W;
	clip_rect.h = GRAPHICS_SCR_H;

	SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
	SDL_RenderClear(g_renderer);

	LTEXTURE_render(g_bg_ltexture, g_renderer, &clip_rect);

	SDL_SetTextureAlphaMod(g_fg_ltexture->texture, g_alpha);
	LTEXTURE_render(g_fg_ltexture, g_renderer, &clip_rect);

	SDL_RenderPresent(g_renderer);
	SDL_Delay(30);
}

void GRAPHICS_modify_alpha(int amount)
{
	g_alpha += amount;
}

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
LTexture *g_texture = NULL;
SDL_Rect g_sprite_clips[4];

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
	if (g_texture != NULL) {
		LTEXTURE_destroy(g_texture);
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
	int clip_w, clip_h;

	g_texture = LTEXTURE_load(g_renderer, GRAPHICS_IMG_DIR"/texture.png");
	if (NULL == g_texture) {
		return false;
	}
	clip_w = g_texture->w / 2;
	clip_h = g_texture->h / 2;

	g_sprite_clips[0].x = 0;
	g_sprite_clips[0].y = 0;
	g_sprite_clips[0].w = clip_w;
	g_sprite_clips[0].h = clip_h;

	g_sprite_clips[1].x = clip_w;
	g_sprite_clips[1].y = 0;
	g_sprite_clips[1].w = clip_w;
	g_sprite_clips[1].h = clip_h;

	g_sprite_clips[2].x = 0;
	g_sprite_clips[2].y = clip_h;
	g_sprite_clips[2].w = clip_w;
	g_sprite_clips[2].h = clip_h;

	g_sprite_clips[3].x = clip_w;
	g_sprite_clips[3].y = clip_h;
	g_sprite_clips[3].w = clip_w;
	g_sprite_clips[3].h = clip_h;

	return true;
}

void GRAPHICS_update(void)
{
	SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
	SDL_RenderClear(g_renderer);

	LTEXTURE_render(g_texture, g_renderer, &g_sprite_clips[0],
			0, 0);
	LTEXTURE_render(g_texture, g_renderer, &g_sprite_clips[1],
			GRAPHICS_SCR_W - g_sprite_clips[1].w, 0);
	LTEXTURE_render(g_texture, g_renderer, &g_sprite_clips[2],
			0, GRAPHICS_SCR_H - g_sprite_clips[2].h);
	LTEXTURE_render(g_texture, g_renderer, &g_sprite_clips[3],
			GRAPHICS_SCR_W - g_sprite_clips[3].w,
			GRAPHICS_SCR_H - g_sprite_clips[3].h);

	SDL_RenderPresent(g_renderer);
	SDL_Delay(30);
}

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
LTexture *g_spriteset = NULL;
#define FRAME_NUM 2
SDL_Rect g_sprite_clips[FRAME_NUM];
int frame_index = 0;

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
	if (g_spriteset != NULL) {
		LTEXTURE_destroy(g_spriteset);
		g_spriteset = NULL;
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
	g_spriteset =
		LTEXTURE_load(g_renderer, GRAPHICS_IMG_DIR"/spritesheet.png");
	if (NULL == g_spriteset) {
		return false;
	}
	g_sprite_clips[0].x = 0;
	g_sprite_clips[0].y = 0;
	g_sprite_clips[0].w = g_spriteset->w / FRAME_NUM;
	g_sprite_clips[0].h = g_spriteset->h;

	g_sprite_clips[1].x = g_spriteset->w / FRAME_NUM;
	g_sprite_clips[1].y = 0;
	g_sprite_clips[1].w = g_spriteset->w / FRAME_NUM;
	g_sprite_clips[1].h = g_spriteset->h;
	return true;
}

void GRAPHICS_update(void)
{
	SDL_Rect dst_rect;
	dst_rect.x = 0;
	dst_rect.y = 0;
	dst_rect.w = (g_spriteset->w / FRAME_NUM) * 3;
	dst_rect.h = g_spriteset->h * 3;

	SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
	SDL_RenderClear(g_renderer);

	SDL_RenderCopy(g_renderer, g_spriteset->texture,
			&g_sprite_clips[frame_index], &dst_rect);
	frame_index++;
	frame_index %= FRAME_NUM;

	SDL_RenderPresent(g_renderer);
	SDL_Delay(100);
}

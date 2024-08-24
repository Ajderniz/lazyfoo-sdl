/*
 * Included at header:
 * ===================
 * stdbool.h
 */
#include <SDL2/SDL_mouse.h>
#include <stdlib.h> /* malloc, free */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>

#include "../include/graphics.h"

enum button_sprites {
	BUTTON_SPRITE_MOUSE_OUT = 0,
	BUTTON_SPRITE_MOUSE_OVER_MOTION,
	BUTTON_SPRITE_MOUSE_DOWN,
	BUTTON_SPRITE_MOUSE_UP,
	BUTTON_SPRITE_NUM
};

SDL_Window *g_window = NULL;
SDL_Renderer *g_renderer = NULL;
SDL_Texture *g_texture = NULL;
SDL_Rect g_dst_rect;
enum button_sprites g_sprite_index = BUTTON_SPRITE_MOUSE_OUT;

bool GRAPHICS_init(void)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		return false;
	}
	if (0 == IMG_Init(IMG_INIT_PNG)) {
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
	g_texture = IMG_LoadTexture(g_renderer, GRAPHICS_IMG_DIR"/button.png");
	if (NULL == g_texture) {
		return false;
	}
	SDL_QueryTexture(g_texture, NULL, NULL, &g_dst_rect.w, &g_dst_rect.h);
	g_dst_rect.w /= BUTTON_SPRITE_NUM;
	g_dst_rect.x = (GRAPHICS_SCR_W - g_dst_rect.w) / 2;
	g_dst_rect.y = (GRAPHICS_SCR_H - g_dst_rect.h) / 2;
	return true;
}

void GRAPHICS_update(void)
{
	SDL_Rect src_rect;

	SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
	SDL_RenderClear(g_renderer);

	src_rect.x = g_dst_rect.w * g_sprite_index;
	src_rect.y = 0;
	src_rect.w = g_dst_rect.w;
	src_rect.h = g_dst_rect.h;
	SDL_RenderCopy(g_renderer, g_texture, &src_rect, &g_dst_rect);

	SDL_RenderPresent(g_renderer);
	SDL_Delay(30);
}

void GRAPHICS_handle_mouse_event(SDL_Event *event)
{
	int x, y;
	SDL_GetMouseState(&x, &y);

	if (x < g_dst_rect.x || (g_dst_rect.x + g_dst_rect.w) < x ||
		y < g_dst_rect.y || (g_dst_rect.y + g_dst_rect.h) < y) {
		g_sprite_index = BUTTON_SPRITE_MOUSE_OUT;
		return;
	}

	switch(event->type) {
	case SDL_MOUSEMOTION:
		g_sprite_index = BUTTON_SPRITE_MOUSE_OVER_MOTION;
		break;
	case SDL_MOUSEBUTTONDOWN:
		g_sprite_index = BUTTON_SPRITE_MOUSE_DOWN;
		break;
	case SDL_MOUSEBUTTONUP:
		g_sprite_index = BUTTON_SPRITE_MOUSE_OVER_MOTION;
		break;
	}
}

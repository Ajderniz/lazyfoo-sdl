/*
 * Included at header:
 * ===================
 * stdbool.h
 */
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_mouse.h>
#include <stdlib.h> /* malloc, free */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>

#include "../include/graphics.h"

SDL_Window *g_window = NULL;
SDL_Renderer *g_renderer = NULL;
SDL_Texture *g_texture_press = NULL;
SDL_Texture *g_texture_up = NULL;
SDL_Texture *g_texture_down = NULL;
SDL_Texture *g_texture_left = NULL;
SDL_Texture *g_texture_right = NULL;
SDL_Rect g_dst_rect;

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
	if (g_texture_press != NULL) {
		SDL_DestroyTexture(g_texture_press);
		g_texture_press = NULL;
	}
	if (g_texture_up != NULL) {
		SDL_DestroyTexture(g_texture_up);
		g_texture_up = NULL;
	}
	if (g_texture_down != NULL) {
		SDL_DestroyTexture(g_texture_down);
		g_texture_down = NULL;
	}
	if (g_texture_left != NULL) {
		SDL_DestroyTexture(g_texture_left);
		g_texture_left = NULL;
	}
	if (g_texture_right != NULL) {
		SDL_DestroyTexture(g_texture_right);
		g_texture_right = NULL;
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
	g_texture_press =
		IMG_LoadTexture(g_renderer, GRAPHICS_IMG_DIR"/press.png");
	g_texture_up =
		IMG_LoadTexture(g_renderer, GRAPHICS_IMG_DIR"/up.png");
	g_texture_down =
		IMG_LoadTexture(g_renderer, GRAPHICS_IMG_DIR"/down.png");
	g_texture_left =
		IMG_LoadTexture(g_renderer, GRAPHICS_IMG_DIR"/left.png");
	g_texture_right =
		IMG_LoadTexture(g_renderer, GRAPHICS_IMG_DIR"/right.png");
	if (NULL == g_texture_press || NULL == g_texture_up ||
			NULL == g_texture_down || NULL == g_texture_left ||
			NULL == g_texture_right) {
		return false;
	}
	g_dst_rect.x = g_dst_rect.y = 0;
	g_dst_rect.w = GRAPHICS_SCR_W;
	g_dst_rect.h = GRAPHICS_SCR_H;

	return true;
}

void GRAPHICS_update(void)
{
	SDL_Texture *render_texture = NULL;
	const Uint8* current_key_states = SDL_GetKeyboardState(NULL);

	SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
	SDL_RenderClear(g_renderer);

	if (current_key_states[SDL_SCANCODE_UP]) {
		render_texture = g_texture_up;
	} else if (current_key_states[SDL_SCANCODE_DOWN]) {
		render_texture = g_texture_down;
	} else if (current_key_states[SDL_SCANCODE_LEFT]) {
		render_texture = g_texture_left;
	} else if (current_key_states[SDL_SCANCODE_RIGHT]) {
		render_texture = g_texture_right;
	} else {
		render_texture = g_texture_press;
	}
	SDL_RenderCopy(g_renderer, render_texture, NULL, &g_dst_rect);

	SDL_RenderPresent(g_renderer);
	SDL_Delay(30);
}

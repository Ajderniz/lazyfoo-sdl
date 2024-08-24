/*
 * Included at header:
 * ===================
 * stdbool.h
 */
#include <stdlib.h> /* malloc, free */
#include <math.h> /* atan2 */
#ifndef M_PI
#    define M_PI 3.14159265358979323846
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_joystick.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include "../include/graphics.h"

SDL_Window *g_window = NULL;
SDL_Renderer *g_renderer = NULL;
SDL_Texture *g_texture = NULL;
SDL_Joystick * g_game_controller = NULL;
SDL_Rect g_dst_rect;
int g_xdir, g_ydir;

bool GRAPHICS_init(void)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) {
		return false;
	}

	if (SDL_NumJoysticks() < 1) {
		printf("No joysticks connected\n");
	}
	g_game_controller = SDL_JoystickOpen(0);
	if (NULL == g_game_controller) {
		printf("Failed to open game controller: %s\n", SDL_GetError());
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
	if (g_game_controller != NULL) {
		SDL_JoystickClose(g_game_controller);
		g_game_controller = NULL;
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
	g_texture = IMG_LoadTexture(g_renderer, GRAPHICS_IMG_DIR"/arrow.png");
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
	double angle;

	SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
	SDL_RenderClear(g_renderer);

	angle = (g_xdir != 0 || g_ydir != 0) ?
		(atan2((double)g_ydir, (double)g_xdir)) * 180.0 / M_PI :
		0;

	SDL_RenderCopyEx
		(g_renderer, g_texture, NULL, &g_dst_rect,
		 angle, NULL, SDL_FLIP_NONE);

	SDL_RenderPresent(g_renderer);
	SDL_Delay(30);
}

void GRAPHICS_set_xdir(int xdir)
{
	g_xdir = xdir;
}

void GRAPHICS_set_ydir(int ydir)
{
	g_ydir = ydir;
}

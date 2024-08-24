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
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>

#include "../include/graphics.h"

SDL_Window *g_window = NULL;
SDL_Renderer *g_renderer = NULL;
SDL_Texture *g_texture = NULL;
SDL_Rect g_dst_rect;

TTF_Font *g_font = NULL;
SDL_Color g_white;

Uint32 g_start_time = 0;

bool GRAPHICS_init(void)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		return false;
	}

	if (0 == IMG_Init(IMG_INIT_PNG)) {
		return false;
	}

	if (TTF_Init() == -1) {
		return false;
	}

	g_window = SDL_CreateWindow("SDL TUTORIAL",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCR_W, SCR_H,
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
	IMG_Quit();
	SDL_Quit();
}

bool GRAPHICS_load_media(void)
{
	SDL_Surface *ttf_surface = NULL;

	g_font = TTF_OpenFont(TTF_DIR"/font.ttf", 28);
	if (NULL == g_font) {
		return false;
	}

	g_white.r = g_white.g = g_white.b = g_white.a = 255;
	ttf_surface = TTF_RenderText_Solid(g_font,
			"Press Enter to restart timer", g_white);
	if (NULL == ttf_surface) {
		return false;
	}

	g_texture = SDL_CreateTextureFromSurface(g_renderer, ttf_surface);
	SDL_FreeSurface(ttf_surface);
	ttf_surface = NULL;
	if (NULL == g_texture) {
		return false;
	}
	SDL_QueryTexture(g_texture, NULL, NULL, &g_dst_rect.w, &g_dst_rect.h);
	g_dst_rect.x = (SCR_W - g_dst_rect.w) / 2;
	g_dst_rect.y = 0;

	return true;
}

void GRAPHICS_update(void)
{
	char elapsed_time_str[50] = { '\0' };
	SDL_Surface *timer_surface = NULL;
	SDL_Texture *timer_texture = NULL;
	SDL_Rect timer_dst_rect;

	SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
	SDL_RenderClear(g_renderer);

	SDL_RenderCopy(g_renderer, g_texture, NULL, &g_dst_rect);

	sprintf(elapsed_time_str, "Milliseconds since start time: %u",
			SDL_GetTicks() - g_start_time);
	timer_surface = TTF_RenderText_Solid(g_font, elapsed_time_str, g_white);
	if (NULL == timer_surface) {
		return;
	}
	timer_texture = SDL_CreateTextureFromSurface(g_renderer, timer_surface);
	SDL_FreeSurface(timer_surface);
	timer_surface = NULL;
	if (NULL == timer_texture) {
		return;
	}
	SDL_QueryTexture(timer_texture, NULL, NULL,
			&timer_dst_rect.w, &timer_dst_rect.h);
	timer_dst_rect.x = (SCR_W - timer_dst_rect.w) / 2;
	timer_dst_rect.y = (SCR_H - timer_dst_rect.h) / 2;
	SDL_RenderCopy(g_renderer, timer_texture, NULL, &timer_dst_rect);

	SDL_RenderPresent(g_renderer);
	SDL_Delay(100);
}

void GRAPHICS_reset_timer()
{
	g_start_time = SDL_GetTicks();
}

#include "../include/screen.h"
/*
 * Included at header:
 * ===================
 * stdbool.h
 */
#include <stdlib.h> /* malloc, free */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include "../include/log.h"
#include "../include/shared.h"
#include "../include/timer.h"

extern struct Shared shared;

SDL_Window *g_window = NULL;
SDL_Renderer *g_renderer = NULL;

SDL_Texture *g_dot_texture = NULL;
SDL_Rect g_dot_dst_rect;

SDL_Texture *g_bg_texture = NULL;
SDL_Rect g_bg_dst_rect;

SDL_Rect g_camera;

bool SCREEN_init(void)
{
	LOG_DEBUG(("Initializing screen\n"));

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		LOG_ERROR(("Could not initialize SDL: %s\n", SDL_GetError()));
		return false;
	}

	if (0 == IMG_Init(IMG_INIT_PNG)) {
		LOG_ERROR(("Could not initialize IMG: %s\n", SDL_GetError()));
		return false;
	}

	g_window = SDL_CreateWindow("SDL TUTORIAL",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
	if (NULL == g_window) {
		LOG_ERROR(("Could not create window: %s\n", SDL_GetError()));
		return false;
	}

	g_renderer = SDL_CreateRenderer(g_window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (NULL == g_renderer) {
		LOG_ERROR(("Could not create renderer: %s\n", SDL_GetError()));
		return false;
	}

	return true;
}

void SCREEN_destroy(void)
{
	LOG_DEBUG(("Destroying screen\n"));
	if (g_dot_texture != NULL) {
		SDL_DestroyTexture(g_dot_texture);
		g_dot_texture = NULL;
	}
	if (g_bg_texture != NULL) {
		SDL_DestroyTexture(g_bg_texture);
		g_bg_texture = NULL;
	}
	if (g_renderer != NULL) {
		SDL_DestroyRenderer(g_renderer);
		g_renderer = NULL;
	}
	if (g_window != NULL) {
		SDL_DestroyWindow(g_window);
		g_window = NULL;
	}
	LOG_DEBUG(("Quitting SDL\n"));
	SDL_Quit();
}

bool SCREEN_load_media(void)
{
	SHARED_load();

	g_dot_texture = IMG_LoadTexture(g_renderer, IMG_DIR"/dot.png");
	if (NULL == g_dot_texture) {
		LOG_ERROR(("Could not load texture: %s\n", SDL_GetError()));
		return false;
	}
	SDL_QueryTexture(g_dot_texture, NULL, NULL,
			&g_dot_dst_rect.w, &g_dot_dst_rect.h);
	shared.dot.rect.w = g_dot_dst_rect.w;
	shared.dot.rect.h = g_dot_dst_rect.h;

	g_bg_texture = IMG_LoadTexture(g_renderer, IMG_DIR"/bg.png");
	if (NULL == g_dot_texture) {
		LOG_ERROR(("Could not load texture: %s\n", SDL_GetError()));
		return false;
	}
	g_bg_dst_rect.x = g_bg_dst_rect.y = 0;
	g_bg_dst_rect.w = SCREEN_WIDTH;
	g_bg_dst_rect.h = SCREEN_HEIGHT;

	g_camera.x = g_camera.y = 0;
	g_camera.w = SCREEN_WIDTH;
	g_camera.h = SCREEN_HEIGHT;

	return true;
}

void SCREEN_update(void)
{
	int frame_ticks;
	Timer cap_timer;

	TIMER_start(&cap_timer);

	DOT_move(&shared.dot);

	g_camera.x = (shared.dot.rect.x + (shared.dot.rect.w / 2))
			- (SCREEN_WIDTH / 2);
	g_camera.y = (shared.dot.rect.y + (shared.dot.rect.h / 2))
			- (SCREEN_HEIGHT / 2);
	if (g_camera.x < 0) {
		g_camera.x = 0;
	} else if ((LEVEL_WIDTH - g_camera.w) < g_camera.x) {
		g_camera.x = LEVEL_WIDTH - g_camera.w;
	}
	if (g_camera.y < 0) {
		g_camera.y = 0;
	} else if ((LEVEL_HEIGHT - g_camera.h) < g_camera.y) {
		g_camera.y = LEVEL_HEIGHT - g_camera.h;
	}

	SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
	SDL_RenderClear(g_renderer);

	SDL_RenderCopy(g_renderer, g_bg_texture, &g_camera, &g_bg_dst_rect);

	g_dot_dst_rect.x = shared.dot.rect.x - g_camera.x;
	g_dot_dst_rect.y = shared.dot.rect.y - g_camera.y;
	SDL_RenderCopy(g_renderer, g_dot_texture, NULL, &g_dot_dst_rect);

	SDL_RenderPresent(g_renderer);

	frame_ticks = TIMER_get_ticks(&cap_timer);
	if (frame_ticks < TICKS_A_FRAME) {
		SDL_Delay(TICKS_A_FRAME - frame_ticks);
	}
}
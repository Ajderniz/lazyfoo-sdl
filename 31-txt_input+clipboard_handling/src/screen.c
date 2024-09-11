#include "../include/screen.h"
/*
 * Included at header:
 * ===================
 * bool.h
 */
#include <stdlib.h> /* malloc, free */
#include <string.h> /* strcmp */

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>

#include "../include/log.h"
#include "../include/shared.h"
#include "../include/timer.h"

extern struct Shared shared;

SDL_Window *g_window = NULL;
SDL_Renderer *g_renderer = NULL;

SDL_Color g_white;
TTF_Font *g_font = NULL;

SDL_Texture *g_prompt_texture = NULL;
SDL_Rect g_prompt_dst_rect;

SDL_Texture *g_input_texture = NULL;
SDL_Rect g_input_dst_rect;

SDL_Texture * create_texture_from_string(const char *str)
{
	SDL_Surface *tmp_surface = NULL;
	SDL_Texture *return_texture = NULL;

	tmp_surface = TTF_RenderUTF8_Solid_Wrapped (g_font, str, g_white,
			SCREEN_WIDTH / 2);
	if (NULL == tmp_surface) {
		LOG_ERROR(("Could not render surface from text: %s\n",
					SDL_GetError()));
		return NULL;
	}

	return_texture = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
	SDL_FreeSurface(tmp_surface);
	tmp_surface = NULL;
	if (NULL == return_texture) {
		LOG_ERROR(("Could not create texture from temp texture: %s\n",
					SDL_GetError()));
		return NULL;
	}

	return return_texture;
}

Bool SCREEN_init(void)
{
	LOG_DEBUG(("Initializing screen\n"));

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		LOG_ERROR(("Could not initialize SDL: %s\n", SDL_GetError()));
		return FALSE;
	}
	if (TTF_Init() < 0) {
		LOG_ERROR(("Could not initialize SDL_ttf: %s\n",
					SDL_GetError()));
		return FALSE;
	}

	g_window = SDL_CreateWindow("SDL TUTORIAL",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
	if (NULL == g_window) {
		LOG_ERROR(("Could not create window: %s\n", SDL_GetError()));
		return FALSE;
	}

	g_renderer = SDL_CreateRenderer(g_window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (NULL == g_renderer) {
		LOG_ERROR(("Could not create renderer: %s\n", SDL_GetError()));
		return FALSE;
	}

	return TRUE;
}

void SCREEN_destroy(void)
{
	LOG_DEBUG(("Destroying screen\n"));
	SHARED_free();
	if (g_renderer != NULL) {
		SDL_DestroyRenderer(g_renderer);
		g_renderer = NULL;
	}
	if (g_window != NULL) {
		SDL_DestroyWindow(g_window);
		g_window = NULL;
	}

	LOG_DEBUG(("Quitting SDL\n"));
	TTF_Quit();
	SDL_Quit();
}

Bool SCREEN_load_media(void)
{
	if (FALSE == SHARED_init()) {
		LOG_ERROR(("Could not initialize shared resources\n"));
		return FALSE;
	}

	g_white.r = g_white.g = g_white.b = g_white.a = 255;
	g_font = TTF_OpenFont(TTF_DIR"/font.ttf", 18);
	if (NULL == g_font) {
		LOG_ERROR(("Could not open font: %s\n", SDL_GetError()));
		return FALSE;
	}

	g_prompt_texture = create_texture_from_string("Enter some text:");
	if (NULL == g_prompt_texture) {
		LOG_ERROR(("Could not create prompt texture from string\n"));
		return FALSE;
	}

	SDL_QueryTexture(g_prompt_texture, NULL, NULL,
			&g_prompt_dst_rect.w, &g_prompt_dst_rect.h);
	g_prompt_dst_rect.x = (SCREEN_WIDTH - g_prompt_dst_rect.w) / 2;
	g_prompt_dst_rect.y = 6;

	return TRUE;
}

void SCREEN_update(void)
{
	int frame_ticks;
	Timer cap_timer;

	TIMER_start(&cap_timer);

	SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
	SDL_RenderClear(g_renderer);

	SDL_RenderCopy(g_renderer, g_prompt_texture, NULL, &g_prompt_dst_rect);

	if (TRUE == shared.update_txt) {
		if (strcmp(shared.input_str, "") != 0) {

			g_input_texture =
				create_texture_from_string(shared.input_str);

			SDL_QueryTexture(g_input_texture, NULL, NULL,
					&g_input_dst_rect.w,
					&g_input_dst_rect.h);
			g_input_dst_rect.x =
				(SCREEN_WIDTH - g_input_dst_rect.w) / 2;
			g_input_dst_rect.y =
				(SCREEN_HEIGHT - g_input_dst_rect.h) / 2;

		} else {
			g_input_texture = create_texture_from_string(" ");
		}
		if (NULL == g_input_texture) {
			LOG_ERROR(("Could not create input texture from input "
						"string\n"));
		}
		shared.update_txt = FALSE;
	}

	if (SDL_RenderCopy(g_renderer, g_input_texture, NULL,
				&g_input_dst_rect) < 0) {
		LOG_ERROR(("Could not render input texture: %s\n",
					SDL_GetError()));
	}

	SDL_RenderPresent(g_renderer);

	frame_ticks = TIMER_get_ticks(&cap_timer);
	if (frame_ticks < TICKS_A_FRAME) {
		SDL_Delay(TICKS_A_FRAME - frame_ticks);
	}
}

#include "video.h"
/*
 * Included in header:
 * ===================
 * SDL_stdinc.h
 *
 * def.h
 */
#include "SDL.h"
#include "SDL_log.h"
#include "SDL_render.h"
#include "SDL_surface.h"
#include "SDL_ttf.h"
#include "SDL_video.h"

#include "shared.h"
#include "texture.h"

extern struct Shared shared;

SDL_Window *g_window = NULL;
SDL_Renderer *g_renderer = NULL;

SDL_Color g_white;
SDL_Color g_red;

TTF_Font *g_font = NULL;

SDL_Texture *g_prompt_texture = NULL;
SDL_Rect g_prompt_dst_rect;

#define INITIAL_Y 32
#define Y_STEP 20
SDL_Texture *g_data_textures[TOTAL_DATA] = { NULL };
SDL_Rect g_data_dst_rects[TOTAL_DATA];

Bool VIDEO_init(void)
{
	SDL_Log("Initializing video\n");

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_SYSTEM,
				"Could not initialize SDL: %s\n",
				SDL_GetError());
		return FALSE;
	}
	if (TTF_Init() < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_SYSTEM,
				"Could not initialize SDL_ttf: %s\n",
				SDL_GetError());
		return FALSE;
	}

	g_window = SDL_CreateWindow("SDL TUTORIAL",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			VIDEO_SCR_W, VIDEO_SCR_H,
			SDL_WINDOW_SHOWN);
	if (NULL == g_window) {
		SDL_LogError(SDL_LOG_CATEGORY_VIDEO,
				"Could not create window: %s\n",
				SDL_GetError());
		return FALSE;
	}

	g_renderer = SDL_CreateRenderer(g_window, -1,
			SDL_RENDERER_PRESENTVSYNC);
			
	if (NULL == g_renderer) {
		SDL_LogError(SDL_LOG_CATEGORY_VIDEO,
				"Could not create renderer: %s\n",
				SDL_GetError());
		return FALSE;
	}

	return TRUE;
}

void VIDEO_destroy(void)
{
	int i;

	SDL_Log("Freeing video resources\n");
	SHARED_free();
	if (g_font != NULL) {
		TTF_CloseFont(g_font);
		g_font = NULL;
	}
	if (g_prompt_texture != NULL) {
		SDL_DestroyTexture(g_prompt_texture);
		g_prompt_texture = NULL;
	}
	for (i = 0; i < TOTAL_DATA; i++) {
		if (g_data_textures[i] != NULL) {
			SDL_DestroyTexture(g_data_textures[i]);
			g_data_textures[i] = NULL;
		}
	}
	if (g_renderer != NULL) {
		SDL_DestroyRenderer(g_renderer);
		g_renderer = NULL;
	}
	if (g_window != NULL) {
		SDL_DestroyWindow(g_window);
		g_window = NULL;
	}

	SDL_Log("Quitting SDL and extensions\n");
	TTF_Quit();
	SDL_Quit();
}

Bool VIDEO_load_media(void)
{
	if (FALSE == SHARED_init()) {
		SDL_LogError(MY_LOG_CATEGORY_RES,
				"Could not initalize shared resources\n");
		return FALSE;
	}

	g_white.r = g_white.g = g_white.b = g_white.a = 255;
	g_red.r = g_red.a = 255;
	g_red.g = g_red.b = 0;

	g_font = TTF_OpenFont(TTF_DIR"/font.ttf", 18);
	if (NULL == g_font) {
		SDL_LogError(MY_LOG_CATEGORY_RES, "Could not open font: %s\n",
				SDL_GetError());
		return FALSE;
	}

	g_prompt_texture = TEXTURE_create_from_string(g_renderer, g_font,
			"Enter some data:", g_white);
	if (NULL == g_prompt_texture) {
		SDL_LogError(MY_LOG_CATEGORY_RES, "Could not create prompt "
				"texture from string\n");
		return FALSE;
	}
	SDL_QueryTexture(g_prompt_texture, NULL, NULL,
			&g_prompt_dst_rect.w, &g_prompt_dst_rect.h);
	g_prompt_dst_rect.x = (VIDEO_SCR_W - g_prompt_dst_rect.w) / 2;
	g_prompt_dst_rect.y = 6;

	return TRUE;
}

void VIDEO_update(void)
{
	int i;
	char tmp_str[32];
	SDL_Color color;

	SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
	SDL_RenderClear(g_renderer);

	SDL_RenderCopy(g_renderer, g_prompt_texture, NULL, &g_prompt_dst_rect);

	for (i = 0; i < TOTAL_DATA; i++) {
		if (TRUE == shared.update_data_texture[i]) {
			SDL_itoa(shared.data[i], tmp_str, 10);
			color = (i == shared.current_data) ? g_red : g_white;
			g_data_textures[i] = TEXTURE_create_from_string(
					g_renderer, g_font, tmp_str, color);
			if (NULL == g_data_textures[i]) {
				SDL_LogError(MY_LOG_CATEGORY_RES, "Could not "
						"create texture %d\n", i);
				continue;
			}
			SDL_QueryTexture(g_data_textures[i], NULL, NULL,
					&g_data_dst_rects[i].w,
					&g_data_dst_rects[i].h);
			g_data_dst_rects[i].x =
				(VIDEO_SCR_W - g_data_dst_rects[i].w) / 2;
			g_data_dst_rects[i].y = INITIAL_Y + (Y_STEP * i);

			shared.update_data_texture[i] = FALSE;
		}
		SDL_RenderCopy(g_renderer, g_data_textures[i], NULL,
				&g_data_dst_rects[i]);
	}

	SDL_RenderPresent(g_renderer);
}

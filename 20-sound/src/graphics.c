/*
 * Included at header:
 * ===================
 * stdbool.h
 */
#include <stdlib.h> /* malloc, free */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include "../include/graphics.h"

SDL_Window *g_window = NULL;
SDL_Renderer *g_renderer = NULL;
SDL_Texture *g_texture = NULL;
SDL_Rect g_dst_rect;

Mix_Music *g_music = NULL;
Mix_Chunk *g_sound = NULL;

bool GRAPHICS_init(void)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		return false;
	}

	if (0 == IMG_Init(IMG_INIT_PNG)) {
		return false;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
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
	if (g_music != NULL) {
		Mix_FreeMusic(g_music);
		g_music = NULL;
	}
	if (g_sound != NULL) {
		Mix_FreeChunk(g_sound);
		g_sound = NULL;
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
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool GRAPHICS_load_media(void)
{
	g_texture = IMG_LoadTexture(g_renderer, IMG_DIR"/texture.png");
	if (NULL == g_texture) {
		return false;
	}
	g_dst_rect.x = g_dst_rect.y = 0;
	g_dst_rect.w = SCR_W;
	g_dst_rect.h = SCR_H;

	g_music = Mix_LoadMUS(AUD_DIR"/music.mp3");
	g_sound = Mix_LoadWAV(AUD_DIR"/sound.wav");
	if (NULL == g_music || NULL == g_sound) {
		return false;
	}

	return true;
}

void GRAPHICS_update(void)
{
	SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
	SDL_RenderClear(g_renderer);

	SDL_RenderCopy(g_renderer, g_texture, NULL, &g_dst_rect);

	SDL_RenderPresent(g_renderer);
	SDL_Delay(30);
}

void GRAPHICS_play_music(void)
{
	if (0 == Mix_PlayingMusic()) {
		Mix_PlayMusic(g_music, -1);
	} else if (1 == Mix_PausedMusic()) {
		Mix_ResumeMusic();
	} else {
		Mix_PauseMusic();
	}
}

void GRAPHICS_stop_music(void)
{
	Mix_HaltMusic();
}

void GRAPHICS_play_sound(void)
{
	Mix_PlayChannel(-1, g_sound, 0);
}

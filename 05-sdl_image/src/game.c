/*
 * Included at header:
 * ===================
 * stdbool.h
 */
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>

#include "../include/game.h"

Game * GAME_init(void)
{
	Game *this = NULL;

	this = malloc(sizeof(Game));
	if (NULL == this) {
		return NULL;
	}
	this->window = NULL;
	this->window_surface = NULL;
	this->stretched_surface = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		GAME_exit_and_destroy(this);
		return NULL;
	}

	this->window = SDL_CreateWindow("SDL TUTORIAL",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			GAME_SCR_W, GAME_SCR_H,
			SDL_WINDOW_SHOWN);
	if (NULL == this->window) {
		GAME_exit_and_destroy(this);
		return NULL;
	}

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))  {
		GAME_exit_and_destroy(this);
		return NULL;
	}

	this->window_surface = SDL_GetWindowSurface(this->window);

	return this;
}

void GAME_exit_and_destroy(Game *this)
{
	if (NULL == this) {
		return;
	}
	if (this->stretched_surface != NULL) {
		SDL_FreeSurface(this->stretched_surface);
		this->stretched_surface = NULL;
	}
	if (this->window != NULL) {
		SDL_DestroyWindow(this->window);
		this->window = NULL;
		this->window_surface = NULL;
	}
	free(this);
	SDL_Quit();
}

bool GAME_load_media(Game *this)
{
	this->stretched_surface = load_surface(this, IMG_DIR"/img.png");
	if (NULL == this) {
		return false;
	}
	return true;
}

SDL_Surface * load_surface(Game* this, char *path)
{
	SDL_Surface *loaded_surface = NULL;
	SDL_Surface *optimized_surface = NULL;

	loaded_surface = IMG_Load(path);
	if (NULL == loaded_surface) {
		return NULL;
	}

	optimized_surface = SDL_ConvertSurface
		(loaded_surface, this->window_surface->format, 0);
	if (NULL == optimized_surface) {
		return NULL;
	}

	SDL_FreeSurface(loaded_surface);
	loaded_surface = NULL;

	return optimized_surface;
}

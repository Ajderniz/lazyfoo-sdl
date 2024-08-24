/*
 * Included in header:
 * ===================
 * bool.h
 */
#include <stdlib.h> /* malloc, free */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>

#include "../include/ltexture.h"

LTexture * LTEXTURE_init(void)
{
	LTexture *this = malloc(sizeof(LTexture));
	if (NULL == this) {
		return NULL;
	}
	this->texture = NULL;
	this->w = 0;
	this->h = 0;
	return this;
}

void LTEXTURE_destroy(LTexture *this) {
	if (NULL == this) {
		return;
	}
	if (this->texture != NULL) {
		SDL_DestroyTexture(this->texture);
		this->texture = NULL;
		this->w = this->h = 0;
	}
	free(this);
}

LTexture * LTEXTURE_load(SDL_Renderer *renderer, char *path)
{
	LTexture *this = NULL;
	SDL_Surface *loaded_surface = NULL;

	this = malloc(sizeof(LTexture));
	if (NULL == this) {
		return NULL;
	}
	this->texture = NULL;
	this->w = 0;
	this->h = 0;

	loaded_surface = IMG_Load(path);
	if (NULL == loaded_surface) {
		return NULL;
	}
	SDL_SetColorKey(loaded_surface, SDL_TRUE,
			SDL_MapRGB(loaded_surface->format, 255, 0, 255));

	this->texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
	if (NULL == this->texture) {
		return NULL;
	}

	this->w = loaded_surface->w;
	this->h = loaded_surface->h;

	SDL_FreeSurface(loaded_surface);
	loaded_surface = NULL;

	return this;
}

void LTEXTURE_render
(LTexture* this, SDL_Renderer *renderer, SDL_Rect *clip, int x, int y)
{
	SDL_Rect render_quad;

	render_quad.x = x;
	render_quad.y = y;
	render_quad.w = this->w;
	render_quad.h = this->h;

	if (clip != NULL) {
		render_quad.w = clip->w;
		render_quad.h = clip->h;
	}
	SDL_RenderCopy(renderer, this->texture, clip, &render_quad);
}

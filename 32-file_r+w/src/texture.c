#include "texture.h"
/*
 * Included in header:
 * ===================
 * SDL_render.h
 * SDL_ttf.h
 */
#include "SDL_log.h"

#include "def.h"
#include "video.h"

SDL_Texture * TEXTURE_create_from_string
(SDL_Renderer *renderer, TTF_Font *font, const char *str, SDL_Color color)
{
	SDL_Surface *tmp_surface = NULL;
	SDL_Texture *return_texture = NULL;

	tmp_surface = TTF_RenderUTF8_Solid_Wrapped(font, str, color,
			VIDEO_SCR_W / 2);
	if (NULL == tmp_surface) {
		SDL_LogError(SDL_LOG_CATEGORY_RENDER,
				"Could not render surface from text: %s\n",
				SDL_GetError());
		return NULL;
	}

	return_texture = SDL_CreateTextureFromSurface(renderer, tmp_surface);
	SDL_FreeSurface(tmp_surface);
	tmp_surface = NULL;
	if (NULL == return_texture) {
		SDL_LogError(SDL_LOG_CATEGORY_RENDER,
				"Could not create texture from temp surface: "
				"%s\n", SDL_GetError());
		return NULL;
	}

	return return_texture;
}

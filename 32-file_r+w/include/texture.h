#ifndef TEXTURE_H
#define TEXTURE_H

#include "SDL_render.h"
#include "SDL_ttf.h"

SDL_Texture * TEXTURE_create_from_string
(SDL_Renderer*, TTF_Font*, const char *str, SDL_Color);

#endif

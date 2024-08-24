#ifndef LTEXTURE_H
#define LTEXTURE_H

#include <stdbool.h>

struct SDL_Rect;
struct SDL_Renderer;
struct SDL_Texture;

typedef struct {
	struct SDL_Texture *texture;
	int w;
	int h;
} LTexture;

LTexture * LTEXTURE_load(struct SDL_Renderer*, char *path);
void LTEXTURE_destroy(LTexture*);

void LTEXTURE_render
(LTexture*, struct SDL_Renderer*, int x, int y, int w, int h);

#endif

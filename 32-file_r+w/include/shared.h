#ifndef SHARED_H
#define SHARED_H

#include "SDL_render.h"

#include "def.h"

#define TOTAL_DATA 10

struct Shared {
	Sint32 data[TOTAL_DATA];
	Sint32 current_data;
	Bool update_data_texture[TOTAL_DATA];
};

Bool SHARED_init(void);
void SHARED_free(void);

#endif

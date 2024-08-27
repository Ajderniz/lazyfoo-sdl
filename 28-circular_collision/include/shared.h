#ifndef RES_H
#define RES_H

#define RES_DIR "res"
#define AUD_DIR RES_DIR"/aud"
#define IMG_DIR RES_DIR"/img"
#define TTF_DIR RES_DIR"/ttf"

#include "../include/dot.h"

struct Shared {
	Dot dot;
	Dot other_dot;
	SDL_Rect wall;
};

void SHARED_load(void);

#endif

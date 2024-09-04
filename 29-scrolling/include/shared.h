#ifndef RES_H
#define RES_H

#include "../include/dot.h"

#define RES_DIR "res"
#define AUD_DIR RES_DIR"/aud"
#define IMG_DIR RES_DIR"/img"
#define TTF_DIR RES_DIR"/ttf"

#define LEVEL_WIDTH 1280
#define LEVEL_HEIGHT 1024

struct Shared {
	Dot dot;
};

void SHARED_load(void);

#endif

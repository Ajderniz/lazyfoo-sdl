#ifndef VIDEO_H
#define VIDEO_H

#include "SDL_stdinc.h"

#include "def.h"

#define VIDEO_SCR_W 640
#define VIDEO_SCR_H 480

#define VIDEO_FPS 25
#define TICKS_A_FRAME 1000 / VIDEO_FPS

Bool VIDEO_init(void);
void VIDEO_destroy(void);

Bool VIDEO_load_media(void);
void VIDEO_update(void);

#endif

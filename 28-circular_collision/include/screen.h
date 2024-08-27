#ifndef SCREEN_H
#define SCREEN_H

#include <stdbool.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define SCREEN_FPS 30
#define TICKS_A_FRAME 1000 / SCREEN_FPS

bool SCREEN_init(void);
void SCREEN_destroy(void);

bool SCREEN_load_media(void);
void SCREEN_update(void);

void SCREEN_line(int x1, int y1, int x2, int y2);

#endif

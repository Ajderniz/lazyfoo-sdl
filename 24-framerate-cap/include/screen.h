#ifndef SCREEN_H
#define SCREEN_H

#include <stdbool.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define RES_DIR "res"
#define IMG_DIR RES_DIR"/img"
#define TTF_DIR RES_DIR"/ttf"

bool SCREEN_init(void);
void SCREEN_destroy(void);

bool SCREEN_load_media(void);
void SCREEN_update(void);

#endif

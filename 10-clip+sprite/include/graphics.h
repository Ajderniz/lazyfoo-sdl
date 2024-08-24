#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdbool.h>

#define GRAPHICS_SCR_W 640
#define GRAPHICS_SCR_H 480

#define GRAPHICS_IMG_DIR "res/img"

bool GRAPHICS_init(void);
void GRAPHICS_destroy(void);

bool GRAPHICS_load_media(void);
void GRAPHICS_update(void);

#endif

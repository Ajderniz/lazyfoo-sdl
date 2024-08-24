#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdbool.h>

#define SCR_W 640
#define SCR_H 480

#define RES_DIR "res"
#define IMG_DIR RES_DIR"/img"
#define AUD_DIR RES_DIR"/aud"

bool GRAPHICS_init(void);
void GRAPHICS_destroy(void);

bool GRAPHICS_load_media(void);
void GRAPHICS_update(void);

void GRAPHICS_play_music(void);
void GRAPHICS_stop_music(void);
void GRAPHICS_play_sound(void);

#endif

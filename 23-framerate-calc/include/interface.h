#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdbool.h>

#define SCR_W 640
#define SCR_H 480

#define RES_DIR "res"
#define IMG_DIR RES_DIR"/img"
#define TTF_DIR RES_DIR"/ttf"

bool INTERFACE_init(void);
void INTERFACE_destroy(void);

bool INTERFACE_load_media(void);
void INTERFACE_update(void);

#endif

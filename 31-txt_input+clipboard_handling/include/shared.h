#ifndef RES_H
#define RES_H

#include "../include/bool.h"

#define RES_DIR "res"
#define AUD_DIR RES_DIR"/aud"
#define IMG_DIR RES_DIR"/img"
#define TTF_DIR RES_DIR"/ttf"

struct Shared {
	char *input_str;
	unsigned int str_max_len;
	Bool update_txt;
};

Bool SHARED_init(void);
void SHARED_free(void);

#endif

#ifndef DEF_H
#define DEF_H

#include "SDL_log.h"
#include "SDL_stdinc.h"

#define RES_DIR "res"
#define AUD_DIR RES_DIR"/aud"
#define IMG_DIR RES_DIR"/img"
#define TTF_DIR RES_DIR"/ttf"
#define BIN_DIR RES_DIR"/bin"

typedef SDL_bool Bool;
#define TRUE SDL_TRUE
#define FALSE SDL_FALSE

enum {
	MY_LOG_CATEGORY_RES = SDL_LOG_CATEGORY_CUSTOM
};

#endif

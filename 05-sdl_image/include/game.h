#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#define GAME_SCR_W 640
#define GAME_SCR_H 480

#define IMG_DIR "res/img"

struct SDL_Window;
struct SDL_Surface;

typedef struct {
	struct SDL_Window *window;
	struct SDL_Surface *window_surface;
	struct SDL_Surface *stretched_surface;
} Game;

Game * GAME_init(void);
void GAME_exit_and_destroy(Game*);
bool GAME_load_media(Game*);
SDL_Surface * load_surface(Game*, char *path);

#endif

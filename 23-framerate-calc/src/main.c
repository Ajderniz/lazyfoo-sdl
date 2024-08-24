#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>

#include "../include/game.h"

int main(void)
{
	if (false == GAME_init()) {
		GAME_fini();
		exit(1);
	}
	GAME_loop();
	GAME_fini();
	return 0;
}

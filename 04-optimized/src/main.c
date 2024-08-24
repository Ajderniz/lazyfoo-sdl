#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>

#include "../include/game.h"

int main(void)
{
	Game *game = NULL;
	bool running;
	SDL_Event event;
	SDL_Rect stretch_rect;

	game = GAME_init();
	if (NULL == game) {
		GAME_exit_and_destroy(game);
		exit(1);
	}

	if (false == GAME_load_media(game)) {
		GAME_exit_and_destroy(game);
		exit(1);
	}

	running = true;
	while (true == running) {
		while (SDL_PollEvent(&event)) {
			switch(event.type) {
			case SDL_QUIT:
				running = false;
				break;
			default:
				break;
			}
		}
		stretch_rect.x = stretch_rect.y = 0;
		stretch_rect.w = GAME_SCR_W;
		stretch_rect.h = GAME_SCR_H;
		SDL_BlitScaled(game->stretched_surface, NULL,
				game->window_surface, &stretch_rect);
		SDL_UpdateWindowSurface(game->window);

		SDL_Delay(30);
	}

	GAME_exit_and_destroy(game);

	return 0;
}

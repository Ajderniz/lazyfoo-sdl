#include <stdbool.h>
#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

#define SCR_W 640
#define SCR_H 480

struct game {
	SDL_Window *window;
	SDL_Surface *surface;
	SDL_Surface *img_surface;
};

struct game * game_init(void)
{
	struct game *this = NULL;
	this = malloc(sizeof(struct game));
	if (NULL == this) {
		return NULL;
	}

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		free(this);
		this = NULL;
		return NULL;
	}
	this->window = SDL_CreateWindow("SDL TUTORIAL",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCR_W, SCR_H,
			SDL_WINDOW_SHOWN);
	if (NULL == this->window) {
		SDL_DestroyWindow(this->window);
		this->window = NULL;
		free(this);
		this = NULL;
		return NULL;
	}
	this->surface = SDL_GetWindowSurface(this->window);
	
	return this;
}

void game_exit(struct game *this)
{
	SDL_FreeSurface(this->img_surface);
	this->img_surface = NULL;
	SDL_DestroyWindow(this->window);
	this->window = NULL;
	free(this);
	SDL_Quit();
}

bool game_load_media(struct game *this)
{
	this->img_surface = SDL_LoadBMP("img.bmp");
	return (this->img_surface != NULL) ? true : false;
}

int main(void)
{
	struct game *game = NULL;
	SDL_Event event;
	bool running;

	game = game_init();
	if (NULL == game) {
		game_exit(game);
		exit(1);
	}

	if (false == game_load_media(game)) {
		game_exit(game);
		exit(1);
	}

	SDL_BlitSurface(game->img_surface, NULL, game->surface, NULL);
	SDL_UpdateWindowSurface(game->window);

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
		SDL_Delay(30);
	}

	game_exit(game);

	return 0;
}

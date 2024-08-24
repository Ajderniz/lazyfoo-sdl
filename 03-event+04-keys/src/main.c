#include <stdbool.h>
#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

#define SCR_W 640
#define SCR_H 480

enum key_press_surfaces {
	KEY_PRESS_SURFACE_DEFAULT = 0,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_NUM
};

struct game {
	SDL_Window *window;
	SDL_Surface *surface;
	SDL_Surface *current_surface;
	SDL_Surface *surfaces[KEY_PRESS_SURFACE_NUM];
};

struct game * game_init(void);
void game_exit(struct game*);
bool game_load_media(struct game*);

struct game * game_init(void)
{
	int i;
	struct game *this = NULL;
	this = malloc(sizeof(struct game));
	if (NULL == this) {
		return NULL;
	}
	this->window = NULL;
	this->surface = NULL;
	this->current_surface = NULL;
	for (i = 0; i < KEY_PRESS_SURFACE_NUM; i++) {
		this->surfaces[i] = NULL;
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
	SDL_FreeSurface(this->current_surface);
	this->current_surface = NULL;
	SDL_DestroyWindow(this->window);
	this->window = NULL;
	free(this);
	SDL_Quit();
}

bool game_load_media(struct game *this) {
	this->surfaces[KEY_PRESS_SURFACE_DEFAULT] = SDL_LoadBMP("default.bmp");
	this->surfaces[KEY_PRESS_SURFACE_UP] = SDL_LoadBMP("up.bmp");
	this->surfaces[KEY_PRESS_SURFACE_DOWN] = SDL_LoadBMP("down.bmp");
	this->surfaces[KEY_PRESS_SURFACE_LEFT] = SDL_LoadBMP("left.bmp");
	this->surfaces[KEY_PRESS_SURFACE_RIGHT] = SDL_LoadBMP("right.bmp");
	if (NULL == this->surfaces[KEY_PRESS_SURFACE_DEFAULT] ||
		NULL == this->surfaces[KEY_PRESS_SURFACE_UP] ||
		NULL == this->surfaces[KEY_PRESS_SURFACE_DOWN] ||
		NULL == this->surfaces[KEY_PRESS_SURFACE_LEFT] ||
		NULL == this->surfaces[KEY_PRESS_SURFACE_RIGHT]) {
		return false;
	}
	return true;
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

	running = true;
	while (true == running) {
		while (SDL_PollEvent(&event)) {
			switch(event.type) {
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_UP:
					game->current_surface = game->surfaces
						[KEY_PRESS_SURFACE_UP];
					break;
				case SDLK_DOWN:
					game->current_surface = game->surfaces
						[KEY_PRESS_SURFACE_DOWN];
					break;
				case SDLK_LEFT:
					game->current_surface = game->surfaces
						[KEY_PRESS_SURFACE_LEFT];
					break;
				case SDLK_RIGHT:
					game->current_surface = game->surfaces
						[KEY_PRESS_SURFACE_RIGHT];
					break;
				default:
					break;
				}
				break;
			case SDL_KEYUP:
				game->current_surface = game->surfaces
					[KEY_PRESS_SURFACE_DEFAULT];
				break;
			default:
				break;
			}
		}
		SDL_BlitSurface
			(game->current_surface, NULL, game->surface, NULL);
		SDL_UpdateWindowSurface(game->window);

		SDL_Delay(30);
	}

	game_exit(game);

	return 0;
}

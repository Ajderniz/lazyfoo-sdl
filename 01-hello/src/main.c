#include <stdbool.h>
#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

#define SCR_W 640
#define SCR_H 480

int main(void)
{
	SDL_Window *window = NULL;
	SDL_Surface *surface = NULL;
	SDL_Event event;
	bool running;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		exit(1);
	}

	window = SDL_CreateWindow("SDL TUTORIAL",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCR_W, SCR_H,
			SDL_WINDOW_SHOWN);
	if (NULL == window) {
		exit(1);
	}

	surface = SDL_GetWindowSurface(window);

	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 255, 255));
	SDL_UpdateWindowSurface(window);

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

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

#include <SDL2/SDL_events.h>

#include "../include/input.h"

enum Continue INPUT_handle(void)
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (SDL_QUIT == event.type) {
			return INPUT_QUIT;
		}
	}
	return INPUT_CONTINUE;
}

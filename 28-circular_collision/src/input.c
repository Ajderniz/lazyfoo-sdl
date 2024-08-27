#include <SDL2/SDL_events.h>

#include "../include/input.h"
#include "../include/shared.h"

extern struct Shared shared;

enum Continue INPUT_handle(void)
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (SDL_QUIT == event.type) {
			return INPUT_QUIT;
		} else if ((SDL_KEYDOWN == event.type ||
				SDL_KEYUP == event.type) &&
				0 == event.key.repeat) {
			DOT_handle_event(&shared.dot, &event);
		}
	}
	return INPUT_CONTINUE;
}

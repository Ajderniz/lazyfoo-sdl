#include "input.h"

#include "SDL_events.h"
#include "SDL_keyboard.h"
#include "SDL_log.h"

#include "shared.h"

extern struct Shared shared;

enum INPUT_State INPUT_handle(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (SDL_QUIT == event.type) {
			return INPUT_QUIT;
		} else if (SDL_KEYDOWN == event.type) {
			shared.update_data_texture[shared.current_data] = TRUE;
			switch (event.key.keysym.scancode) {
			case SDL_SCANCODE_UP:
				shared.current_data--;
				if (shared.current_data < 0) {
					shared.current_data = TOTAL_DATA - 1;
				}
				break;
			case SDL_SCANCODE_DOWN:
				shared.current_data++;
				shared.current_data %= TOTAL_DATA;
				break;
			case SDL_SCANCODE_LEFT:
				shared.data[shared.current_data]--;
				break;
			case SDL_SCANCODE_RIGHT:
				shared.data[shared.current_data]++;
				break;
			default: break;
			}
			shared.update_data_texture[shared.current_data] = TRUE;
		}
	}

	return INPUT_CONTINUE;
}

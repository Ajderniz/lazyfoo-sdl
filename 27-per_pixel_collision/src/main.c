#include <stdbool.h>
#include <stdlib.h> /* exit */

#include <SDL2/SDL.h> /* Delay */

#include "../include/input.h"
#include "../include/log.h"
#include "../include/shared.h"
#include "../include/screen.h"

bool init(void);
void fini(void);
void loop(void);

struct Shared shared;

int main(void)
{
	if (false == init()) {
		LOG_ERROR(("Could not initialize system\n"));
		fini();
		exit(1);
	}
	loop();
	fini();
	return 0;
}

bool init(void)
{
	if (false == SCREEN_init()) {
		LOG_ERROR(("Could not initialize screen\n"));
		return false;
	}
	if (false == SCREEN_load_media()) {
		LOG_ERROR(("Could not load media\n"));
		return false;
	}
	return true;
}

void fini(void)
{
	LOG_DEBUG(("Quitting\n"));
	SCREEN_destroy();
}

void loop(void)
{
	bool running;

	running = true;
	while (true == running) {
		if (INPUT_QUIT == INPUT_handle()) {
			LOG_DEBUG(("Received INPUT_QUIT\n"));
			running = false;
		}
		SCREEN_update();
	}
}

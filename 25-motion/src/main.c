#include <stdbool.h>
#include <stdlib.h> /* exit */

#include <SDL2/SDL.h> /* Delay */

#include "../include/input.h"
#include "../include/res.h"
#include "../include/screen.h"

bool init(void);
void fini(void);
void loop(void);

struct Res res;

int main(void)
{
	if (false == init()) {
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
		return false;
	}
	if (false == SCREEN_load_media()) {
		return false;
	}
	return true;
}

void fini(void)
{
	SCREEN_destroy();
}

void loop(void)
{
	bool running;

	running = true;
	while (true == running) {
		if (INPUT_QUIT == INPUT_handle()) {
			running = false;
		}

		SCREEN_update();
	}
}

#include <stdbool.h>
#include <stdlib.h> /* exit */

#include <SDL2/SDL.h> /* Delay */

#include "../include/input.h"
#include "../include/screen.h"
#include "../include/timer.h"

#define FPS 30
#define TICKS_FRAME 1000 / FPS

bool init(void);
void fini(void);
void loop(void);

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
	Timer cap_timer;

	running = true;
	while (true == running) {
		int frame_ticks;

		TIMER_start(&cap_timer);

		if (INPUT_QUIT == INPUT_handle()) {
			running = false;
		}

		SCREEN_update();

		frame_ticks = TIMER_get_ticks(&cap_timer);
		if (frame_ticks < TICKS_FRAME) {
			SDL_Delay(TICKS_FRAME - frame_ticks);
		}
	}
}

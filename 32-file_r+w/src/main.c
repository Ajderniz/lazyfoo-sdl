#include "SDL.h"
#include "SDL_stdinc.h"
#include "SDL_log.h"

#include "input.h"
#include "shared.h"
#include "video.h"

struct Shared shared;

Bool init(void)
{
	if (FALSE == VIDEO_init()) {
		SDL_LogError(SDL_LOG_CATEGORY_SYSTEM,
				"Could not initialize screen\n");
		return FALSE;
	}
	if (FALSE == VIDEO_load_media()) {
		SDL_LogError(SDL_LOG_CATEGORY_SYSTEM,
				"Could not load video media\n");
		return FALSE;
	}
	return TRUE;
}

void fini(void)
{
	SDL_Log("Exitting\n");
	VIDEO_destroy();
}

void loop(void)
{
	Bool running;

	running = TRUE;
	while (TRUE == running) {
		if (INPUT_QUIT == INPUT_handle()) {
			SDL_Log("Received quit signal\n");
			running = FALSE;
		}
		VIDEO_update();
	}
}

int main(int argc, char **argv)
{
	if (FALSE == init()) {
		SDL_LogError(SDL_LOG_CATEGORY_SYSTEM,
				"Could not initialize system\n");
		fini();
		return 1;
	}
	loop();
	fini();
	return 0;
}

#include <stdlib.h> /* exit */

#include "../include/bool.h"
#include "../include/input.h"
#include "../include/log.h"
#include "../include/screen.h"
#include "../include/shared.h"

Bool init(void);
void fini(void);
void loop(void);

struct Shared shared;

int main(void)
{
	if (FALSE == init()) {
		LOG_ERROR(("Could not initialize system\n"));
		fini();
		exit(1);
	}
	loop();
	fini();
	return 0;
}

Bool init(void)
{
	if (FALSE == SCREEN_init()) {
		LOG_ERROR(("Could not initialize screen\n"));
		return FALSE;
	}
	if (FALSE == SCREEN_load_media()) {
		LOG_ERROR(("Could not load media\n"));
		return FALSE;
	}
	return TRUE;
}

void fini(void)
{
	LOG_DEBUG(("Quitting\n"));
	SCREEN_destroy();
}

void loop(void)
{
	Bool running;

	running = TRUE;
	while (TRUE == running) {
		if (INPUT_QUIT == INPUT_handle()) {
			LOG_DEBUG(("Received INPUT_QUIT\n"));
			running = FALSE;
		}
		SCREEN_update();
	}
}

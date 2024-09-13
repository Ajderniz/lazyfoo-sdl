#include "shared.h"
/*
 * Included in header:
 * ===================
 * def.h
 */
#include "SDL_log.h"
#include "SDL_rwops.h"

extern struct Shared shared;

Bool SHARED_init(void)
{
	int i;
	SDL_RWops *file = NULL;

	SDL_Log("Initializing shared resources\n");

	file = SDL_RWFromFile(BIN_DIR"/nums.bin", "r+b");
	if (NULL == file) {
		SDL_LogWarn(MY_LOG_CATEGORY_RES, "Could not open file: %s\n",
				SDL_GetError());
		SDL_Log("Creating file\n");
		file = SDL_RWFromFile(BIN_DIR"/nums.bin", "w+b");
		if (NULL == file) {
			SDL_LogError(MY_LOG_CATEGORY_RES, "Could not create "
					"file: %s\n", SDL_GetError());
			return FALSE;
		}
		for (i = 0; i < TOTAL_DATA; i++) {
			shared.data[i] = 0;
			SDL_RWwrite(file, &shared.data[i], sizeof(Sint32), 1);
			shared.update_data_texture[i] = TRUE;
		}
	} else {
		SDL_Log("Reading file\n");
		for (i = 0; i < TOTAL_DATA; i++) {
			SDL_RWread(file, &shared.data[i], sizeof(Sint32), 1);
			shared.update_data_texture[i] = TRUE;
		}
	}
	SDL_RWclose(file);
	file = NULL;

	shared.current_data = 0;

	return TRUE;
}

void SHARED_free(void)
{
	int i;
	SDL_RWops *file = NULL;

	SDL_Log("Freeing shared resources\n");

	file = SDL_RWFromFile(BIN_DIR"/nums.bin", "w+b");
	if (NULL == file) {
		SDL_LogError(MY_LOG_CATEGORY_RES, "Could not open file for "
				"saving: %s\n",
				SDL_GetError());
		return;
	}
	for (i = 0; i < TOTAL_DATA; i++) {
		SDL_RWwrite(file, &shared.data[i], sizeof(Sint32), 1);
	}
	SDL_RWclose(file);
	file = NULL;
}

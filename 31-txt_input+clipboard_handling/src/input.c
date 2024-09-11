#include "../include/input.h"

#include <stdlib.h> /* calloc, free */
#include <string.h> /* strlen */

#include <SDL2/SDL_clipboard.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>

#include "../include/log.h"
#include "../include/shared.h"

extern struct Shared shared;

enum INPUT_State INPUT_handle(void)
{
	SDL_Event event;

	unsigned int str_len;
	char *tmp_str = NULL;

	SDL_StartTextInput();
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			return INPUT_QUIT;
			break;
		case SDL_KEYDOWN:
			str_len = strlen(shared.input_str);
			if (SDLK_BACKSPACE == event.key.keysym.sym &&
					str_len > 0) {

				shared.input_str[str_len - 1] = '\0';
				shared.update_txt = TRUE;

			} else if ((SDL_GetModState() & KMOD_CTRL) != 0 &&
					SDLK_c == event.key.keysym.sym) {

				SDL_SetClipboardText(shared.input_str);
				shared.update_txt = TRUE;

			} else if ((SDL_GetModState() & KMOD_CTRL) != 0 &&
					SDLK_v == event.key.keysym.sym) {

				tmp_str = SDL_GetClipboardText();

				str_len = strlen(tmp_str);
				if (shared.str_max_len < str_len + 1) {
					shared.str_max_len = str_len + 1;
					free(shared.input_str);
					shared.input_str = NULL;
					shared.input_str =
						calloc(shared.str_max_len,
							sizeof(char));
					if (NULL == shared.input_str) {
						LOG_ERROR(("Could not allocate "
								"memory for "
								"copy\n"));
						SDL_free(tmp_str);
						return INPUT_QUIT;
						break;
					}
				}
				strcpy(shared.input_str, tmp_str);

				SDL_free(tmp_str);
				tmp_str = NULL;

				shared.update_txt = TRUE;
			}
			break;
		case SDL_TEXTINPUT:
			if ((SDL_GetModState() & KMOD_CTRL) != 0 &&
					(event.text.text[0] == 'c' ||
					 event.text.text[0] == 'C' ||
					 event.text.text[0] == 'v' ||
					 event.text.text[0] == 'V')) {
				break;
			}

			if (shared.str_max_len < (strlen(shared.input_str) + 
						strlen(event.text.text) + 1)) {

				tmp_str = calloc(strlen(shared.input_str) + 1,
						sizeof(char));
				if (NULL == tmp_str) {
					LOG_ERROR(("Could not allocate memory "
							"for temp string\n"));
					return INPUT_QUIT;
				}
				strcpy(tmp_str, shared.input_str);

				free(shared.input_str);
				shared.input_str = NULL;

				shared.str_max_len *= 2;
				shared.input_str = calloc(shared.str_max_len,
						sizeof(char));
				if (NULL == shared.input_str) {
					LOG_ERROR(("Could not allocate memory "
							"for input string\n"));
					return INPUT_QUIT;
				}
				strcpy(shared.input_str, tmp_str);
				free(tmp_str);
				tmp_str = NULL;
			}
			strcat(shared.input_str, event.text.text);

			shared.update_txt = TRUE;
			break;
		default: break;
		}
	}
	SDL_StopTextInput();

	return INPUT_CONTINUE;
}

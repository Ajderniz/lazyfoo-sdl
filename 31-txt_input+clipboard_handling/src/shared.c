#include "../include/shared.h"

#include <stdlib.h> /* calloc, free */
#include <string.h> /* strlen */

#include "../include/log.h"

extern struct Shared shared;

Bool SHARED_init(void)
{
	char tmp_str[] = "Some text";

	LOG_DEBUG(("Initializing shared resources\n"));

	shared.input_str = NULL;
	shared.input_str = calloc(strlen(tmp_str) + 1, sizeof(char));
	if (NULL == shared.input_str) {
		LOG_ERROR(("Could not allocate memory for input string\n"));
		return FALSE;
	}
	strcpy(shared.input_str, tmp_str);

	shared.str_max_len = strlen(shared.input_str) + 1;

	shared.update_txt = TRUE;

	return TRUE;
}

void SHARED_free(void)
{
	LOG_DEBUG(("Freeing shared resources\n"));

	if (shared.input_str != NULL) {
		free(shared.input_str);
		shared.input_str = NULL;
	}
}

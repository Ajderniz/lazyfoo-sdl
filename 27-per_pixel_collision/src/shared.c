#include "../include/dot.h"
#include "../include/shared.h"

extern struct Shared shared;

void SHARED_load(void)
{
	DOT_init(&shared.dot, 0, 0);
	DOT_init(&shared.other_dot, 100, 100);
}

#ifndef TIMER_H
#define TIMER_H

#include "../include/bool.h"

typedef unsigned int Uint32;

typedef struct {
	Uint32 start_ticks;
	Uint32 paused_ticks;
	Bool started;
	Bool paused;
} Timer;

void TIMER_start(Timer*);
void TIMER_stop(Timer*);
void TIMER_pause(Timer*);
void TIMER_unpause(Timer*);
Uint32 TIMER_get_ticks(Timer*);

#endif

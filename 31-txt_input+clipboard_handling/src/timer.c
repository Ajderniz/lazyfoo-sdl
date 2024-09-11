#include "../include/timer.h"
/* Included at header:
 * ===================
 * bool.h
 */
#include <SDL2/SDL_timer.h>

void TIMER_start(Timer *this)
{
	this->started = TRUE;
	this->paused = FALSE;
	this->start_ticks = SDL_GetTicks();
	this->paused_ticks = 0;
}

void TIMER_stop(Timer *this)
{
	this->started = FALSE;
	this->paused = FALSE;
	this->start_ticks = 0;
	this->paused_ticks = 0;
}

void TIMER_pause(Timer *this) {
	if (FALSE == this->started || TRUE == this->paused) {
		return;
	}
	this->paused = TRUE;
	this->paused_ticks = SDL_GetTicks() - this->start_ticks;
	this->start_ticks = 0;
}

void TIMER_unpause(Timer *this) {
	if (FALSE == this->started || FALSE == this->paused) {
		return;
	}
	this->paused = FALSE;
	this->start_ticks = SDL_GetTicks() - this->paused_ticks;
	this->paused_ticks = 0;
}

Uint32 TIMER_get_ticks(Timer *this) {
	if (FALSE == this->started) {
		return 0;
	}
	if (FALSE == this->paused) {
		return SDL_GetTicks() - this->start_ticks;
	}
	return this->paused_ticks;
}

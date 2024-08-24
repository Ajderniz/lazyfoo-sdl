/* Included at header:
 * ===================
 * stdbool.h
 */
#include <SDL2/SDL_timer.h>

#include "../include/timer.h"

void TIMER_start(Timer *this)
{
	this->started = true;
	this->paused = false;
	this->start_ticks = SDL_GetTicks();
	this->paused_ticks = 0;
}

void TIMER_stop(Timer *this)
{
	this->started = false;
	this->paused = false;
	this->start_ticks = 0;
	this->paused_ticks = 0;
}

void TIMER_pause(Timer *this) {
	if (false == this->started || true == this->paused) {
		return;
	}
	this->paused = true;
	this->paused_ticks = SDL_GetTicks() - this->start_ticks;
	this->start_ticks = 0;
}

void TIMER_unpause(Timer *this) {
	if (false == this->started || false == this->paused) {
		return;
	}
	this->paused = false;
	this->start_ticks = SDL_GetTicks() - this->paused_ticks;
	this->paused_ticks = 0;
}

Uint32 TIMER_get_ticks(Timer *this) {
	if (false == this->started) {
		return 0;
	}
	if (false == this->paused) {
		return SDL_GetTicks() - this->start_ticks;
	}
	return this->paused_ticks;
}

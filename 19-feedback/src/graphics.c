/*
 * Included at header:
 * ===================
 * stdbool.h
 */
#include <SDL2/SDL_error.h>
#include <stdlib.h> /* malloc, free */

#include <SDL2/SDL.h>
#include <SDL2/SDL_gamecontroller.h>
#include <SDL2/SDL_haptic.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_joystick.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include "../include/graphics.h"

#define SEVENTY_FIVE (0xFFFF / 4) * 3
#define TIME 100

SDL_Window *g_window = NULL;
SDL_Renderer *g_renderer = NULL;
SDL_Texture *g_texture = NULL;
SDL_GameController *g_game_controller = NULL;
SDL_Joystick *g_joystick = NULL;
SDL_Haptic *g_joy_haptic = NULL;
SDL_Rect g_dst_rect;

bool GRAPHICS_init(void)
{
	if (SDL_Init(SDL_INIT_VIDEO |
			SDL_INIT_JOYSTICK |
			SDL_INIT_HAPTIC |
			SDL_INIT_GAMECONTROLLER) < 0) {
		return false;
	}

	if (SDL_NumJoysticks() < 1) {
		puts("No joysticks connected");
	}
	if (SDL_IsGameController(0)) {
		g_game_controller = SDL_GameControllerOpen(0);
		if (NULL == g_game_controller) {
			printf("Failed to open game controller: %s\n",
					SDL_GetError());
		} else if (!SDL_GameControllerHasRumble(g_game_controller)) {
			puts("Game controller does not have rumble");
		}
	} else {
		puts("Joystick not compatible with game controller interface");
		g_joystick = SDL_JoystickOpen(0);
		if (NULL == g_joystick) {
			printf("Failed to open joystick: %s\n", SDL_GetError());
		} else {
			if (!SDL_JoystickIsHaptic(g_joystick)) {
				puts("Joystick does not support haptics");
			} else {
				g_joy_haptic =
					SDL_HapticOpenFromJoystick(g_joystick);
				if (NULL == g_joy_haptic) {
					printf("Could not get joystic haptics: "
							"%s\n", SDL_GetError());
				} else if (SDL_HapticRumbleInit(g_joy_haptic)
						< 0) {
					printf("Could not initialize haptic "
							"rumble: %s\n",
							SDL_GetError());
				}
			}
		}
	}

	if (0 == IMG_Init(IMG_INIT_PNG)) {
		return false;
	}

	g_window = SDL_CreateWindow("SDL TUTORIAL",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			GRAPHICS_SCR_W, GRAPHICS_SCR_H,
			SDL_WINDOW_SHOWN);
	if (NULL == g_window) {
		return false;
	}

	g_renderer = SDL_CreateRenderer(g_window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (NULL == g_renderer) {
		return false;
	}

	return true;
}

void GRAPHICS_destroy(void)
{
	if (g_texture != NULL) {
		SDL_DestroyTexture(g_texture);
		g_texture = NULL;
	}
	if (g_game_controller != NULL) {
		SDL_GameControllerClose(g_game_controller);
		g_game_controller = NULL;
	}
	if (g_joy_haptic != NULL) {
		SDL_HapticClose(g_joy_haptic);
		g_joy_haptic = NULL;
	}
	if (g_joystick != NULL) {
		SDL_JoystickClose(g_joystick);
		g_joystick = NULL;
	}
	if (g_renderer != NULL) {
		SDL_DestroyRenderer(g_renderer);
		g_renderer = NULL;
	}
	if (g_window != NULL) {
		SDL_DestroyWindow(g_window);
		g_window = NULL;
	}
	IMG_Quit();
	SDL_Quit();
}

bool GRAPHICS_load_media(void)
{
	g_texture = IMG_LoadTexture(g_renderer, GRAPHICS_IMG_DIR"/texture.png");
	if (NULL == g_texture) {
		return false;
	}
	g_dst_rect.x = g_dst_rect.y = 0;
	g_dst_rect.w = GRAPHICS_SCR_W;
	g_dst_rect.h = GRAPHICS_SCR_H;

	return true;
}

void GRAPHICS_update(void)
{
	SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
	SDL_RenderClear(g_renderer);

	SDL_RenderCopy(g_renderer, g_texture, NULL, &g_dst_rect);

	SDL_RenderPresent(g_renderer);
	SDL_Delay(30);
}

void GRAPHICS_vibrate(void) {
	if (g_game_controller != NULL) {
		if (SDL_GameControllerRumble(g_game_controller, 
				 0xFFFF, 0xFFFF, TIME) != 0) {
			printf("Unable to play game controller rumble: %s\n",
					SDL_GetError());
		}
	} else if (g_joy_haptic != NULL) {
		if (SDL_HapticRumblePlay(g_joy_haptic, 1, TIME) != 0) {
			printf("Unable to play haptic rumble: %s\n",
					SDL_GetError());
		}
	}
}

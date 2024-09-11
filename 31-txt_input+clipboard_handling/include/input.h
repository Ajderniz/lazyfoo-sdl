#ifndef INPUT_H
#define INPUT_H

enum INPUT_State {
	INPUT_CONTINUE,
	INPUT_QUIT
};

enum INPUT_State INPUT_handle(void);

#endif

#ifndef MOUSE_H_
#define MOUSE_H_

#include <stdbool.h>
#include "vector2d.h"

typedef struct {
	vector2d_t position;
	bool left_button_pressed;
	bool right_button_pressed;
} mouse_t;

void hover(int x, int y);
void left_click(int state);
void right_click(int state);
void wheel(int state);
void click(int button, int state, int x, int y);
void hold(int x, int y);
void tap(unsigned char key, int x, int y);

#endif // MOUSE_H_

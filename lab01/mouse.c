#include "mouse.h"
#include <GL/glut.h>
#include "global.h"
#include "receive.h"
#include "likely.h"

void hover(int x, int y) {
	mouse.position.x = x;
	mouse.position.y = y;
}

void left_click(int state) {
	switch (state) {
	case GLUT_UP:
		mouse.left_button_pressed = false;
		break;
	case GLUT_DOWN:
		mouse.left_button_pressed = true;
		break;
	default:
		break;
	}
}

void right_click(int state) {
	switch (state) {
	case GLUT_UP:
		mouse.right_button_pressed = false;
		break;
	case GLUT_DOWN:
		mouse.right_button_pressed = true;
		break;
	default:
		break;
	}
}

void wheel(int state) {
	transform_meta.type = UNIFORM_SCALING;
	switch (state) {
	case GLUT_UP:
		transform_meta.uniform_scaling.factor = 1.0 / 0.9;
		break;
	case GLUT_DOWN:
		transform_meta.uniform_scaling.factor = 0.9;
		break;
	default:
		return;
	}
	receive_transform();
	glutPostRedisplay();
}

void hold(int x, int y) {
	int dx = x - mouse.position.x;
	int dy = y - mouse.position.y;

	if ((dx || dy) && (mouse.left_button_pressed || mouse.right_button_pressed)) {
		if (mouse.left_button_pressed) {
			transform_meta.type = ROTATION;
			const vector3d_t axis = create_vector3d(0.2 * dy, -0.2 * dx, 0.0);
			const double angle = 0.01;
			const rotation_t rotation = {axis, angle};
			transform_meta.rotation = rotation;
		}
		else if (mouse.right_button_pressed) {
			transform_meta.type = TRANSLATION;
			const vector3d_t displacement = create_vector3d(0.01 * dx, 0.01 * dy, 0.0);
			const translation_t translation = {displacement};
			transform_meta.translation = translation;
		}
		receive_transform();
		glutPostRedisplay();
	}
	hover(x, y);
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void click(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:
		left_click(state);
		break;
	case GLUT_RIGHT_BUTTON:
		right_click(state);
		break;
	case 3:
		wheel(GLUT_UP);
		break;
	case 4:
		wheel(GLUT_DOWN);
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

static inline __attribute__((always_inline)) unsigned char char_to_key(char c) {
	return c - 'a' + 1;
}

void tap(unsigned char key, int x, int y) {
	if (glutGetModifiers() == GLUT_ACTIVE_CTRL) {
		if (key  == char_to_key('r')) {
			receive_load();
			glutPostRedisplay();
		}
		else if (key == char_to_key('s')) {
			receive_save();
		}
	}
}

#pragma GCC diagnostic pop

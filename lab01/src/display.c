#include "display.h"
#include <GL/glut.h>
#include "receive.h"

void display(void) {
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.7, 0.0, 0.0);
	glPointSize(1);

	glBegin(GL_LINES);

	receive_render();

	glEnd();
	glFlush();
}

void draw_point(const vector2d_t *vector2d) {
	glVertex2d(vector2d->x, vector2d->y);
}


#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "execute.h"
#include "global.h"
#include "display.h"
#include "receive.h"

const char *filename = NULL;
transform_meta_t transform_meta;
screen_t screen = {10, 10, 5, &draw_point};
mouse_t mouse = {{{0, 0}}, false, false};

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fputs("Usage: wm3dv <filename>\n", stderr);
		return EXIT_FAILURE;
	}

	filename = argv[1];

	error_t error = receive_load();
	if (error) {
		perrmsg(error);
		return EXIT_FAILURE;
	}

	puts("Ctrl + R: reset");
	puts("Ctrl + S: save");

	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutCreateWindow("Wireframe model 3D viewer");
	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, screen.width, 0, screen.height);
	
	glutDisplayFunc(display);
	glutPassiveMotionFunc(hover);
	glutMouseFunc(click);
	glutMotionFunc(hold);
	glutKeyboardFunc(tap);

	glutMainLoop();

	return EXIT_SUCCESS;
}

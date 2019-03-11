#ifndef SCREEN_H_
#define SCREEN_H_

#include "vector3d.h"
#include "vector2d.h"

typedef struct {
	double width;
	double height;
	double cam_dist;
	void (*draw_point)(const vector2d_t *);
} screen_t;

vector2d_t project_3d_on_2d(const vector3d_t *vector3d, const screen_t *screen);

#endif // SCREEN_H_

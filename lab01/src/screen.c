#include "screen.h"

vector2d_t project_3d_on_2d(const vector3d_t *vector3d, const screen_t *screen) {
        vector2d_t vector2d = {{
		screen->width / 2 + vector3d->x * screen->cam_dist / (vector3d->z + screen->cam_dist),
		screen->height / 2 - vector3d->y * screen->cam_dist / (vector3d->z + screen->cam_dist)
	}};
	return vector2d;
}

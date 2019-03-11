#include "render.h"

void draw_line(const vector2d_t *a, const vector2d_t *b, const screen_t *screen) {
	screen->draw_point(a);
	screen->draw_point(b);
}

error_t render_model(const model_t *model, const screen_t *screen) {
	for (int i = 0; i != model->n_edges; ++i) {
		vector2d_t a = project_3d_on_2d(get_ij_vertex(model, i, 0), screen);
		vector2d_t b = project_3d_on_2d(get_ij_vertex(model, i, 1), screen);
		draw_line(&a, &b, screen);
	}
	return NONE;
}

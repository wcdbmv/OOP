#ifndef MODEL_H_
#define MODEL_H_

#include "transform.h"
#include "edge.h"
#include "error.h"

typedef struct {
	vector3d_t *vertices;
	edge_t *edges;
	int n_vertices;
	int n_edges;
} model_t;

const vector3d_t *get_ij_vertex(const model_t *model, int i, int j);

model_t create_model(int n_vertices, int n_edges);
void delete_model(model_t *model);

error_t load_model(model_t *model, const char *filename);
error_t dump_model(const model_t *model, const char *filename);
error_t transform_model(model_t *model, const transform_meta_t *transform_meta);

#endif // MODEL_H_

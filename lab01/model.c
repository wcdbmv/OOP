#include "model.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "likely.h"
#include "read_common.h"

model_t create_model(int n_vertices, int n_edges) {
	model_t model = {NULL, NULL, n_vertices, n_edges};
	return model;
}

bool alloc_model(model_t *model) {
	assert(model->n_vertices >= 0 && model->n_edges >= 0);
	if (model->n_vertices > 0) {
		if (!(model->vertices = malloc(model->n_vertices * sizeof *model->vertices)))
			return false;
		if (model->n_edges > 0 && !(model->edges = malloc(model->n_edges * sizeof *model->edges))) {
			free(model->vertices);
			return false;
		}
		return true;
	}
	else if (model->n_edges > 0)
		return false;
	return true;
}

void delete_model(model_t *model) {
	if (model->n_vertices)
		free(model->vertices);
	if (model->n_edges)
		free(model->edges);
	*model = create_model(0, 0);
}

static inline __attribute__((always_inline)) bool read_header(model_t *model, FILE *file) {
	return read_int(&model->n_vertices, file)
	    && read_int(&model->n_edges, file);
}

static inline __attribute__((always_inline)) void write_header(const model_t *model, FILE *file) {
	fprintf(file, "%d %d", model->n_vertices, model->n_edges);
}

error_t read_model(model_t *model, FILE *file) {
	if (unlikely(!read_header(model, file)))
		return INVALID_FILE_FORMAT;
	if (unlikely(!alloc_model(model)))
		return ALLOC_FAIL;
	if (likely(read_vectors3d(model->vertices, model->n_vertices, file)
	        && read_edges(model->edges, model->n_edges, file))) {
		return NONE;
	}
	delete_model(model);
	return INVALID_FILE_FORMAT;
}

void write_model(const model_t *model, FILE *file) {
	write_header(model, file);
	fputs("\n\n", file);
	write_vectors3d(model->vertices, model->n_vertices, file);
	fputs("\n\n", file);
	write_edges(model->edges, model->n_edges, file);
	putc('\n', file);
}

error_t load_model(model_t *model, const char *filename) {
	FILE *file = fopen(filename, "r");
	if (unlikely(!file))
		return CANT_OPEN_FILE;
	model_t tmp = create_model(0, 0);
	error_t error = read_model(&tmp, file);
	fclose(file);
	if (likely(!error)) {
		delete_model(model);
		*model = tmp;
	}
	return error;
}

error_t dump_model(const model_t *model, const char *filename) {
	FILE *file = fopen(filename, "w");
	if (unlikely(!file))
		return CANT_OPEN_FILE;
	write_model(model, file);
	fclose(file);
	return NONE;
}

void transform_model(const transform_t *transform, model_t *model) {
	for (int i = 0; i != model->n_vertices; ++i)
		model->vertices[i] = transform_vector3d(transform, &model->vertices[i]);
}

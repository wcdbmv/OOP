#include "vector.h"

const vector_t origin = {
	0.0, 0.0, 0.0
};

const vector_t unit_x = {
	1.0, 0.0, 0.0
};

const vector_t unit_y = {
	0.0, 1.0, 0.0
};

const vector_t unit_z = {
	0.0, 0.0, 1.0
};

vector_t create_vector(double x, double y, double z) {
	vector_t vector = {x, y, z};
	return vector;
}

vector_t negate_vector(const vector_t *vector) {
	return create_vector(-vector->x, -vector->y, -vector->z);
}

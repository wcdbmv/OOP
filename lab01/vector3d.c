#include "vector3d.h"
#include "read_common.h"

const vector3d_t origin = {
	0.0, 0.0, 0.0
};

const vector3d_t unit_x = {
	1.0, 0.0, 0.0
};

const vector3d_t unit_y = {
	0.0, 1.0, 0.0
};

const vector3d_t unit_z = {
	0.0, 0.0, 1.0
};

vector3d_t create_vector3d(double x, double y, double z) {
	vector3d_t vector3d = {x, y, z};
	return vector3d;
}

vector3d_t negate_vector3d(const vector3d_t *vector3d) {
	return create_vector3d(-vector3d->x, -vector3d->y, -vector3d->z);
}

bool read_vector3d(vector3d_t *vector3d, FILE *file) {
	return read_double(&vector3d->x, file)
	    && read_double(&vector3d->y, file)
	    && read_double(&vector3d->z, file);
}

bool read_vectors3d(vector3d_t *vectors3d, int n, FILE *file) {
	bool ok = true;
	for (int i = 0; i < n && (ok = read_vector3d(vectors3d + i, file)); ++i)
		;
	return ok;
}

void write_vector3d(const vector3d_t *vector3d, FILE *file) {
	fprintf(file, "%lf %lf %lf", vector3d->x, vector3d->y, vector3d->z);
}

void write_vectors3d(const vector3d_t *vectors3d, int n, FILE *file) {
	for (int i = 0; i != n; ++i) {
		write_vector3d(vectors3d + i, file);
		putc('\n', file);
	}
}

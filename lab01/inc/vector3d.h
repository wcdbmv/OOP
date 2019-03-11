#ifndef VECTOR3D_H_
#define VECTOR3D_H_

#include <stdio.h>
#include <stdbool.h>

typedef union {
	struct {
		double x, y, z;
	};
	double m[3];
} vector3d_t;

extern const vector3d_t origin;
extern const vector3d_t unit_x;
extern const vector3d_t unit_y;
extern const vector3d_t unit_z;

vector3d_t create_vector3d(double x, double y, double z);

bool read_vector3d(vector3d_t *vector3d, FILE *file);
bool read_vectors3d(vector3d_t *vectors3d, int n, FILE *file);
void write_vector3d(const vector3d_t *vector3d, FILE *file);
void write_vectors3d(const vector3d_t *vectors_3d, int n, FILE *file);

#endif // VECTOR3D_H_

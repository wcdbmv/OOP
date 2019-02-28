#ifndef VECTOR_H_
#define VECTOR_H_

typedef union {
	double m[3];
	struct {
		double x, y, z;
	};
} vector_t;

extern const vector_t origin;
extern const vector_t unit_x;
extern const vector_t unit_y;
extern const vector_t unit_z;

vector_t create_vector(double x, double y, double z);
vector_t negate_vector(const vector_t *vector);

#endif // VECTOR_H_

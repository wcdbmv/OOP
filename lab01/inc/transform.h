#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "transform_meta.h"

typedef union {
	double m[4][4];
	struct {
		double
			m00, m01, m02, m03,
			m10, m11, m12, m13,
			m20, m21, m22, m23,
			m30, m31, m32, m33;
	};
} transform_t;

extern const transform_t identity;

transform_t create_transform(const transform_meta_t *transform_meta);
vector3d_t transform_vector3d(const transform_t *transform, const vector3d_t *vector3d);
transform_t composition(const transform_t *a, const transform_t *b);

#endif // TRANSFORM_H_

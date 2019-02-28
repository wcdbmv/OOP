#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "vector.h"
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

#endif // TRANSFORM_H_

#ifndef TRANSFORM_META_H_
#define TRANSFORM_META_H_

#include "vector.h"

typedef enum {
	TRANSLATION,
	ROTATION,
	UNIFORM_SCALING
} transform_type_t;

typedef struct {
	vector_t displacement;
} translation_t;

typedef struct {
	vector_t axis;
	double angle;
} rotation_t;

typedef struct uniform_scaling {
	double factor;
} uniform_scaling_t;

typedef struct {
	transform_type_t type;
	union {
		translation_t translation;
		rotation_t rotation;
		uniform_scaling_t uniform_scaling;
	};
} transform_meta_t;

#endif // TRANSFORM_META_H_

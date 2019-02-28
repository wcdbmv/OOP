#include "transform.h"
#include <math.h>
#include <assert.h>

#define SQR(x) (x) * (x)
#define INIT_ZEROS 0.0

const transform_t identity = {
	1.0, 0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0.0, 0.0, 0.0, 1.0
};

transform_t create_translation_transform(const translation_t *translation) {
	transform_t transform = identity;
	transform.m30 = translation->displacement.x;
	transform.m31 = translation->displacement.y;
	transform.m32 = translation->displacement.z;
	return transform;
}

transform_t create_rotation_transform(const rotation_t *rotation) {
	transform_t transform = identity;
	const double sin_a = sin(rotation->angle);
	const double cos_a = cos(rotation->angle);
	const double complement_cos_a = 1.0 - cos_a;
	transform.m00 = cos_a + SQR(rotation->axis.x) * complement_cos_a;
	transform.m11 = cos_a + SQR(rotation->axis.y) * complement_cos_a;
	transform.m22 = cos_a + SQR(rotation->axis.z) * complement_cos_a;
	double tmp_f = rotation->axis.x * rotation->axis.y * complement_cos_a;
	double tmp_s = rotation->axis.z * sin_a;
	transform.m01 = tmp_f + tmp_s;
	transform.m10 = tmp_f - tmp_s;
	tmp_f = rotation->axis.z * rotation->axis.x * complement_cos_a;
	tmp_s = rotation->axis.y * sin_a;
	transform.m02 = tmp_f - tmp_s;
	transform.m20 = tmp_f + tmp_s;
	tmp_f = rotation->axis.y * rotation->axis.z * complement_cos_a;
	tmp_s = rotation->axis.x * sin_a;
	transform.m12 = tmp_f + tmp_s;
	transform.m21 = tmp_f - tmp_s;
	return transform;
}

transform_t create_uniform_scaling_transform(const uniform_scaling_t *uniform_scaling) {
	transform_t transform = identity;
	transform.m00 = transform.m11 = transform.m22 = uniform_scaling->factor;
	return transform;
}

transform_t create_transform(const transform_meta_t *transform_meta) {
	switch (transform_meta->type) {
	case TRANSLATION:
		return create_translation_transform(&transform_meta->translation);
	case ROTATION:
		return create_rotation_transform(&transform_meta->rotation);
	case UNIFORM_SCALING:
		return create_uniform_scaling_transform(&transform_meta->uniform_scaling);
	}
	assert(0);
}

vector_t transform_vector(const transform_t *transform, const vector_t *vector) {
	double a[4] = {vector->x, vector->y, vector->z, 1.0};
	double b[4] = {INIT_ZEROS};
	for (int i = 0; i != 4; ++i)
		for (int k = 0; k != 4; ++k)
			b[i] += transform->m[i][k] * a[k];
	return create_vector(b[0], b[1], b[2]);
}

transform_t composition(const transform_t *a, const transform_t *b) {
	transform_t c = {INIT_ZEROS};
	for (int i = 0; i != 4; ++i)
		for (int j = 0; j != 4; ++j)
			for (int k = 0; k != 4; ++k)
				c.m[i][j] = a->m[i][k] * b->m[k][j];
	return c;
}


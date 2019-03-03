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

transform_t create_translation_transform(const vector3d_t *displacement) {
	transform_t transform = identity;
	transform.m30 = displacement->x;
	transform.m31 = displacement->y;
	transform.m32 = displacement->z;
	return transform;
}

transform_t create_rotation_transform(const vector3d_t *axis, double angle) {
	transform_t transform = identity;
	const double sin_a = sin(angle);
	const double cos_a = cos(angle);
	const double complement_cos_a = 1.0 - cos_a;
	transform.m00 = cos_a + SQR(axis->x) * complement_cos_a;
	transform.m11 = cos_a + SQR(axis->y) * complement_cos_a;
	transform.m22 = cos_a + SQR(axis->z) * complement_cos_a;
	double tmp_f = axis->x * axis->y * complement_cos_a;
	double tmp_s = axis->z * sin_a;
	transform.m01 = tmp_f + tmp_s;
	transform.m10 = tmp_f - tmp_s;
	tmp_f = axis->z * axis->x * complement_cos_a;
	tmp_s = axis->y * sin_a;
	transform.m02 = tmp_f - tmp_s;
	transform.m20 = tmp_f + tmp_s;
	tmp_f = axis->y * axis->z * complement_cos_a;
	tmp_s = axis->x * sin_a;
	transform.m12 = tmp_f + tmp_s;
	transform.m21 = tmp_f - tmp_s;
	return transform;
}

transform_t create_uniform_scaling_transform(double factor) {
	transform_t transform = identity;
	transform.m00 = transform.m11 = transform.m22 = factor;
	return transform;
}

transform_t translate(const translation_t *translation) {
	const vector3d_t *displacement = &translation->displacement;
	return create_translation_transform(displacement);
}

transform_t rotate(const rotation_t *rotate) {
	const vector3d_t *axis = &rotate->axis;
	const double angle = rotate->angle;
	return create_rotation_transform(axis, angle);
}

transform_t uniform_scale(const uniform_scaling_t *uniform_scaling) {
	const double factor = uniform_scaling->factor;
	return create_uniform_scaling_transform(factor);
}

transform_t create_transform(const transform_meta_t *transform_meta) {
	switch (transform_meta->type) {
	case TRANSLATION:
		return translate(&transform_meta->translation);
	case ROTATION:
		return rotate(&transform_meta->rotation);
	case UNIFORM_SCALING:
		return uniform_scale(&transform_meta->uniform_scaling);
	}
	assert(0);
}

vector3d_t transform_vector3d(const transform_t *transform, const vector3d_t *vector3d) {
	double a[4] = {vector3d->x, vector3d->y, vector3d->z, 1.0};
	double b[4] = {INIT_ZEROS};
	for (int i = 0; i != 4; ++i)
		for (int k = 0; k != 4; ++k)
			b[i] += transform->m[i][k] * a[k];
	return create_vector3d(b[0], b[1], b[2]);
}

transform_t composition(const transform_t *a, const transform_t *b) {
	transform_t c = {INIT_ZEROS};
	for (int i = 0; i != 4; ++i)
		for (int j = 0; j != 4; ++j)
			for (int k = 0; k != 4; ++k)
				c.m[i][j] = a->m[i][k] * b->m[k][j];
	return c;
}

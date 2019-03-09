#ifndef VECTOR2D_H_
#define VECTOR2D_H_

typedef union {
	struct {
		double x, y;
	};
	double m[2];
} vector2d_t;

#endif // VECTOR2D_H_

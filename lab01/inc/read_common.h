#ifndef READ_COMMON_H_
#define READ_COMMON_H_

#include <stdio.h>
#include <stdbool.h>

static inline __attribute__((always_inline)) bool read_int(int *pint, FILE *file) {
	return fscanf(file, "%d", pint) == 1;
}

static inline __attribute__((always_inline)) bool read_double(double *pdouble, FILE *file) {
	return fscanf(file, "%lf", pdouble) == 1;
}

#endif // READ_COMMON_H_

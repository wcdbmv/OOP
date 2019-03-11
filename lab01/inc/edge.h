#ifndef EDGE_H_
#define EDGE_H_

#include <stdio.h>
#include <stdbool.h>

typedef union {
	int m[2];
	struct {
		int end1, end2;
	};
} edge_t;

int get_i_end(const edge_t *edge, int i);

bool read_edge(edge_t *edge, FILE *file);
bool read_edges(edge_t *edges, int n, FILE *file);
void write_edge(const edge_t *edge, FILE *file);
void write_edges(const edge_t *edges, int n, FILE *file);

#endif // EDGE_H_

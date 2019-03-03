#include "edge.h"
#include "read_common.h"

bool read_edge(edge_t *edge, FILE *file) {
	return read_int(&edge->end1, file)
	    && read_int(&edge->end2, file);
}

bool read_edges(edge_t *edges, int n, FILE *file) {
	bool ok = true;
	for (int i = 0; i != n && (ok = read_edge(edges + i, file)); ++i)
		;
	return ok;
}

void write_edge(const edge_t *edge, FILE *file) {
	fprintf(file, "%d %d", edge->end1, edge->end2);
}

void write_edges(const edge_t *edges, int n, FILE *file) {
	for (int i = 0; i != n; ++i) {
		write_edge(edges + i, file);
		putc('\n', file);
	}
}

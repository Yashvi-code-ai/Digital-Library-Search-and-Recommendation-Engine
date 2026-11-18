#ifndef ANALYSIS_H
#define ANALYSIS_H
#include <stddef.h>

/* Polynomial-time reduction: Independent Set (G,k) -> Vertex Cover (G, |V|-k). */
int analysis_reduce_independent_set_to_vertex_cover(size_t vertices,
                                                     size_t independent_set_k,
                                                     size_t *vertex_cover_k);

/* Runs reproducible worst-case-style Naive vs KMP string-search benchmarks.
   Writes CSV results to csv_path. Returns 1 on success, 0 on failure. */
int analysis_run_benchmark(const char *csv_path);

#endif

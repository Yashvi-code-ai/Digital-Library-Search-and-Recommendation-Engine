#ifndef FLOW_MATCHING_H
#define FLOW_MATCHING_H
#include <stddef.h>
int flow_ford_fulkerson(const int *capacity,size_t vertices,size_t source,size_t sink,long long *max_flow);
int flow_bipartite_matching(const int *adjacency,size_t left_count,size_t right_count,int *left_match,int *right_match,size_t *matching_size);
#endif

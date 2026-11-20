#ifndef FLOW_MATCHING_H
#define FLOW_MATCHING_H
#include <stddef.h>
int flow_ford_fulkerson(const int *capacity,size_t vertices,size_t source,size_t sink,long long *max_flow);
#endif

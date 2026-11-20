#ifndef GREEDY_H
#define GREEDY_H
#include <stddef.h>
typedef struct { int start,finish; } Activity;
size_t greedy_activity_selection(const Activity *activities,size_t count,size_t *selected);
int greedy_dijkstra(const int *graph,size_t n,size_t source,long long *distances,int *parents);
#endif

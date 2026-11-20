#ifndef GREEDY_H
#define GREEDY_H
#include <stddef.h>
typedef struct { int start, finish; } Activity;
size_t greedy_activity_selection(const Activity *activities, size_t count, size_t *selected);
#endif

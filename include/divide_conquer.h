#ifndef DIVIDE_CONQUER_H
#define DIVIDE_CONQUER_H
#include <stddef.h>
typedef struct { long long sum; size_t start,end; } MaxSubarrayResult;
int maximum_subarray_divide_conquer(const long long *values,size_t count,MaxSubarrayResult *result);
#endif

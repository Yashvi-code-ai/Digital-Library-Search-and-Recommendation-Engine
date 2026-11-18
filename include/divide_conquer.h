#ifndef DIVIDE_CONQUER_H
#define DIVIDE_CONQUER_H

#include <stddef.h>

typedef struct {
    long long sum;
    size_t start;
    size_t end;
} MaxSubarrayResult;

/* Returns 1 on success. The input array must contain at least one element. */
int maximum_subarray_divide_conquer(const long long *values, size_t count,
                                   MaxSubarrayResult *result);

/* Computes base^exponent; returns 0 if the result would overflow long long. */
int fast_power(long long base, unsigned int exponent, long long *result);

/* Matrix is an n-by-n row-major array. Returns celebrity index, or -1. */
int celebrity_divide_conquer(const int *knows, size_t count);

/* Matrices are n-by-n row-major arrays. Values/results must fit in long long. */
int matrix_multiply_classical(const long long *a, const long long *b,
                              long long *result, size_t n);
int matrix_multiply_strassen(const long long *a, const long long *b,
                             long long *result, size_t n);

#endif

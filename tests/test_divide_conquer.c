#include "divide_conquer.h"

#include <assert.h>
#include <stdio.h>

static void test_maximum_subarray(void) {
    const long long values[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    MaxSubarrayResult result;
    assert(maximum_subarray_divide_conquer(values, 9, &result));
    assert(result.sum == 6);
    assert(result.start == 3 && result.end == 6);
    const long long negatives[] = {-8, -3, -6};
    assert(maximum_subarray_divide_conquer(negatives, 3, &result));
    assert(result.sum == -3 && result.start == 1 && result.end == 1);
    assert(!maximum_subarray_divide_conquer(values, 0, &result));
}

static void test_fast_power(void) {
    long long result;
    assert(fast_power(2, 10, &result) && result == 1024);
    assert(fast_power(-2, 3, &result) && result == -8);
    assert(fast_power(7, 0, &result) && result == 1);
    assert(!fast_power(LLONG_MAX, 2, &result));
}

static void test_celebrity(void) {
    const int knows[] = {
        0,1,1,
        0,0,1,
        0,0,0
    };
    const int nobody[] = {
        0,1,0,
        0,0,1,
        1,0,0
    };
    assert(celebrity_divide_conquer(knows, 3) == 2);
    assert(celebrity_divide_conquer(nobody, 3) == -1);
}

static void test_matrices(void) {
    const long long a[] = {1,2,3,4,5,6,7,8,9};
    const long long b[] = {9,8,7,6,5,4,3,2,1};
    long long classic[9], strassen[9];
    assert(matrix_multiply_classical(a,b,classic,3));
    assert(matrix_multiply_strassen(a,b,strassen,3));
    for (int i=0;i<9;i++) assert(classic[i] == strassen[i]);
    assert(classic[0] == 30 && classic[8] == 90);
}

int main(void) {
    test_maximum_subarray();
    test_fast_power();
    test_celebrity();
    test_matrices();
    puts("Phase 3 divide-and-conquer tests passed.");
    return 0;
}

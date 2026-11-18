#include "divide_conquer.h"

#include <limits.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
    long long sum;
    size_t start;
    size_t end;
} Segment;

static Segment max_crossing(const long long *v, size_t left,
                            size_t middle, size_t right) {
    long long sum = 0;
    long long best_left = LLONG_MIN;
    size_t best_start = middle;
    for (size_t i = middle + 1; i-- > left;) {
        sum += v[i];
        if (sum > best_left) {
            best_left = sum;
            best_start = i;
        }
    }

    sum = 0;
    long long best_right = LLONG_MIN;
    size_t best_end = middle + 1;
    for (size_t i = middle + 1; i <= right; ++i) {
        sum += v[i];
        if (sum > best_right) {
            best_right = sum;
            best_end = i;
        }
    }

    Segment answer = {best_left + best_right, best_start, best_end};
    return answer;
}

static Segment max_subarray_recursive(const long long *v, size_t left,
                                      size_t right) {
    if (left == right) {
        Segment one = {v[left], left, right};
        return one;
    }

    size_t middle = left + (right - left) / 2;
    Segment a = max_subarray_recursive(v, left, middle);
    Segment b = max_subarray_recursive(v, middle + 1, right);
    Segment c = max_crossing(v, left, middle, right);

    if (a.sum >= b.sum && a.sum >= c.sum) return a;
    if (b.sum >= a.sum && b.sum >= c.sum) return b;
    return c;
}

int maximum_subarray_divide_conquer(const long long *values, size_t count,
                                   MaxSubarrayResult *result) {
    if (!values || !result || count == 0) return 0;
    Segment answer = max_subarray_recursive(values, 0, count - 1);
    result->sum = answer.sum;
    result->start = answer.start;
    result->end = answer.end;
    return 1;
}

static int multiply_checked(long long a, long long b, long long *out) {
    if (a == 0 || b == 0) {
        *out = 0;
        return 1;
    }
    if (a == -1 && b == LLONG_MIN) return 0;
    if (b == -1 && a == LLONG_MIN) return 0;
    if (a > 0) {
        if (b > 0 && a > LLONG_MAX / b) return 0;
        if (b < 0 && b < LLONG_MIN / a) return 0;
    } else {
        if (b > 0 && a < LLONG_MIN / b) return 0;
        if (b < 0 && a < LLONG_MAX / b) return 0;
    }
    *out = a * b;
    return 1;
}

int fast_power(long long base, unsigned int exponent, long long *result) {
    if (!result) return 0;
    long long answer = 1;
    long long factor = base;
    while (exponent > 0) {
        if (exponent & 1U) {
            if (!multiply_checked(answer, factor, &answer)) return 0;
        }
        exponent >>= 1U;
        if (exponent > 0 && !multiply_checked(factor, factor, &factor)) return 0;
    }
    *result = answer;
    return 1;
}

static int celebrity_candidate(const int *m, size_t n, size_t people) {
    if (people == 1) return 0;
    int candidate = celebrity_candidate(m, n, people - 1);
    size_t last = people - 1;
    if (m[(size_t)candidate * n + last]) return (int)last;
    if (m[last * n + (size_t)candidate]) return candidate;
    return -1;
}

int celebrity_divide_conquer(const int *knows, size_t count) {
    if (!knows || count == 0 || count > (size_t)INT_MAX) return -1;
    int candidate = celebrity_candidate(knows, count, count);
    if (candidate < 0) {
        size_t last = count - 1;
        for (size_t i = 0; i < last; ++i) {
            if (knows[i * count + last] == 0 || knows[last * count + i] != 0)
                return -1;
        }
        return (int)last;
    }

    for (size_t i = 0; i < count; ++i) {
        if (i == (size_t)candidate) continue;
        if (knows[(size_t)candidate * count + i] != 0 ||
            knows[i * count + (size_t)candidate] == 0) return -1;
    }
    return candidate;
}

int matrix_multiply_classical(const long long *a, const long long *b,
                              long long *result, size_t n) {
    if (!a || !b || !result || n == 0 || n > SIZE_MAX / n ||
        n * n > SIZE_MAX / sizeof(long long)) return 0;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            long long sum = 0;
            for (size_t k = 0; k < n; ++k)
                sum += a[i * n + k] * b[k * n + j];
            result[i * n + j] = sum;
        }
    }
    return 1;
}

static void add_matrix(const long long *a, const long long *b,
                       long long *out, size_t count, int subtract) {
    for (size_t i = 0; i < count; ++i)
        out[i] = subtract ? a[i] - b[i] : a[i] + b[i];
}

static void classical_power_two(const long long *a, const long long *b,
                                long long *c, size_t n) {
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < n; ++j) {
            long long sum = 0;
            for (size_t k = 0; k < n; ++k)
                sum += a[i * n + k] * b[k * n + j];
            c[i * n + j] = sum;
        }
}

static int strassen_recursive(const long long *a, const long long *b,
                              long long *c, size_t n) {
    if (n <= 2) {
        classical_power_two(a, b, c, n);
        return 1;
    }

    size_t h = n / 2;
    if (h > SIZE_MAX / h || h * h > SIZE_MAX / sizeof(long long)) return 0;
    size_t cells = h * h;
    if (cells > SIZE_MAX / (17 * sizeof(long long))) return 0;
    long long *mem = (long long *)malloc(17 * cells * sizeof(long long));
    if (!mem) return 0;

    long long *a11=mem, *a12=a11+cells, *a21=a12+cells, *a22=a21+cells;
    long long *b11=a22+cells, *b12=b11+cells, *b21=b12+cells, *b22=b21+cells;
    long long *m1=b22+cells, *m2=m1+cells, *m3=m2+cells, *m4=m3+cells;
    long long *m5=m4+cells, *m6=m5+cells, *m7=m6+cells;
    long long *t1=m7+cells, *t2=t1+cells;

    for (size_t i=0;i<h;i++) for (size_t j=0;j<h;j++) {
        a11[i*h+j]=a[i*n+j]; a12[i*h+j]=a[i*n+j+h];
        a21[i*h+j]=a[(i+h)*n+j]; a22[i*h+j]=a[(i+h)*n+j+h];
        b11[i*h+j]=b[i*n+j]; b12[i*h+j]=b[i*n+j+h];
        b21[i*h+j]=b[(i+h)*n+j]; b22[i*h+j]=b[(i+h)*n+j+h];
    }

    add_matrix(a11,a22,t1,cells,0); add_matrix(b11,b22,t2,cells,0);
    int ok = strassen_recursive(t1,t2,m1,h);
    add_matrix(a21,a22,t1,cells,0);
    if (ok) ok = strassen_recursive(t1,b11,m2,h);
    add_matrix(b12,b22,t2,cells,1);
    if (ok) ok = strassen_recursive(a11,t2,m3,h);
    add_matrix(b21,b11,t2,cells,1);
    if (ok) ok = strassen_recursive(a22,t2,m4,h);
    add_matrix(a11,a12,t1,cells,0);
    if (ok) ok = strassen_recursive(t1,b22,m5,h);
    add_matrix(a21,a11,t1,cells,1); add_matrix(b11,b12,t2,cells,0);
    if (ok) ok = strassen_recursive(t1,t2,m6,h);
    add_matrix(a12,a22,t1,cells,1); add_matrix(b21,b22,t2,cells,0);
    if (ok) ok = strassen_recursive(t1,t2,m7,h);

    if (ok) {
        for (size_t i=0;i<h;i++) for (size_t j=0;j<h;j++) {
            size_t p=i*h+j;
            long long c11=m1[p]+m4[p]-m5[p]+m7[p];
            long long c12=m3[p]+m5[p];
            long long c21=m2[p]+m4[p];
            long long c22=m1[p]-m2[p]+m3[p]+m6[p];
            c[i*n+j]=c11; c[i*n+j+h]=c12;
            c[(i+h)*n+j]=c21; c[(i+h)*n+j+h]=c22;
        }
    }
    free(mem);
    return ok;
}

int matrix_multiply_strassen(const long long *a, const long long *b,
                             long long *result, size_t n) {
    if (!a || !b || !result || n == 0 || n > SIZE_MAX / n ||
        n * n > SIZE_MAX / sizeof(long long)) return 0;
    size_t padded = 1;
    while (padded < n) {
        if (padded > SIZE_MAX / 2) return 0;
        padded *= 2;
    }
    if (padded > SIZE_MAX / padded ||
        padded * padded > SIZE_MAX / sizeof(long long)) return 0;

    size_t cells = padded * padded;
    long long *pa = (long long *)calloc(cells, sizeof(long long));
    long long *pb = (long long *)calloc(cells, sizeof(long long));
    long long *pc = (long long *)calloc(cells, sizeof(long long));
    if (!pa || !pb || !pc) {
        free(pa); free(pb); free(pc);
        return 0;
    }
    for (size_t i=0;i<n;i++) for (size_t j=0;j<n;j++) {
        pa[i*padded+j]=a[i*n+j];
        pb[i*padded+j]=b[i*n+j];
    }
    int ok = strassen_recursive(pa,pb,pc,padded);
    if (ok)
        for (size_t i=0;i<n;i++) for (size_t j=0;j<n;j++)
            result[i*n+j]=pc[i*padded+j];
    free(pa); free(pb); free(pc);
    return ok;
}

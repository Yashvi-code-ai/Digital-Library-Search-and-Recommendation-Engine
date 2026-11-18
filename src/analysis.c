#include "analysis.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int analysis_reduce_independent_set_to_vertex_cover(size_t vertices,
                                                     size_t independent_set_k,
                                                     size_t *vertex_cover_k) {
    if (!vertex_cover_k || independent_set_k > vertices) return 0;
    *vertex_cover_k = vertices - independent_set_k;
    return 1;
}

static size_t naive_count(const char *text, const char *pattern,
                          uint64_t *comparisons) {
    size_t n = strlen(text), m = strlen(pattern);
    *comparisons = 0;
    if (m == 0) return 0;
    if (m > n) return SIZE_MAX;
    for (size_t i = 0; i <= n - m; ++i) {
        size_t j = 0;
        while (j < m) {
            ++*comparisons;
            if (text[i + j] != pattern[j]) break;
            ++j;
        }
        if (j == m) return i;
    }
    return SIZE_MAX;
}

static size_t kmp_count(const char *text, const char *pattern,
                        uint64_t *comparisons) {
    size_t n = strlen(text), m = strlen(pattern);
    *comparisons = 0;
    if (m == 0) return 0;
    if (m > n) return SIZE_MAX;
    size_t *lps = calloc(m, sizeof(*lps));
    if (!lps) return SIZE_MAX;

    for (size_t i = 1, len = 0; i < m;) {
        ++*comparisons;
        if (pattern[i] == pattern[len]) lps[i++] = ++len;
        else if (len) len = lps[len - 1];
        else lps[i++] = 0;
    }

    size_t i = 0, j = 0, answer = SIZE_MAX;
    while (i < n) {
        ++*comparisons;
        if (text[i] == pattern[j]) { ++i; ++j; }
        if (j == m) { answer = i - j; break; }
        if (i < n) {
            ++*comparisons;
            if (text[i] != pattern[j]) {
                if (j) j = lps[j - 1];
                else ++i;
            }
        }
    }
    free(lps);
    return answer;
}

static double elapsed_ms(clock_t start, clock_t finish) {
    return 1000.0 * (double)(finish - start) / (double)CLOCKS_PER_SEC;
}

int analysis_run_benchmark(const char *csv_path) {
    static const size_t sizes[] = {500, 1000, 2000, 4000};
    if (!csv_path || !csv_path[0]) return 0;
    FILE *file = fopen(csv_path, "w");
    if (!file) return 0;

    fprintf(file, "algorithm,text_length,pattern_length,character_comparisons,time_ms,match_index\n");
    puts("\nBenchmark: Naive vs KMP string matching");
    puts("Synthetic worst-case-style input: repeated 'a' text; pattern ends in 'b'.");
    puts("Size       Algorithm       Comparisons       Time (ms)      Result");
    for (size_t s = 0; s < sizeof(sizes) / sizeof(sizes[0]); ++s) {
        size_t n = sizes[s], m = n / 4;
        char *text = malloc(n + 1), *pattern = malloc(m + 1);
        if (!text || !pattern) {
            free(text); free(pattern); fclose(file); return 0;
        }
        memset(text, 'a', n); text[n] = '\0';
        memset(pattern, 'a', m); pattern[m - 1] = 'b'; pattern[m] = '\0';

        uint64_t comparisons = 0;
        clock_t begin = clock();
        size_t match = naive_count(text, pattern, &comparisons);
        clock_t finish = clock();
        double ms = elapsed_ms(begin, finish);
        fprintf(file, "Naive,%zu,%zu,%llu,%.6f,%s\n", n, m,
                (unsigned long long)comparisons, ms, match == SIZE_MAX ? "not_found" : "found");
        printf("%-10zu %-15s %-17llu %-14.6f %s\n", n, "Naive",
               (unsigned long long)comparisons, ms,
               match == SIZE_MAX ? "not found" : "found");

        begin = clock();
        match = kmp_count(text, pattern, &comparisons);
        finish = clock();
        ms = elapsed_ms(begin, finish);
        fprintf(file, "KMP,%zu,%zu,%llu,%.6f,%s\n", n, m,
                (unsigned long long)comparisons, ms, match == SIZE_MAX ? "not_found" : "found");
        printf("%-10zu %-15s %-17llu %-14.6f %s\n", n, "KMP",
               (unsigned long long)comparisons, ms,
               match == SIZE_MAX ? "not found" : "found");
        free(text);
        free(pattern);
    }
    if (fclose(file) != 0) return 0;
    printf("\nCSV benchmark report saved to: %s\n", csv_path);
    return 1;
}

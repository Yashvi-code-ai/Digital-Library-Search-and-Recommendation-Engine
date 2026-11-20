#include "string_number_theory.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

size_t string_match_kmp(const char *text, const char *pattern) {
    if (!text || !pattern) return SIZE_MAX;
    size_t text_length = strlen(text);
    size_t pattern_length = strlen(pattern);
    if (!pattern_length) return 0;
    if (pattern_length > text_length) return SIZE_MAX;

    size_t *lps = calloc(pattern_length, sizeof(*lps));
    if (!lps) return SIZE_MAX;

    for (size_t i = 1, length = 0; i < pattern_length;) {
        if (pattern[i] == pattern[length]) lps[i++] = ++length;
        else if (length) length = lps[length - 1];
        else lps[i++] = 0;
    }

    size_t i = 0, j = 0, found = SIZE_MAX;
    while (i < text_length) {
        if (text[i] == pattern[j]) {
            i++;
            j++;
            if (j == pattern_length) {
                found = i - j;
                break;
            }
        } else if (j) j = lps[j - 1];
        else i++;
    }
    free(lps);
    return found;
}

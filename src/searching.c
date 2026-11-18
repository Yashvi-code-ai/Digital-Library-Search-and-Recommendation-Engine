#include "algorithms.h"
#include <ctype.h>
#include <stddef.h>

int compare_title_text(const char *left, const char *right) {
    while (*left && *right) {
        int a = tolower((unsigned char)*left);
        int b = tolower((unsigned char)*right);
        if (a != b) return a < b ? -1 : 1;
        left++;
        right++;
    }
    if (*left) return 1;
    if (*right) return -1;
    return 0;
}

int linear_search_title(const Book *books, size_t count, const char *title) {
    if (!books || !title) return -1;
    for (size_t i = 0; i < count; i++) {
        if (compare_title_text(books[i].title, title) == 0)
            return (int)i;
    }
    return -1;
}

int binary_search_title_iterative(const Book *books, size_t count, const char *title) {
    if (!books || !title) return -1;
    size_t low = 0;
    size_t high = count;
    while (low < high) {
        size_t middle = low + (high - low) / 2;
        int comparison = compare_title_text(books[middle].title, title);
        if (comparison == 0) return (int)middle;
        if (comparison < 0) low = middle + 1;
        else high = middle;
    }
    return -1;
}

static int binary_search_recursive_range(const Book *books, const char *title,
                                         ptrdiff_t low, ptrdiff_t high) {
    if (low > high) return -1;
    ptrdiff_t middle = low + (high - low) / 2;
    int comparison = compare_title_text(books[middle].title, title);
    if (comparison == 0) return (int)middle;
    if (comparison < 0)
        return binary_search_recursive_range(books, title, middle + 1, high);
    return binary_search_recursive_range(books, title, low, middle - 1);
}

int binary_search_title_recursive(const Book *books, size_t count, const char *title) {
    if (!books || !title || count == 0) return -1;
    return binary_search_recursive_range(books, title, 0, (ptrdiff_t)count - 1);
}

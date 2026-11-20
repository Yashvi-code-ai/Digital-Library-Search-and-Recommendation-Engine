#include "algorithms.h"
#include <ctype.h>

int compare_title_text(const char *a, const char *b) {
    while (*a && *b) {
        int x = tolower((unsigned char)*a);
        int y = tolower((unsigned char)*b);
        if (x != y) return x < y ? -1 : 1;
        a++;
        b++;
    }
    return (*a != 0) - (*b != 0);
}

int linear_search_title(const Book *books, size_t count, const char *title) {
    if (!books || !title) return -1;
    for (size_t i = 0; i < count; i++) {
        if (compare_title_text(books[i].title, title) == 0) return (int)i;
    }
    return -1;
}

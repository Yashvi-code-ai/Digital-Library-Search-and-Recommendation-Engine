#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "book.h"
#include <stddef.h>

/* Exact, case-insensitive title searches. Binary search requires title-sorted data. */
int linear_search_title(const Book *books, size_t count, const char *title);
int binary_search_title_iterative(const Book *books, size_t count, const char *title);
int binary_search_title_recursive(const Book *books, size_t count, const char *title);

/* Sorts Book records in-place by title, case-insensitively. */
int merge_sort_books(Book *books, size_t count);
void quick_sort_books(Book *books, size_t count);
int books_sorted_by_title(const Book *books, size_t count);
int compare_title_text(const char *left, const char *right);

#endif

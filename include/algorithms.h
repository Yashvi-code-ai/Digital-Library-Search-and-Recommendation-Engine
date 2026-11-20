#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include "book.h"
#include <stddef.h>
int compare_title_text(const char *a,const char *b);
int linear_search_title(const Book *books,size_t count,const char *title);
int binary_search_title(const Book *books,size_t count,const char *title);
int books_sorted_by_title(const Book *books,size_t count);
int merge_sort_books(Book *books,size_t count);
#endif

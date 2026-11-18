#include "algorithms.h"
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

static void swap_books(Book *a, Book *b) {
    Book temporary = *a;
    *a = *b;
    *b = temporary;
}

int books_sorted_by_title(const Book *books, size_t count) {
    if (!books) return count == 0;
    for (size_t i = 1; i < count; i++) {
        if (compare_title_text(books[i - 1].title, books[i].title) > 0)
            return 0;
    }
    return 1;
}

static void merge_ranges(Book *books, Book *temporary,
                         size_t left, size_t middle, size_t right) {
    size_t i = left;
    size_t j = middle;
    size_t out = left;

    while (i < middle && j < right) {
        if (compare_title_text(books[i].title, books[j].title) <= 0)
            temporary[out++] = books[i++];
        else
            temporary[out++] = books[j++];
    }
    while (i < middle) temporary[out++] = books[i++];
    while (j < right) temporary[out++] = books[j++];

    for (size_t k = left; k < right; k++) books[k] = temporary[k];
}

static void merge_sort_range(Book *books, Book *temporary,
                             size_t left, size_t right) {
    if (right - left < 2) return;
    size_t middle = left + (right - left) / 2;
    merge_sort_range(books, temporary, left, middle);
    merge_sort_range(books, temporary, middle, right);
    merge_ranges(books, temporary, left, middle, right);
}

int merge_sort_books(Book *books, size_t count) {
    if (!books && count > 0) return 0;
    if (count < 2) return 1;
    if (count > (size_t)-1 / sizeof *books) return 0;

    Book *temporary = malloc(count * sizeof *temporary);
    if (!temporary) return 0;
    merge_sort_range(books, temporary, 0, count);
    free(temporary);
    return 1;
}

static size_t partition_books(Book *books, size_t low, size_t high) {
    char pivot[TITLE_LEN];
    size_t left = low;
    size_t right = high;
    size_t middle = low + (high - low) / 2;
    memcpy(pivot, books[middle].title, sizeof pivot);
    pivot[sizeof pivot - 1] = '\0';

    while (left <= right) {
        while (compare_title_text(books[left].title, pivot) < 0) left++;
        while (compare_title_text(books[right].title, pivot) > 0) {
            if (right == 0) break;
            right--;
        }
        if (left <= right) {
            swap_books(&books[left], &books[right]);
            left++;
            if (right == 0) break;
            right--;
        }
    }
    return left;
}

static void quick_sort_range(Book *books, size_t low, size_t high) {
    if (low >= high) return;
    size_t split = partition_books(books, low, high);
    if (split > low) quick_sort_range(books, low, split - 1);
    if (split <= high) quick_sort_range(books, split, high);
}

void quick_sort_books(Book *books, size_t count) {
    if (!books || count < 2) return;
    quick_sort_range(books, 0, count - 1);
}

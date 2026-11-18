#include "algorithms.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

static void set_title(Book *book, int id, const char *title) {
    memset(book, 0, sizeof *book);
    book->id = id;
    snprintf(book->title, sizeof book->title, "%s", title);
}

static void check_sorted(const Book *books, size_t count) {
    assert(books_sorted_by_title(books, count));
    for (size_t i = 1; i < count; i++)
        assert(compare_title_text(books[i - 1].title, books[i].title) <= 0);
}

int main(void) {
    Book merge_data[7], quick_data[7];
    const char *titles[] = {
        "The C Programming Language", "Algorithms", "Clean Code",
        "data structures", "Binary Search", "Operating Systems", "Compiler Design"
    };

    for (size_t i = 0; i < 7; i++) {
        set_title(&merge_data[i], (int)i + 1, titles[i]);
        quick_data[i] = merge_data[i];
    }

    assert(linear_search_title(merge_data, 7, "clean code") == 2);
    assert(linear_search_title(merge_data, 7, "Missing Book") == -1);
    assert(linear_search_title(NULL, 0, "Anything") == -1);

    assert(merge_sort_books(merge_data, 7));
    check_sorted(merge_data, 7);
    assert(binary_search_title_iterative(merge_data, 7, "CLEAN CODE") >= 0);
    assert(binary_search_title_recursive(merge_data, 7, "algorithms") >= 0);
    assert(binary_search_title_iterative(merge_data, 7, "Not Present") == -1);
    assert(binary_search_title_recursive(merge_data, 7, "Not Present") == -1);

    quick_sort_books(quick_data, 7);
    check_sorted(quick_data, 7);
    assert(binary_search_title_iterative(quick_data, 7, "Operating Systems") >= 0);

    assert(merge_sort_books(NULL, 0));
    quick_sort_books(NULL, 0);
    puts("All Phase 2 searching and sorting tests passed.");
    return 0;
}

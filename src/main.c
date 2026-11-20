#include "book.h"
#include "library.h"
#include "algorithms.h"
#include "greedy.h"
#include "dp.h"
#include "backtracking.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define DATA_FILE "data/books.csv"

static int read_signed_int(const char *prompt, int *value) {
    char line[64], *end;
    long number;
    read_line(prompt, line, sizeof line);
    if (!line[0]) return 0;
    number = strtol(line, &end, 10);
    if (*end || number < INT_MIN || number > INT_MAX) return 0;
    *value = (int)number;
    return 1;
}

static void input_book(Book *book) {
    read_line("Title: ", book->title, TITLE_LEN);
    read_line("Author: ", book->author, AUTHOR_LEN);
    read_line("Category: ", book->category, CATEGORY_LEN);
    read_line("Keywords: ", book->keywords, KEYWORDS_LEN);
    if (!read_int("Citations: ", &book->citations)) book->citations = 0;
    if (!read_int("Popularity: ", &book->popularity)) book->popularity = 0;
}

static void add_book(Library *library) {
    Book book = {0};
    book.id = library_next_id(library);
    input_book(&book);
    if (!book.title[0] || !book.author[0]) {
        puts("Title and author are required.");
        return;
    }
    puts(library_add(library, &book) ? "Book added." : "Could not add book.");
}

static void update_book(Library *library) {
    int id;
    if (!read_int("Book ID: ", &id) || library_find_id(library, id) < 0) {
        puts("Book not found.");
        return;
    }
    Book replacement = {0};
    input_book(&replacement);
    if (!replacement.title[0] || !replacement.author[0]) {
        puts("Title and author are required.");
        return;
    }
    puts(library_update(library, id, &replacement) ? "Book updated." : "Update failed.");
}

static void delete_book(Library *library) {
    int id;
    if (!read_int("Book ID: ", &id)) {
        puts("Invalid ID.");
        return;
    }
    puts(library_remove(library, id) ? "Book deleted." : "Book not found.");
}

static void search_books(Library *library) {
    int choice;
    char title[TITLE_LEN];
    puts("\n1. Linear Search  0. Back");
    if (!read_int("Choice: ", &choice)) return;
    if (choice != 1) return;
    read_line("Exact title: ", title, sizeof title);
    int index = linear_search_title(library->items, library->count, title);
    if (index < 0) puts("Book not found.");
    else print_book(&library->items[index]);
}

static void greedy_menu(void) {
    int count;
    if (!read_int("Number of activities (1-50): ", &count) || count < 1 || count > 50) return;
    Activity activities[50];
    size_t selected[50];
    for (int i = 0; i < count; i++) {
        if (!read_int("Start time: ", &activities[i].start) ||
            !read_int("Finish time: ", &activities[i].finish)) return;
    }
    size_t total = greedy_activity_selection(activities, (size_t)count, selected);
    printf("Selected %zu activities:", total);
    for (size_t i = 0; i < total; i++) printf(" %zu", selected[i] + 1);
    putchar('\\n');
}

static void knapsack_menu(void) {
    int count, capacity;
    if (!read_int("Number of items (1-50): ", &count) || count < 1 || count > 50 ||
        !read_int("Bag capacity: ", &capacity) || capacity > 100000) return;
    int weights[50], values[50];
    for (int i = 0; i < count; i++) {
        if (!read_int("Weight: ", &weights[i]) || !read_int("Value: ", &values[i])) return;
    }
    long long best;
    if (dp_knapsack(weights, values, (size_t)count, capacity, &best))
        printf("Maximum value: %lld\n", best);
    else puts("Invalid item details.");
}

static void backtracking_menu(void) {
    int n;
    if (!read_int("Board size (1-14): ", &n)) return;
    long long solutions = bt_nqueens_count(n);
    if (solutions < 0) puts("Choose a board size from 1 to 14.");
    else printf("Number of solutions: %lld\\n", solutions);
}

static void algorithms_menu(Library *library) {
    int choice;
    for (;;) {
        puts("\\n===== DAA ALGORITHMS =====");
        puts("1 Linear Search  2 Merge Sort");
        puts("3 Activity Selection  4 0/1 Knapsack  5 N-Queens");
        puts("0 Back to Library Menu");
        if (!read_int("Choice: ", &choice)) continue;
        switch (choice) {
            case 0: return;
            case 1: search_books(library); break;
            case 2: puts(merge_sort_books(library->items, library->count)
                         ? "Books sorted by title." : "Sort failed."); break;
            case 3: greedy_menu(); break;
            case 4: knapsack_menu(); break;
            case 5: backtracking_menu(); break;
            default: puts("Invalid option.");
        }
    }
}


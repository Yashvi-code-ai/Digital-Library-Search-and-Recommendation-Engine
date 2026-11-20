#include "book.h"
#include "library.h"
#include "algorithms.h"
#include "divide_conquer.h"
#include "greedy.h"
#include "dp.h"
#include "backtracking.h"
#include "string_number_theory.h"
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
    puts("\n1. Linear Search  2. Binary Search  0. Back");
    if (!read_int("Choice: ", &choice)) return;
    if (choice != 1 && choice != 2) return;
    read_line("Exact title: ", title, sizeof title);
    if (choice == 2 && !books_sorted_by_title(library->items, library->count)) {
        puts("Sorting the library first so Binary Search can work.");
        if (!merge_sort_books(library->items, library->count)) return;
    }
    int index = choice == 1
        ? linear_search_title(library->items, library->count, title)
        : binary_search_title(library->items, library->count, title);
    if (index < 0) puts("Book not found.");
    else print_book(&library->items[index]);
}

static void maximum_subarray_menu(void) {
    int count;
    if (!read_int("Number of values (1-100): ", &count) || count < 1 || count > 100) return;
    long long values[100];
    for (int i = 0; i < count; i++) {
        int value;
        if (!read_signed_int("Value (negative numbers allowed): ", &value)) return;
        values[i] = value;
    }
    MaxSubarrayResult result;
    if (maximum_subarray_divide_conquer(values, (size_t)count, &result))
        printf("Maximum sum: %lld (positions %zu to %zu)\n",
               result.sum, result.start + 1, result.end + 1);
}

static void greedy_menu(void) {
    int choice;
    if (!read_int("1. Activity Selection  2. Dijkstra  0. Back: ", &choice)) return;
    if (choice == 1) {
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
        putchar('\n');
    } else if (choice == 2) {
        int count, source;
        if (!read_int("Number of vertices (1-20): ", &count) || count < 1 || count > 20) return;
        int graph[400], parent[20];
        long long distance[20];
        puts("Enter the adjacency matrix (0 means no edge).");
        for (int i = 0; i < count * count; i++)
            if (!read_int("Weight: ", &graph[i])) return;
        if (!read_int("Source vertex (0-based): ", &source) || source >= count) return;
        if (!greedy_dijkstra(graph, (size_t)count, (size_t)source, distance, parent)) {
            puts("Invalid graph.");
            return;
        }
        for (int i = 0; i < count; i++) {
            if (distance[i] == LLONG_MAX) printf("%d: unreachable\n", i);
            else printf("%d: %lld\n", i, distance[i]);
        }
    }
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
    int choice;
    if (!read_int("1. N-Queens  2. Subset Sum  0. Back: ", &choice)) return;
    if (choice == 1) {
        int n;
        if (!read_int("Board size (1-14): ", &n)) return;
        long long solutions = bt_nqueens_count(n);
        if (solutions < 0) puts("Choose a board size from 1 to 14.");
        else printf("Number of solutions: %lld\n", solutions);
    } else if (choice == 2) {
        int count, target;
        if (!read_int("Number of values (1-30): ", &count) || count < 1 || count > 30 ||
            !read_int("Target sum: ", &target)) return;
        int values[30];
        for (int i = 0; i < count; i++)
            if (!read_int("Value (zero or positive): ", &values[i])) return;
        puts(bt_subset_sum(values, (size_t)count, target)
             ? "A subset with that sum exists." : "No matching subset exists.");
    }
}

static void kmp_menu(void) {
    char text[500], pattern[100];
    read_line("Text: ", text, sizeof text);
    read_line("Pattern to find: ", pattern, sizeof pattern);
    size_t position = string_match_kmp(text, pattern);
    if (position == (size_t)-1) puts("Pattern not found.");
    else printf("Pattern found at position %zu.\n", position);
}

static void algorithms_menu(Library *library) {
    int choice;
    for (;;) {
        puts("\n===== DAA ALGORITHMS =====");
        puts("1 Search (Linear/Binary)  2 Merge Sort  3 Maximum Subarray");
        puts("4 Greedy Algorithms  5 0/1 Knapsack  6 Backtracking  7 KMP");
        puts("0 Back to Library Menu");
        if (!read_int("Choice: ", &choice)) continue;
        switch (choice) {
            case 0: return;
            case 1: search_books(library); break;
            case 2: puts(merge_sort_books(library->items, library->count)
                         ? "Books sorted by title." : "Sort failed."); break;
            case 3: maximum_subarray_menu(); break;
            case 4: greedy_menu(); break;
            case 5: knapsack_menu(); break;
            case 6: backtracking_menu(); break;
            case 7: kmp_menu(); break;
            default: puts("Invalid option.");
        }
    }
}

int main(void) {
    Library library;
    library_init(&library);
    if (!library_load_csv(&library, DATA_FILE)) puts("Starting with an empty library.");

    int choice;
    for (;;) {
        puts("\n===== DIGITAL LIBRARY =====");
        puts("1 Add Book  2 List Books  3 Search Titles");
        puts("4 Update Book  5 Delete Book  6 Sort Books");
        puts("7 DAA Algorithms  8 Save Library  0 Save and Exit");
        if (!read_int("Choice: ", &choice)) {
            puts("Please enter a valid number.");
            continue;
        }
        switch (choice) {
            case 0:
                library_save_csv(&library, DATA_FILE);
                library_free(&library);
                puts("Goodbye.");
                return 0;
            case 1: add_book(&library); break;
            case 2: library_list(&library); break;
            case 3: {
                char query[TITLE_LEN];
                read_line("Enter title text: ", query, sizeof query);
                library_search_title(&library, query);
                break;
            }
            case 4: update_book(&library); break;
            case 5: delete_book(&library); break;
            case 6:
                puts(merge_sort_books(library.items, library.count)
                     ? "Books sorted by title." : "Sort failed.");
                break;
            case 7: algorithms_menu(&library); break;
            case 8:
                puts(library_save_csv(&library, DATA_FILE) ? "Library saved." : "Save failed.");
                break;
            default: puts("Invalid option.");
        }
    }
}

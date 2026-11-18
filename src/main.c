#include "book.h"
#include "library.h"
#include "algorithms.h"
#include "divide_conquer.h"
#include <stdio.h>
#include <stdlib.h>

#define DATA_FILE "data/books.csv"

static void input_book(Book *book) {
    read_line("Title: ", book->title, sizeof book->title);
    read_line("Author: ", book->author, sizeof book->author);
    read_line("Category: ", book->category, sizeof book->category);
    read_line("Keywords (separated by spaces): ", book->keywords, sizeof book->keywords);
    if (!read_int("Citation count (0 or more): ", &book->citations)) book->citations = 0;
    if (!read_int("Popularity score (0 or more): ", &book->popularity)) book->popularity = 0;
}

static void add_book(Library *library) {
    Book book = {0};
    book.id = library_next_id(library);
    puts("\nEnter book details:");
    input_book(&book);
    if (!book.title[0] || !book.author[0]) {
        puts("Title and author are required.");
        return;
    }
    if (library_add(library, &book)) puts("Book added successfully.");
    else puts("Could not add book (duplicate ID or insufficient memory).");
}

static void edit_book(Library *library) {
    int id;
    if (!read_int("Enter book ID to update: ", &id)) { puts("Invalid ID."); return; }
    int index = library_find_id(library, id);
    if (index < 0) { puts("Book not found."); return; }
    Book replacement = {0};
    puts("Enter replacement details:");
    input_book(&replacement);
    if (!replacement.title[0] || !replacement.author[0]) {
        puts("Title and author are required.");
        return;
    }
    if (library_update(library, id, &replacement)) puts("Book updated.");
}

static void delete_book(Library *library) {
    int id;
    if (!read_int("Enter book ID to delete: ", &id)) { puts("Invalid ID."); return; }
    puts(library_remove(library, id) ? "Book deleted." : "Book not found.");
}

static void show_search_result(const Library *library, int index) {
    if (index >= 0) print_book(&library->items[index]);
    else puts("No exact title match found.");
}

static void ensure_title_order(Library *library) {
    if (books_sorted_by_title(library->items, library->count)) return;
    puts("Binary search needs titles sorted alphabetically.");
    if (merge_sort_books(library->items, library->count))
        puts("The library has been sorted using Merge Sort.");
    else
        puts("Could not allocate memory for sorting.");
}

static void search_sort_menu(Library *library) {
    int choice;
    for (;;) {
        puts("\n========== PHASE 2: SEARCHING AND SORTING ==========");
        puts("1. Linear Search (exact title)");
        puts("2. Iterative Binary Search");
        puts("3. Recursive Binary Search");
        puts("4. Sort books using Merge Sort");
        puts("5. Sort books using Quick Sort");
        puts("6. Display current book order");
        puts("0. Return to main menu");
        if (!read_int("Choose an option: ", &choice)) {
            puts("Please enter a valid number.");
            continue;
        }
        if (choice == 0) return;
        if (choice >= 1 && choice <= 3) {
            char title[TITLE_LEN];
            int index;
            read_line("Enter the complete book title: ", title, sizeof title);
            if (!title[0]) { puts("Title cannot be empty."); continue; }
            if (choice == 1) index = linear_search_title(library->items, library->count, title);
            else {
                ensure_title_order(library);
                if (!books_sorted_by_title(library->items, library->count)) continue;
                index = choice == 2
                    ? binary_search_title_iterative(library->items, library->count, title)
                    : binary_search_title_recursive(library->items, library->count, title);
            }
            show_search_result(library, index);
        } else if (choice == 4) {
            puts(merge_sort_books(library->items, library->count)
                ? "Merge Sort completed. Books are now in alphabetical order."
                : "Merge Sort could not allocate the required temporary memory.");
        } else if (choice == 5) {
            quick_sort_books(library->items, library->count);
            puts("Quick Sort completed. Books are now in alphabetical order.");
        } else if (choice == 6) library_list(library);
        else puts("Unknown option. Try again.");
    }
}

static void maximum_subarray_menu(void) {
    int count;
    if (!read_int("How many integers (1-1000)? ", &count) || count < 1 || count > 1000) {
        puts("Please enter a count from 1 to 1000."); return;
    }
    long long *values = (long long *)malloc((size_t)count * sizeof(long long));
    if (!values) { puts("Not enough memory."); return; }
    for (int i=0;i<count;i++) {
        int value;
        char prompt[48];
        snprintf(prompt,sizeof prompt,"Value %d: ",i+1);
        if (!read_int(prompt,&value)) { puts("Invalid value."); free(values); return; }
        values[i]=value;
    }
    MaxSubarrayResult result;
    if (maximum_subarray_divide_conquer(values,(size_t)count,&result))
        printf("Maximum subarray sum: %lld\nZero-based range: %zu to %zu\n",
               result.sum,result.start,result.end);
    else puts("Could not calculate the maximum subarray.");
    free(values);
}

static void fast_power_menu(void) {
    int base, exponent;
    if (!read_int("Enter integer base: ",&base) ||
        !read_int("Enter non-negative exponent: ",&exponent) || exponent < 0) {
        puts("Invalid base or exponent."); return;
    }
    long long result;
    if (fast_power(base,(unsigned int)exponent,&result))
        printf("Result: %lld\n",result);
    else puts("The result is outside the range of long long.");
}

static void celebrity_menu(void) {
    int count;
    if (!read_int("Number of people (1-20): ",&count) || count < 1 || count > 20) {
        puts("Please enter a count from 1 to 20."); return;
    }
    int matrix[400];
    puts("Enter the 0/1 knows matrix row by row (person i knows person j):");
    for (int i=0;i<count;i++) for (int j=0;j<count;j++) {
        char prompt[48];
        int value;
        snprintf(prompt,sizeof prompt,"knows[%d][%d]: ",i,j);
        if (!read_int(prompt,&value) || (value != 0 && value != 1)) {
            puts("Every matrix entry must be 0 or 1."); return;
        }
        matrix[i*count+j]=value;
    }
    int answer=celebrity_divide_conquer(matrix,(size_t)count);
    if (answer < 0) puts("No celebrity exists.");
    else printf("Celebrity found: person %d (zero-based index).\n",answer);
}

static void matrix_menu(void) {
    int n;
    if (!read_int("Enter square matrix dimension (1-8): ",&n) || n < 1 || n > 8) {
        puts("Please enter a dimension from 1 to 8."); return;
    }
    long long a[64],b[64],classic[64],strassen[64];
    puts("Enter Matrix A row by row:");
    for (int i=0;i<n*n;i++) {
        int value;
        if (!read_int("Value: ",&value)) { puts("Invalid matrix value."); return; }
        a[i]=value;
    }
    puts("Enter Matrix B row by row:");
    for (int i=0;i<n*n;i++) {
        int value;
        if (!read_int("Value: ",&value)) { puts("Invalid matrix value."); return; }
        b[i]=value;
    }
    if (!matrix_multiply_classical(a,b,classic,(size_t)n) ||
        !matrix_multiply_strassen(a,b,strassen,(size_t)n)) {
        puts("Matrix multiplication failed."); return;
    }
    puts("\nClassical multiplication result:");
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++) printf("%lld ",classic[i*n+j]);
        putchar('\n');
    }
    puts("Strassen multiplication result:");
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++) printf("%lld ",strassen[i*n+j]);
        putchar('\n');
    }
    puts("Both methods should produce the same result.");
}

static void divide_conquer_menu(void) {
    int choice;
    for (;;) {
        puts("\n========== PHASE 3: DIVIDE AND CONQUER ==========");
        puts("1. Maximum Subarray");
        puts("2. Fast Powering");
        puts("3. Celebrity Problem");
        puts("4. Classical Matrix Multiplication");
        puts("5. Strassen Matrix Multiplication (compared with classical)");
        puts("0. Return to main menu");
        if (!read_int("Choose an option: ",&choice)) { puts("Enter a valid number."); continue; }
        switch (choice) {
            case 0: return;
            case 1: maximum_subarray_menu(); break;
            case 2: fast_power_menu(); break;
            case 3: celebrity_menu(); break;
            case 4:
            case 5: matrix_menu(); break;
            default: puts("Unknown option. Try again.");
        }
    }
}

int main(void) {
    Library library;
    int choice;
    library_init(&library);
    if (!library_load_csv(&library, DATA_FILE))
        puts("Note: starting with an empty library (CSV could not be loaded).");

    for (;;) {
        puts("\n========== DIGITAL LIBRARY: PHASES 1, 2 AND 3 ==========");
        puts("1. Add a book");
        puts("2. List all books");
        puts("3. Search books by title (contains text)");
        puts("4. Update a book");
        puts("5. Delete a book");
        puts("6. Save library");
        puts("7. Phase 2: Searching and Sorting Algorithms");
        puts("8. Phase 3: Divide-and-Conquer Algorithms");
        puts("0. Save and exit");
        if (!read_int("Choose an option: ", &choice)) {
            puts("Please enter a valid number."); continue;
        }
        if (choice == 0) {
            if (!library_save_csv(&library, DATA_FILE)) puts("Warning: could not save data.");
            else puts("Data saved. Goodbye!");
            break;
        }
        switch (choice) {
            case 1: add_book(&library); break;
            case 2: library_list(&library); break;
            case 3: {
                char query[TITLE_LEN];
                read_line("Enter title text to search: ", query, sizeof query);
                library_search_title(&library, query);
                break;
            }
            case 4: edit_book(&library); break;
            case 5: delete_book(&library); break;
            case 6: puts(library_save_csv(&library, DATA_FILE) ? "Library saved." : "Save failed."); break;
            case 7: search_sort_menu(&library); break;
            case 8: divide_conquer_menu(); break;
            default: puts("Unknown option. Try again.");
        }
    }
    library_free(&library);
    return 0;
}

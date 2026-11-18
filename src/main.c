#include "book.h"
#include "library.h"
#include <stdio.h>
#include <string.h>

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

int main(void) {
    Library library;
    int choice;
    library_init(&library);
    if (!library_load_csv(&library, DATA_FILE))
        puts("Note: starting with an empty library (CSV could not be loaded).");

    for (;;) {
        puts("\n========== DIGITAL LIBRARY: PHASE 1 ==========");
        puts("1. Add a book");
        puts("2. List all books");
        puts("3. Search books by title");
        puts("4. Update a book");
        puts("5. Delete a book");
        puts("6. Save library");
        puts("0. Save and exit");
        if (!read_int("Choose an option: ", &choice)) { puts("Please enter a valid number."); continue; }

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
            case 6:
                puts(library_save_csv(&library, DATA_FILE) ? "Library saved." : "Save failed.");
                break;
            default: puts("Unknown option. Try again.");
        }
    }
    library_free(&library);
    return 0;
}

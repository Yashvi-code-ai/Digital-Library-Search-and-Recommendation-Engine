#ifndef LIBRARY_H
#define LIBRARY_H

#include "book.h"
#include <stddef.h>

#define INITIAL_CAPACITY 10

typedef struct {
    Book *items;
    size_t count;
    size_t capacity;
} Library;

void library_init(Library *library);
void library_free(Library *library);
int library_add(Library *library, const Book *book);
int library_find_id(const Library *library, int id);
int library_remove(Library *library, int id);
int library_update(Library *library, int id, const Book *replacement);
void library_list(const Library *library);
void library_search_title(const Library *library, const char *query);
int library_load_csv(Library *library, const char *path);
int library_save_csv(const Library *library, const char *path);
int library_next_id(const Library *library);

#endif

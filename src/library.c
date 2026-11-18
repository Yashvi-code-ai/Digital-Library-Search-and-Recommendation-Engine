#include "library.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static int ensure_capacity(Library *library) {
    if (library->count < library->capacity) return 1;
    size_t next = library->capacity ? library->capacity * 2 : INITIAL_CAPACITY;
    Book *grown = realloc(library->items, next * sizeof *grown);
    if (!grown) return 0;
    library->items = grown;
    library->capacity = next;
    return 1;
}

void library_init(Library *library) {
    library->items = NULL;
    library->count = 0;
    library->capacity = 0;
}

void library_free(Library *library) {
    free(library->items);
    library_init(library);
}

int library_find_id(const Library *library, int id) {
    for (size_t i = 0; i < library->count; i++)
        if (library->items[i].id == id) return (int)i;
    return -1;
}

int library_add(Library *library, const Book *book) {
    if (!book || book->id <= 0 || library_find_id(library, book->id) >= 0) return 0;
    if (!ensure_capacity(library)) return 0;
    library->items[library->count++] = *book;
    return 1;
}

int library_remove(Library *library, int id) {
    int index = library_find_id(library, id);
    if (index < 0) return 0;
    for (size_t i = (size_t)index; i + 1 < library->count; i++)
        library->items[i] = library->items[i + 1];
    library->count--;
    return 1;
}

int library_update(Library *library, int id, const Book *replacement) {
    int index = library_find_id(library, id);
    if (index < 0 || !replacement) return 0;
    Book copy = *replacement;
    copy.id = id;
    library->items[index] = copy;
    return 1;
}

void library_list(const Library *library) {
    if (!library->count) {
        puts("\nThe library is empty.");
        return;
    }
    printf("\n%-6s %-30s %-22s %-16s\n", "ID", "TITLE", "AUTHOR", "CATEGORY");
    puts("--------------------------------------------------------------------------");
    for (size_t i = 0; i < library->count; i++)
        printf("%-6d %-30.30s %-22.22s %-16.16s\n",
               library->items[i].id, library->items[i].title,
               library->items[i].author, library->items[i].category);
}

static int contains_case_insensitive(const char *text, const char *query) {
    size_t n = strlen(query);
    if (!n) return 1;
    for (; *text; text++) {
        size_t i = 0;
        while (i < n && text[i] &&
               tolower((unsigned char)text[i]) == tolower((unsigned char)query[i])) i++;
        if (i == n) return 1;
    }
    return 0;
}

void library_search_title(const Library *library, const char *query) {
    int found = 0;
    for (size_t i = 0; i < library->count; i++) {
        if (contains_case_insensitive(library->items[i].title, query)) {
            print_book(&library->items[i]);
            found++;
        }
    }
    if (!found) puts("\nNo matching title found.");
}

/* CSV helpers support quoted fields and escaped double quotes. */
static void csv_write_field(FILE *file, const char *value) {
    fputc('"', file);
    for (; *value; value++) {
        if (*value == '"') fputc('"', file);
        fputc(*value, file);
    }
    fputc('"', file);
}

static int csv_read_field(char **cursor, char *out, size_t size) {
    size_t used = 0;
    const char *p = *cursor;
    int quoted = (*p == '"');
    if (quoted) p++;
    while (*p) {
        if (quoted && *p == '"') {
            if (p[1] == '"') { if (used + 1 < size) out[used++] = '"'; p += 2; continue; }
            p++;
            break;
        }
        if (!quoted && *p == ',') break;
        if (used + 1 < size) out[used++] = *p;
        p++;
    }
    out[used] = '\0';
    if (*p == ',') p++;
    *cursor = p;
    return 1;
}

int library_save_csv(const Library *library, const char *path) {
    FILE *file = fopen(path, "w");
    if (!file) return 0;
    fputs("id,title,author,category,keywords,citations,popularity\n", file);
    for (size_t i = 0; i < library->count; i++) {
        const Book *b = &library->items[i];
        fprintf(file, "%d,", b->id);
        csv_write_field(file, b->title); fputc(',', file);
        csv_write_field(file, b->author); fputc(',', file);
        csv_write_field(file, b->category); fputc(',', file);
        csv_write_field(file, b->keywords);
        fprintf(file, ",%d,%d\n", b->citations, b->popularity);
    }
    int ok = !ferror(file);
    if (fclose(file) != 0) ok = 0;
    return ok;
}

int library_load_csv(Library *library, const char *path) {
    FILE *file = fopen(path, "r");
    if (!file) return 0;
    char line[2048];
    if (!fgets(line, sizeof line, file)) { fclose(file); return 1; }
    while (fgets(line, sizeof line, file)) {
        Book b = {0};
        char *cursor = line, field[KEYWORDS_LEN + 1], *end;
        long number;
        if (!csv_read_field(&cursor, field, sizeof field)) continue;
        number = strtol(field, &end, 10);
        if (*end || number <= 0 || number > 2147483647L) continue;
        b.id = (int)number;
        csv_read_field(&cursor, b.title, sizeof b.title);
        csv_read_field(&cursor, b.author, sizeof b.author);
        csv_read_field(&cursor, b.category, sizeof b.category);
        csv_read_field(&cursor, b.keywords, sizeof b.keywords);
        if (sscanf(cursor, "%d,%d", &b.citations, &b.popularity) != 2 ||
            b.citations < 0 || b.popularity < 0) continue;
        if (!library_add(library, &b)) {
            if (library_find_id(library, b.id) >= 0) continue;
            fclose(file);
            return 0;
        }
    }
    int ok = !ferror(file);
    fclose(file);
    return ok;
}

int library_next_id(const Library *library) {
    int max_id = 0;
    for (size_t i = 0; i < library->count; i++)
        if (library->items[i].id > max_id) max_id = library->items[i].id;
    return max_id == 2147483647 ? 1 : max_id + 1;
}

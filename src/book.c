#include "book.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void read_line(const char *prompt, char *buffer, int capacity) {
    int ch;
    printf("%s", prompt);
    if (!fgets(buffer, capacity, stdin)) {
        buffer[0] = '\0';
        return;
    }
    size_t length = strlen(buffer);
    if (length > 0 && buffer[length - 1] == '\n') {
        buffer[length - 1] = '\0';
    } else {
        while ((ch = getchar()) != '\n' && ch != EOF) {}
    }
}

int read_int(const char *prompt, int *value) {
    char line[64], *end;
    long parsed;
    read_line(prompt, line, sizeof line);
    if (line[0] == '\0') return 0;
    parsed = strtol(line, &end, 10);
    while (isspace((unsigned char)*end)) end++;
    if (*end != '\0' || parsed < 0 || parsed > 2147483647L) return 0;
    *value = (int)parsed;
    return 1;
}

void print_book(const Book *book) {
    printf("\nID: %d\nTitle: %s\nAuthor: %s\nCategory: %s\nKeywords: %s\nCitations: %d\nPopularity: %d\n",
           book->id, book->title, book->author, book->category,
           book->keywords, book->citations, book->popularity);
}

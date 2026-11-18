#ifndef BOOK_H
#define BOOK_H

#define TITLE_LEN 100
#define AUTHOR_LEN 100
#define CATEGORY_LEN 50
#define KEYWORDS_LEN 200

typedef struct {
    int id;
    char title[TITLE_LEN];
    char author[AUTHOR_LEN];
    char category[CATEGORY_LEN];
    char keywords[KEYWORDS_LEN];
    int citations;
    int popularity;
} Book;

void read_line(const char *prompt, char *buffer, int capacity);
int read_int(const char *prompt, int *value);
void print_book(const Book *book);

#endif

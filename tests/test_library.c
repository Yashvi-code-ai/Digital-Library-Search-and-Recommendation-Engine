#include "library.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    Library library, loaded;
    Book first = {0}, replacement = {0};
    library_init(&library);
    library_init(&loaded);

    first.id = 1;
    strcpy(first.title, "Algorithms, Illustrated");
    strcpy(first.author, "A. Writer");
    strcpy(first.category, "Computer Science");
    strcpy(first.keywords, "graphs sorting");
    first.citations = 12;
    first.popularity = 7;

    assert(library_add(&library, &first));
    assert(!library_add(&library, &first)); /* duplicate ID */
    assert(library_find_id(&library, 1) == 0);
    assert(library_find_id(&library, 99) == -1);
    assert(library_recommend_category(&library, "computer science") == 1);
    assert(library_recommend_category(&library, "History") == 0);

    replacement = first;
    strcpy(replacement.title, "Updated Algorithms");
    assert(library_update(&library, 1, &replacement));
    assert(strcmp(library.items[0].title, "Updated Algorithms") == 0);

    assert(library_save_csv(&library, "tests/test_books_tmp.csv"));
    assert(library_load_csv(&loaded, "tests/test_books_tmp.csv"));
    assert(loaded.count == 1);
    assert(strcmp(loaded.items[0].title, "Updated Algorithms") == 0);
    assert(loaded.items[0].citations == 12);

    assert(library_remove(&loaded, 1));
    assert(!library_remove(&loaded, 1));

    remove("tests/test_books_tmp.csv");
    library_free(&library);
    library_free(&loaded);
    puts("All library tests passed.");
    return 0;
}

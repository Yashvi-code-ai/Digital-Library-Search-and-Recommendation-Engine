#include "algorithms.h"
#include "greedy.h"
#include "dp.h"
#include "backtracking.h"
#include <assert.h>
#include <stdio.h>

int main(void) {
    Book books[3] = {{.title = "Zebra"}, {.title = "Apple"}, {.title = "Mango"}};
    assert(linear_search_title(books, 3, "mango") == 2);
    assert(linear_search_title(books, 3, "Missing") == -1);
    assert(merge_sort_books(books, 3));
    assert(books[0].title[0] == 'A');
    assert(books[1].title[0] == 'M');
    assert(books[2].title[0] == 'Z');

    Activity activities[] = {{1, 2}, {3, 4}, {0, 6}, {5, 7}, {8, 9}, {5, 9}};
    size_t selected[6];
    assert(greedy_activity_selection(activities, 6, selected) == 4);

    int weights[] = {2, 3, 4, 5};
    int values[] = {3, 4, 5, 6};
    long long best;
    assert(dp_knapsack(weights, values, 4, 5, &best) && best == 7);

    assert(bt_nqueens_count(4) == 2);
    assert(bt_nqueens_count(1) == 1);
    assert(bt_nqueens_count(0) == -1);

    puts("All five DAA algorithm tests passed.");
    return 0;
}

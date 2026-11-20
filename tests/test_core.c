#include "algorithms.h"
#include "divide_conquer.h"
#include "greedy.h"
#include "dp.h"
#include "backtracking.h"
#include "string_number_theory.h"
#include <assert.h>
#include <stdio.h>

int main(void) {
    Book books[3] = {{.title="Zebra"}, {.title="Apple"}, {.title="Mango"}};
    assert(linear_search_title(books, 3, "mango") == 2);
    assert(merge_sort_books(books, 3));
    assert(binary_search_title(books, 3, "APPLE") == 0);

    long long values[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    MaxSubarrayResult result;
    assert(maximum_subarray_divide_conquer(values, 9, &result));
    assert(result.sum == 6 && result.start == 3 && result.end == 6);

    Activity activities[] = {{1, 2}, {3, 4}, {0, 6}, {5, 7}, {8, 9}, {5, 9}};
    size_t selected[6];
    assert(greedy_activity_selection(activities, 6, selected) == 4);

    int graph[] = {
        0, 10, 0, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 0, 2, 0,
        0, 0, 0, 0, 3,
        0, 0, 0, 0, 0
    };
    long long distance[5];
    int parent[5];
    assert(greedy_dijkstra(graph, 5, 0, distance, parent));
    assert(distance[4] == 16);

    int weights[] = {2, 3, 4, 5};
    int profits[] = {3, 4, 5, 6};
    long long best;
    assert(dp_knapsack(weights, profits, 4, 5, &best) && best == 7);

    assert(bt_nqueens_count(4) == 2);
    int set[] = {3, 34, 4, 12, 5, 2};
    assert(bt_subset_sum(set, 6, 9));

    assert(string_match_kmp("ABABDABACDABABCABAB", "ABABCABAB") == 10);
    puts("All retained algorithm tests passed.");
    return 0;
}

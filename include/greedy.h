#ifndef GREEDY_H
#define GREEDY_H

#include <stddef.h>

typedef struct { int start, finish; } Activity;
typedef struct { int start, finish, original_index, room; } ScheduledActivity;
typedef struct { int u, v, weight; } WeightedEdge;
typedef struct { int weight; double value; } KnapsackItem;
typedef struct { char symbol; unsigned long long frequency; } HuffmanSymbol;

/* Returns selected activity count; selected_indices receives original indices. */
size_t greedy_activity_selection(const Activity *activities, size_t count,
                                 size_t *selected_indices);
/* Returns minimum rooms used, or 0 for invalid input/allocation failure. */
size_t greedy_interval_partition(const Activity *activities, size_t count,
                                 ScheduledActivity *schedule);

/* Graph is an n-by-n adjacency matrix. 0 means no edge; weights must be >= 0. */
int greedy_dijkstra(const int *graph, size_t n, size_t source,
                    long long *distances, int *parents);
int greedy_prim(const int *graph, size_t n, WeightedEdge *tree_edges,
                long long *total_weight);
int greedy_kruskal(const WeightedEdge *edges, size_t edge_count, size_t vertices,
                   WeightedEdge *tree_edges, size_t *tree_count,
                   long long *total_weight);

/* Generates prefix-free Huffman codes; caller supplies code strings [symbol_count][256]. */
int greedy_huffman(const HuffmanSymbol *symbols, size_t symbol_count,
                   char codes[][256]);

/* Returns maximum value; fractions[i] is the fraction of item i selected. */
int greedy_fractional_knapsack(const KnapsackItem *items, size_t count,
                               int capacity, double *fractions,
                               double *total_value);

#endif

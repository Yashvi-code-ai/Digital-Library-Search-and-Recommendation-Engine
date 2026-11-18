#ifndef BACKTRACKING_H
#define BACKTRACKING_H
#include <stddef.h>
long long bt_nqueens_count(int n);
int bt_subset_sum(const int *values,size_t n,int target);
int bt_knapsack(const int *weights,const int *values,size_t n,int capacity,long long *best);
enum { BT_LIFO=0, BT_FIFO=1, BT_LEAST_COST=2 };
int bt_knapsack_bnb(const int *weights,const int *values,size_t n,int capacity,int strategy,long long *best);
#endif

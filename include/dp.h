#ifndef DP_H
#define DP_H
#include <stddef.h>
#include <limits.h>
int dp_knapsack(const int*,const int*,size_t,int,long long*);
int dp_chain(const int*,size_t,long long*);
int dp_lcs(const char*,const char*,size_t*);
int dp_obst(const int*,size_t,long long*);
int dp_bellman(const int*,size_t,size_t,size_t,long long*);
int dp_floyd(long long*,size_t);
int dp_tsp(const int*,size_t,long long*);
#endif

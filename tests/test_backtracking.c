#include "backtracking.h"
#include <assert.h>
#include <stdio.h>
int main(void){assert(bt_nqueens_count(4)==2);int a[]={3,7,2,9};assert(bt_subset_sum(a,4,12));assert(!bt_subset_sum(a,4,30));int w[]={2,3,4,5},v[]={3,4,5,6};long long x,y;assert(bt_knapsack(w,v,4,5,&x)&&x==7);for(int s=0;s<3;s++)assert(bt_knapsack_bnb(w,v,4,5,s,&y)&&y==7);puts("Phase 6 tests passed.");return 0;}

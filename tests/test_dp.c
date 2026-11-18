#include "dp.h"
#include <assert.h>
#include <stdio.h>
int main(void){long long z;size_t l;int w[]={1,3,4},v[]={15,20,30};assert(dp_knapsack(w,v,3,4,&z)&&z==35);int d[]={10,30,5,60};assert(dp_chain(d,3,&z)&&z==4500);assert(dp_lcs("ABCBDAB","BDCABA",&l)&&l==4);int f[]={3,1,2};assert(dp_obst(f,3,&z)&&z==11);int e[]={0,1,4,0,2,5,1,2,-2,2,3,3};long long ds[4];assert(dp_bellman(e,4,4,0,ds)==1&&ds[3]==6);int g[]={0,10,15,20,10,0,35,25,15,35,0,30,20,25,30,0};assert(dp_tsp(g,4,&z)&&z==80);puts("Phase 5 tests passed");}

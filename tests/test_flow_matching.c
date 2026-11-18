#include "flow_matching.h"
#include <assert.h>
#include <stdio.h>
int main(void){int c[]={0,16,13,0,0,0,0,10,12,0,0,4,0,0,14,0,0,9,0,20,0,0,0,7,0};long long f;assert(flow_ford_fulkerson(c,5,0,4,&f)&&f==23);int a[]={1,1,0,0,1,0,1,0,1};int lm[3],rm[3];size_t m;assert(flow_bipartite_matching(a,3,3,lm,rm,&m)&&m==3);puts("Phase 7 flow/matching tests passed.");return 0;}

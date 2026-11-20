#include "algorithms.h"
#include "divide_conquer.h"
#include "greedy.h"
#include "dp.h"
#include "backtracking.h"
#include "flow_matching.h"
#include "string_number_theory.h"
#include "analysis.h"
#include <assert.h>
#include <limits.h>
#include <stdio.h>

int main(void){
    Book books[3]={{.title="Zebra"},{.title="Apple"},{.title="Mango"}};
    assert(linear_search_title(books,3,"mango")==2);
    assert(merge_sort_books(books,3));
    assert(binary_search_title(books,3,"APPLE")==0);

    long long values[]={-2,1,-3,4,-1,2,1,-5,4};
    MaxSubarrayResult max;
    assert(maximum_subarray_divide_conquer(values,9,&max));
    assert(max.sum==6&&max.start==3&&max.end==6);

    Activity activities[]={{1,2},{3,4},{0,6},{5,7},{8,9},{5,9}};
    size_t selected[6];
    assert(greedy_activity_selection(activities,6,selected)==4);

    int graph[]={0,10,0,0,0, 0,0,1,0,0, 0,0,0,2,0, 0,0,0,0,3, 0,0,0,0,0};
    long long dist[5];int parent[5];
    assert(greedy_dijkstra(graph,5,0,dist,parent));
    assert(dist[4]==16);

    int weights[]={2,3,4,5},profits[]={3,4,5,6};long long best;
    assert(dp_knapsack(weights,profits,4,5,&best)&&best==7);
    assert(bt_nqueens_count(4)==2);
    int set[]={3,34,4,12,5,2};
    assert(bt_subset_sum(set,6,9));

    int cap[]={0,16,13,0,0,0, 0,0,10,12,0,0, 0,4,0,0,14,0,
               0,0,9,0,0,20, 0,0,0,7,0,4, 0,0,0,0,0,0};
    long long flow;
    assert(flow_ford_fulkerson(cap,6,0,5,&flow)&&flow==23);

    assert(string_match_kmp("ABABDABACDABABCABAB","ABABCABAB")==10);
    long long rem[]={2,3,2},mods[]={3,5,7},answer;
    assert(crt_solve(rem,mods,3,&answer)&&answer==23);
    size_t cover;
    assert(analysis_reduce_independent_set_to_vertex_cover(10,4,&cover)&&cover==6);
    puts("All core algorithm tests passed.");
    return 0;
}

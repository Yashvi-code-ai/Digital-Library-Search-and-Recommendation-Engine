#include "greedy.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

static void test_activity_and_rooms(void){
    const Activity a[]={{1,4},{3,5},{0,6},{5,7},{8,9},{5,9}};
    size_t chosen[6];
    size_t n=greedy_activity_selection(a,6,chosen);
    assert(n==3);
    ScheduledActivity schedule[6];
    assert(greedy_interval_partition(a,6,schedule)==3);
}
static void test_graphs(void){
    const int g[]={0,10,0,30,100, 10,0,50,0,0, 0,50,0,20,10,
                   30,0,20,0,60, 100,0,10,60,0};
    long long dist[5];int parent[5];
    assert(greedy_dijkstra(g,5,0,dist,parent));
    assert(dist[0]==0&&dist[1]==10&&dist[2]==50&&dist[3]==30&&dist[4]==60);
    WeightedEdge prim[4];long long prim_cost;
    assert(greedy_prim(g,5,prim,&prim_cost));
    const WeightedEdge edges[]={{0,1,10},{0,3,30},{0,4,100},{1,2,50},
        {2,3,20},{2,4,10},{3,4,60}};
    WeightedEdge kruskal[4];size_t used;long long cost;
    assert(greedy_kruskal(edges,7,5,kruskal,&used,&cost));
    assert(used==4&&cost==70&&prim_cost==70);
}
static void test_huffman_and_knapsack(void){
    const HuffmanSymbol symbols[]={{'A',5},{'B',9},{'C',12},{'D',13},{'E',16},{'F',45}};
    char codes[6][256];
    assert(greedy_huffman(symbols,6,codes));
    for(int i=0;i<6;i++)for(int j=i+1;j<6;j++){
        size_t li=strlen(codes[i]),lj=strlen(codes[j]);
        assert(strncmp(codes[i],codes[j],li<lj?li:lj)!=0 ||
               (li==lj));
    }
    const KnapsackItem items[]={{10,60},{20,100},{30,120}};
    double fractions[3],value;
    assert(greedy_fractional_knapsack(items,3,50,fractions,&value));
    assert(value>239.99&&value<240.01);
}
int main(void){
    test_activity_and_rooms();test_graphs();test_huffman_and_knapsack();
    puts("Phase 4 greedy algorithm tests passed.");return 0;
}

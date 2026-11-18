#include "greedy.h"

#include <limits.h>
#include <stdlib.h>
#include <string.h>

static void sort_activities(ScheduledActivity *a, size_t n, int by_finish) {
    for (size_t i=1;i<n;i++) {
        ScheduledActivity key=a[i]; size_t j=i;
        while (j>0) {
            int move = by_finish
                ? (a[j-1].finish > key.finish ||
                   (a[j-1].finish == key.finish && a[j-1].start > key.start))
                : (a[j-1].start > key.start ||
                   (a[j-1].start == key.start && a[j-1].finish > key.finish));
            if (!move) break;
            a[j]=a[j-1]; --j;
        }
        a[j]=key;
    }
}

size_t greedy_activity_selection(const Activity *activities, size_t count,
                                 size_t *selected_indices) {
    if ((!activities && count) || (!selected_indices && count)) return 0;
    if (!count) return 0;
    ScheduledActivity *copy=(ScheduledActivity *)malloc(count*sizeof(*copy));
    if (!copy) return 0;
    for(size_t i=0;i<count;i++) {
        if(activities[i].finish < activities[i].start) { free(copy); return 0; }
        copy[i]=(ScheduledActivity){activities[i].start,activities[i].finish,(int)i,0};
    }
    sort_activities(copy,count,1);
    size_t used=0; int last_finish=INT_MIN;
    for(size_t i=0;i<count;i++) {
        if(copy[i].start >= last_finish) {
            selected_indices[used++]=(size_t)copy[i].original_index;
            last_finish=copy[i].finish;
        }
    }
    free(copy); return used;
}

size_t greedy_interval_partition(const Activity *activities, size_t count,
                                 ScheduledActivity *schedule) {
    if ((!activities && count) || (!schedule && count)) return 0;
    if (!count) return 0;
    for(size_t i=0;i<count;i++) {
        if(activities[i].finish < activities[i].start) return 0;
        schedule[i]=(ScheduledActivity){activities[i].start,activities[i].finish,(int)i,-1};
    }
    sort_activities(schedule,count,0);
    int *room_finish=(int *)malloc(count*sizeof(int));
    if(!room_finish) return 0;
    size_t rooms=0;
    for(size_t i=0;i<count;i++) {
        size_t room=0;
        while(room<rooms && room_finish[room] > schedule[i].start) room++;
        if(room==rooms) room_finish[rooms++]=schedule[i].finish;
        else room_finish[room]=schedule[i].finish;
        schedule[i].room=(int)room;
    }
    free(room_finish); return rooms;
}

int greedy_dijkstra(const int *g,size_t n,size_t source,long long *dist,int *parent) {
    if(!g || !dist || !parent || !n || source>=n || n>SIZE_MAX/n) return 0;
    unsigned char *used=(unsigned char *)calloc(n,1);
    if(!used) return 0;
    for(size_t i=0;i<n;i++){ dist[i]=LLONG_MAX; parent[i]=-1; }
    dist[source]=0;
    for(size_t step=0;step<n;step++) {
        size_t u=n; long long best=LLONG_MAX;
        for(size_t i=0;i<n;i++) if(!used[i] && dist[i]<best){best=dist[i];u=i;}
        if(u==n) break;
        used[u]=1;
        for(size_t v=0;v<n;v++) {
            int w=g[u*n+v];
            if(w<0){free(used);return 0;}
            if(w>0 && !used[v] && dist[u]<=LLONG_MAX-w &&
               dist[u]+w<dist[v]) {dist[v]=dist[u]+w;parent[v]=(int)u;}
        }
    }
    free(used); return 1;
}

int greedy_prim(const int *g,size_t n,WeightedEdge *edges,long long *total) {
    if(!g || !edges || !total || !n || n>SIZE_MAX/n) return 0;
    long long *key=(long long *)malloc(n*sizeof(long long));
    int *parent=(int *)malloc(n*sizeof(int));
    unsigned char *used=(unsigned char *)calloc(n,1);
    if(!key||!parent||!used){free(key);free(parent);free(used);return 0;}
    for(size_t i=0;i<n;i++){key[i]=LLONG_MAX;parent[i]=-1;}
    key[0]=0; *total=0;
    for(size_t step=0;step<n;step++){
        size_t u=n; long long best=LLONG_MAX;
        for(size_t i=0;i<n;i++)if(!used[i]&&key[i]<best){best=key[i];u=i;}
        if(u==n){free(key);free(parent);free(used);return 0;}
        used[u]=1;
        if(parent[u]>=0){edges[step-1]=(WeightedEdge){parent[u],(int)u,(int)key[u]};*total+=key[u];}
        for(size_t v=0;v<n;v++){
            int w=g[u*n+v]; if(w<0){free(key);free(parent);free(used);return 0;}
            if(w>0&&!used[v]&&w<key[v]){key[v]=w;parent[v]=(int)u;}
        }
    }
    free(key);free(parent);free(used);return 1;
}

static int edge_compare(const void *x,const void *y){
    const WeightedEdge *a=(const WeightedEdge *)x,*b=(const WeightedEdge *)y;
    return (a->weight>b->weight)-(a->weight<b->weight);
}
static size_t dsu_find(size_t *p,size_t x){while(p[x]!=x){p[x]=p[p[x]];x=p[x];}return x;}
int greedy_kruskal(const WeightedEdge *edges,size_t ec,size_t vertices,
                   WeightedEdge *tree,size_t *tree_count,long long *total){
    if(!edges||!tree||!tree_count||!total||!vertices)return 0;
    WeightedEdge *copy=(WeightedEdge *)malloc((ec ? ec : 1)*sizeof(*copy));
    size_t *p=(size_t *)malloc(vertices*sizeof(*p));
    unsigned char *rank=(unsigned char *)calloc(vertices,1);
    if((ec&&!copy)||!p||!rank){free(copy);free(p);free(rank);return 0;}
    memcpy(copy,edges,ec*sizeof(*copy));qsort(copy,ec,sizeof(*copy),edge_compare);
    for(size_t i=0;i<vertices;i++)p[i]=i;
    *tree_count=0;*total=0;
    for(size_t i=0;i<ec&&*tree_count+1<vertices;i++){
        if(copy[i].u<0||copy[i].v<0||(size_t)copy[i].u>=vertices||(size_t)copy[i].v>=vertices){free(copy);free(p);free(rank);return 0;}
        size_t a=dsu_find(p,(size_t)copy[i].u),b=dsu_find(p,(size_t)copy[i].v);
        if(a!=b){
            if(rank[a]<rank[b])p[a]=b;else if(rank[a]>rank[b])p[b]=a;else{p[b]=a;rank[a]++;}
            tree[(*tree_count)++]=copy[i];*total+=copy[i].weight;
        }
    }
    int connected=(*tree_count==vertices-1);
    free(copy);free(p);free(rank);return connected;
}

typedef struct { unsigned long long freq; int left,right,symbol; } HuffNode;
static void build_codes(const HuffNode *nodes,int index,char *path,size_t depth,
                        char codes[][256]){
    const HuffNode *node=&nodes[index];
    if(node->symbol>=0){
        if(depth==0){codes[node->symbol][0]='0';codes[node->symbol][1]='\0';}
        else{memcpy(codes[node->symbol],path,depth);codes[node->symbol][depth]='\0';}
        return;
    }
    if(depth>=254)return;
    path[depth]='0';build_codes(nodes,node->left,path,depth+1,codes);
    path[depth]='1';build_codes(nodes,node->right,path,depth+1,codes);
}
int greedy_huffman(const HuffmanSymbol *symbols,size_t n,char codes[][256]){
    if(!symbols||!codes||!n||n>127)return 0;
    HuffNode *nodes=(HuffNode *)calloc(2*n-1,sizeof(*nodes));
    unsigned char *active=(unsigned char *)calloc(2*n-1,1);
    if(!nodes||!active){free(nodes);free(active);return 0;}
    for(size_t i=0;i<n;i++){nodes[i]=(HuffNode){symbols[i].frequency,-1,-1,(int)i};active[i]=1;codes[i][0]='\0';}
    size_t total=2*n-1;
    for(size_t next=n;next<total;next++){
        int a=-1,b=-1;
        for(size_t j=0;j<next;j++)if(active[j]){
            if(a<0||nodes[j].freq<nodes[a].freq){b=a;a=(int)j;}
            else if(b<0||nodes[j].freq<nodes[b].freq)b=(int)j;
        }
        if(a<0||b<0){free(nodes);free(active);return 0;}
        active[a]=active[b]=0;
        nodes[next]=(HuffNode){nodes[a].freq+nodes[b].freq,a,b,-1};
        active[next]=1;
    }
    char path[256];build_codes(nodes,(int)(total-1),path,0,codes);
    free(nodes);free(active);return 1;
}

typedef struct {size_t index;double ratio;} RatioItem;
static int ratio_compare(const void *x,const void *y){
    double a=((const RatioItem *)x)->ratio,b=((const RatioItem *)y)->ratio;
    return (a<b)-(a>b);
}
int greedy_fractional_knapsack(const KnapsackItem *items,size_t n,int capacity,
                               double *fractions,double *total){
    if((!items&&n)||(!fractions&&n)||!total||capacity<0)return 0;
    RatioItem *order=(RatioItem *)malloc(n*sizeof(*order));
    if(n&&!order)return 0;
    for(size_t i=0;i<n;i++){
        if(items[i].weight<=0||items[i].value<0){free(order);return 0;}
        order[i]=(RatioItem){i,items[i].value/items[i].weight};fractions[i]=0.0;
    }
    qsort(order,n,sizeof(*order),ratio_compare);*total=0.0;
    int remaining=capacity;
    for(size_t k=n;k>0&&remaining>0;k--){
        size_t i=order[k-1].index;
        int take=items[i].weight<remaining?items[i].weight:remaining;
        fractions[i]=(double)take/items[i].weight;
        *total+=fractions[i]*items[i].value;remaining-=take;
    }
    free(order);return 1;
}

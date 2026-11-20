#include "greedy.h"
#include <limits.h>
#include <stdlib.h>
size_t greedy_activity_selection(const Activity *a,size_t n,size_t *selected){
    if((n&&!a)||(n&&!selected))return 0;
    Activity *copy=malloc(n*sizeof(*copy));size_t *ids=malloc(n*sizeof(*ids));
    if(n&&(!copy||!ids)){free(copy);free(ids);return 0;}
    for(size_t i=0;i<n;i++){if(a[i].finish<a[i].start){free(copy);free(ids);return 0;}copy[i]=a[i];ids[i]=i;}
    for(size_t i=1;i<n;i++){Activity key=copy[i];size_t id=ids[i],j=i;
        while(j&&copy[j-1].finish>key.finish){copy[j]=copy[j-1];ids[j]=ids[j-1];j--;}
        copy[j]=key;ids[j]=id;}
    size_t used=0;int finish=INT_MIN;
    for(size_t i=0;i<n;i++)if(copy[i].start>=finish){selected[used++]=ids[i];finish=copy[i].finish;}
    free(copy);free(ids);return used;
}
int greedy_dijkstra(const int *g,size_t n,size_t source,long long *d,int *parent){
    if(!g||!d||!parent||!n||source>=n)return 0;
    unsigned char *done=calloc(n,1);if(!done)return 0;
    for(size_t i=0;i<n;i++){d[i]=LLONG_MAX;parent[i]=-1;}d[source]=0;
    for(size_t step=0;step<n;step++){
        size_t u=n;long long best=LLONG_MAX;
        for(size_t i=0;i<n;i++)if(!done[i]&&d[i]<best){best=d[i];u=i;}
        if(u==n)break;done[u]=1;
        for(size_t v=0;v<n;v++){int w=g[u*n+v];if(w<0){free(done);return 0;}
            if(w&&!done[v]&&d[u]<=LLONG_MAX-w&&d[u]+w<d[v]){d[v]=d[u]+w;parent[v]=(int)u;}}
    }
    free(done);return 1;
}

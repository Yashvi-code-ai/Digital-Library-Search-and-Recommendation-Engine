#include "flow_matching.h"
#include <limits.h>
#include <stdlib.h>
int flow_ford_fulkerson(const int *cap,size_t n,size_t source,size_t sink,long long *out){
    if(!cap||!out||n<2||n>100||source>=n||sink>=n||source==sink)return 0;
    int *res=malloc(n*n*sizeof(*res)),*parent=malloc(n*sizeof(*parent)),*queue=malloc(n*sizeof(*queue));
    if(!res||!parent||!queue){free(res);free(parent);free(queue);return 0;}
    for(size_t i=0;i<n*n;i++){if(cap[i]<0){free(res);free(parent);free(queue);return 0;}res[i]=cap[i];}
    long long flow=0;
    for(;;){
        for(size_t i=0;i<n;i++)parent[i]=-1;
        size_t head=0,tail=0;queue[tail++]=(int)source;parent[source]=(int)source;
        while(head<tail&&parent[sink]<0){
            size_t u=(size_t)queue[head++];
            for(size_t v=0;v<n;v++)if(parent[v]<0&&res[u*n+v]>0){parent[v]=(int)u;queue[tail++]=(int)v;}
        }
        if(parent[sink]<0)break;
        int add=INT_MAX;
        for(size_t v=sink;v!=source;v=(size_t)parent[v])if(res[(size_t)parent[v]*n+v]<add)add=res[(size_t)parent[v]*n+v];
        for(size_t v=sink;v!=source;v=(size_t)parent[v]){
            size_t u=(size_t)parent[v];res[u*n+v]-=add;
            if(res[v*n+u]>INT_MAX-add){free(res);free(parent);free(queue);return 0;}
            res[v*n+u]+=add;
        }
        flow+=add;
    }
    *out=flow;free(res);free(parent);free(queue);return 1;
}

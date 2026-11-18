#include "flow_matching.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int flow_ford_fulkerson(const int *cap,size_t n,size_t source,size_t sink,long long *out){
 if(!cap||!out||n<2||source>=n||sink>=n||source==sink||n>100)return 0;
 size_t cells=n*n;int *res=malloc(cells*sizeof(*res)),*parent=malloc(n*sizeof(*parent)),*queue=malloc(n*sizeof(*queue));
 if(!res||!parent||!queue){free(res);free(parent);free(queue);return 0;}
 for(size_t i=0;i<cells;i++){if(cap[i]<0){free(res);free(parent);free(queue);return 0;}res[i]=cap[i];}
 long long total=0;
 for(;;){for(size_t i=0;i<n;i++)parent[i]=-1;size_t head=0,tail=0;queue[tail++]=(int)source;parent[source]=(int)source;
 while(head<tail&&parent[sink]==-1){int u=queue[head++];for(size_t v=0;v<n;v++)if(parent[v]==-1&&res[(size_t)u*n+v]>0){parent[v]=u;queue[tail++]=(int)v;}}
 if(parent[sink]==-1)break;int add=INT_MAX;for(size_t v=sink;v!=source;v=(size_t)parent[v])if(res[(size_t)parent[v]*n+v]<add)add=res[(size_t)parent[v]*n+v];
 for(size_t v=sink;v!=source;v=(size_t)parent[v]){size_t u=(size_t)parent[v];res[u*n+v]-=add;if(res[v*n+u]>INT_MAX-add){free(res);free(parent);free(queue);return 0;}res[v*n+u]+=add;}total+=add;
 }
 *out=total;free(res);free(parent);free(queue);return 1;
}
static int augment(size_t u,const int*a,size_t right_n,int*rm,int*seen){for(size_t v=0;v<right_n;v++)if(a[u*right_n+v]&&!seen[v]){seen[v]=1;if(rm[v]<0||augment((size_t)rm[v],a,right_n,rm,seen)){rm[v]=(int)u;return 1;}}return 0;}
int flow_bipartite_matching(const int*a,size_t left_n,size_t right_n,int*lm,int*rm,size_t*out){if(!a||!lm||!rm||!out||!left_n||!right_n||left_n>100||right_n>100)return 0;int*seen=malloc(right_n*sizeof(*seen));if(!seen)return 0;for(size_t v=0;v<right_n;v++)rm[v]=-1;for(size_t u=0;u<left_n;u++){lm[u]=-1;for(size_t v=0;v<right_n;v++)if(a[u*right_n+v]!=0&&a[u*right_n+v]!=1){free(seen);return 0;}}
 size_t count=0;for(size_t u=0;u<left_n;u++){memset(seen,0,right_n*sizeof(*seen));if(augment(u,a,right_n,rm,seen))count++;}for(size_t v=0;v<right_n;v++)if(rm[v]>=0)lm[rm[v]]=(int)v;*out=count;free(seen);return 1;}

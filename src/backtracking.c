#include "backtracking.h"
#include <stdlib.h>
static int safe(const int *q,int row,int col){
    for(int r=0;r<row;r++)if(q[r]==col||abs(q[r]-col)==row-r)return 0;
    return 1;
}
static void queens(int n,int row,int *q,long long *count){
    if(row==n){(*count)++;return;}
    for(int col=0;col<n;col++)if(safe(q,row,col)){q[row]=col;queens(n,row+1,q,count);}
}
long long bt_nqueens_count(int n){
    if(n<1||n>14)return -1;
    int *q=malloc((size_t)n*sizeof(*q));if(!q)return -1;
    long long count=0;queens(n,0,q,&count);free(q);return count;
}
static int subset(const int *a,size_t n,size_t i,int target){
    if(target==0)return 1;if(i==n||target<0)return 0;
    return subset(a,n,i+1,target-a[i])||subset(a,n,i+1,target);
}
int bt_subset_sum(const int *a,size_t n,int target){
    if((n&&!a)||target<0)return 0;
    for(size_t i=0;i<n;i++)if(a[i]<0)return 0;
    return subset(a,n,0,target);
}

#include "divide_conquer.h"
#include <limits.h>
typedef struct { long long sum; size_t first,last; } Segment;
static Segment crossing(const long long *a,size_t l,size_t m,size_t r){
    long long sum=0,left=LLONG_MIN,right=LLONG_MIN;size_t start=m,end=m+1;
    for(size_t i=m+1;i-->l;){sum+=a[i];if(sum>left){left=sum;start=i;}}
    sum=0;for(size_t i=m+1;i<=r;i++){sum+=a[i];if(sum>right){right=sum;end=i;}}
    return (Segment){left+right,start,end};
}
static Segment solve(const long long *a,size_t l,size_t r){
    if(l==r)return (Segment){a[l],l,r};
    size_t m=l+(r-l)/2;Segment x=solve(a,l,m),y=solve(a,m+1,r),z=crossing(a,l,m,r);
    if(x.sum>=y.sum&&x.sum>=z.sum)return x;if(y.sum>=z.sum)return y;return z;
}
int maximum_subarray_divide_conquer(const long long *a,size_t n,MaxSubarrayResult *out){
    if(!a||!out||!n)return 0;Segment s=solve(a,0,n-1);
    out->sum=s.sum;out->start=s.first;out->end=s.last;return 1;
}

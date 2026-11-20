#include "dp.h"
#include <stdlib.h>
int dp_knapsack(const int *w,const int *v,size_t n,int cap,long long *best){
    if(!w||!v||!best||cap<0)return 0;
    long long *dp=calloc((size_t)cap+1,sizeof(*dp));if(!dp)return 0;
    for(size_t i=0;i<n;i++){
        if(w[i]<=0||v[i]<0){free(dp);return 0;}
        for(int c=cap;c>=w[i];c--){long long value=dp[c-w[i]]+v[i];if(value>dp[c])dp[c]=value;}
    }
    *best=dp[cap];free(dp);return 1;
}

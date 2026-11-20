#include "string_number_theory.h"
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
size_t string_match_kmp(const char *text,const char *pattern){
    if(!text||!pattern)return SIZE_MAX;
    size_t n=strlen(text),m=strlen(pattern);if(!m)return 0;if(m>n)return SIZE_MAX;
    size_t *lps=calloc(m,sizeof(*lps));if(!lps)return SIZE_MAX;
    for(size_t i=1,len=0;i<m;){if(pattern[i]==pattern[len])lps[i++]=++len;else if(len)len=lps[len-1];else lps[i++]=0;}
    size_t i=0,j=0,found=SIZE_MAX;
    while(i<n){if(text[i]==pattern[j]){i++;j++;if(j==m){found=i-j;break;}}else if(j)j=lps[j-1];else i++;}
    free(lps);return found;
}
#if defined(__SIZEOF_INT128__)
static long long inverse(long long a,long long m,int *ok){
    __int128 oldr=a,r=m,olds=1,s=0;
    while(r){__int128 q=oldr/r,t=oldr-q*r;oldr=r;r=t;t=olds-q*s;olds=s;s=t;}
    if(oldr!=1){*ok=0;return 0;}olds%=m;if(olds<0)olds+=m;*ok=1;return (long long)olds;
}
#else
static long long inverse(long long a,long long m,int *ok){
    long long t=0,nt=1,r=m,nr=a;
    while(nr){long long q=r/nr,z=t-q*nt;t=nt;nt=z;z=r-q*nr;r=nr;nr=z;}
    if(r!=1){*ok=0;return 0;}*ok=1;t%=m;return t<0?t+m:t;
}
#endif
static long long norm(long long x,long long m){long long r=x%m;return r<0?r+m:r;}
int crt_solve(const long long *r,const long long *m,size_t n,long long *answer){
    if(!r||!m||!answer||!n)return 0;
    long long x=0,product=1;
    for(size_t i=0;i<n;i++){
        if(m[i]<=0||product>LLONG_MAX/m[i])return 0;
        int ok=0;long long inv=inverse(product%m[i],m[i],&ok);if(!ok)return 0;
#if defined(__SIZEOF_INT128__)
        __int128 delta=(__int128)norm(r[i],m[i])-x%m[i];delta%=m[i];if(delta<0)delta+=m[i];
        __int128 factor=delta*inv%m[i],next=(__int128)x+(__int128)product*factor;
        if(next>LLONG_MAX)return 0;x=(long long)next;
#else
        long long delta=norm(r[i],m[i])-x%m[i];if(delta<0)delta+=m[i];
        if(delta&&inv>LLONG_MAX/delta)return 0;long long factor=delta*inv%m[i];
        if(factor&&product>(LLONG_MAX-x)/factor)return 0;x+=product*factor;
#endif
        product*=m[i];
    }
    *answer=x;return 1;
}

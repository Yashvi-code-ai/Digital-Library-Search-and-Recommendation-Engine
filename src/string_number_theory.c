#include "string_number_theory.h"
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

size_t string_match_naive(const char *text, const char *pattern) {
    if (!text || !pattern) return SIZE_MAX;
    size_t n=strlen(text), m=strlen(pattern);
    if (!m) return 0;
    if (m>n) return SIZE_MAX;
    for(size_t i=0;i<=n-m;i++){size_t j=0;while(j<m&&text[i+j]==pattern[j])j++;if(j==m)return i;}
    return SIZE_MAX;
}

size_t string_match_rabin_karp(const char *text, const char *pattern) {
    const uint64_t base=256, mod=1000000007ULL;
    if(!text||!pattern)return SIZE_MAX;
    size_t n=strlen(text),m=strlen(pattern);
    if(!m)return 0;
    if(m>n)return SIZE_MAX;
    uint64_t power=1,ph=0,wh=0;
    for(size_t i=1;i<m;i++)power=(power*base)%mod;
    for(size_t i=0;i<m;i++){ph=(ph*base+(unsigned char)pattern[i])%mod;wh=(wh*base+(unsigned char)text[i])%mod;}
    for(size_t i=0;;i++){
        if(ph==wh&&memcmp(text+i,pattern,m)==0)return i;
        if(i==n-m)break;
        uint64_t lead=((unsigned char)text[i]*power)%mod;
        wh=(wh+mod-lead)%mod;
        wh=(wh*base+(unsigned char)text[i+m])%mod;
    }
    return SIZE_MAX;
}

size_t string_match_automaton(const char *text, const char *pattern) {
    if(!text||!pattern)return SIZE_MAX;
    size_t n=strlen(text),m=strlen(pattern);
    if(!m)return 0;
    if(m>n||m>SIZE_MAX/(256*sizeof(size_t))-1)return SIZE_MAX;
    size_t *table=malloc((m+1)*256*sizeof(size_t));
    if(!table)return SIZE_MAX;
    for(size_t state=0;state<=m;state++)for(size_t ch=0;ch<256;ch++){
        size_t next=0;
        if(state<m&&(unsigned char)pattern[state]==ch)next=state+1;
        else {
            size_t limit=state<m?state:m;
            while(limit>0){
                if((unsigned char)pattern[limit-1]==ch)break;
                limit--;
            }
            if(limit>0){
                size_t prefix=limit-1;
                while(prefix>0&&memcmp(pattern,pattern+state-limit+1,prefix)!=0)prefix--;
                /* The transition is the longest pattern prefix that is a suffix after appending ch. */
                size_t candidate=state<m?state:m;
                while(candidate>0){
                    if((unsigned char)pattern[candidate-1]==ch &&
                       memcmp(pattern, pattern+state-candidate+1, candidate-1)==0)break;
                    candidate--;
                }
                next=candidate;
            }
        }
        table[state*256+ch]=next;
    }
    size_t state=0,answer=SIZE_MAX;
    for(size_t i=0;i<n;i++){state=table[state*256+(unsigned char)text[i]];if(state==m){answer=i+1-m;break;}}
    free(table);
    return answer;
}

size_t string_match_kmp(const char *text,const char *pattern){
    if(!text||!pattern)return SIZE_MAX;
    size_t n=strlen(text),m=strlen(pattern);
    if(!m)return 0;
    if(m>n||m>SIZE_MAX/sizeof(size_t))return SIZE_MAX;
    size_t *lps=calloc(m,sizeof(size_t));if(!lps)return SIZE_MAX;
    for(size_t i=1,len=0;i<m;){if(pattern[i]==pattern[len])lps[i++]=++len;else if(len)len=lps[len-1];else lps[i++]=0;}
    size_t i=0,j=0,answer=SIZE_MAX;
    while(i<n){if(text[i]==pattern[j]){i++;j++;}if(j==m){answer=i-j;break;}if(i<n&&text[i]!=pattern[j]){if(j)j=lps[j-1];else i++;}}
    free(lps);return answer;
}

#if defined(__SIZEOF_INT128__)
static long long norm_mod(long long x,long long m){long long r=x%m;return r<0?r+m:r;}
static long long inverse_mod(long long a,long long m,int *ok){
    __int128 oldr=a,r=m,olds=1,s=0;
    while(r){__int128 q=oldr/r,t=oldr-q*r;oldr=r;r=t;t=olds-q*s;olds=s;s=t;}
    if(oldr!=1){*ok=0;return 0;}olds%=m;if(olds<0)olds+=m;*ok=1;return (long long)olds;
}
#else
static long long norm_mod(long long x,long long m){long long r=x%m;return r<0?r+m:r;}
static long long inverse_mod(long long a,long long m,int *ok){
    long long t=0,nt=1,r=m,nr=a;
    while(nr){long long q=r/nr,z=t-q*nt;t=nt;nt=z;z=r-q*nr;r=nr;nr=z;}
    if(r!=1){*ok=0;return 0;}*ok=1;return norm_mod(t,m);
}
#endif
int crt_solve(const long long *residues,const long long *moduli,size_t count,long long *result){
    if(!residues||!moduli||!result||!count)return 0;
    long long x=0,product=1;
    for(size_t i=0;i<count;i++){
        long long mod=moduli[i];if(mod<=0||product>LLONG_MAX/mod)return 0;
        int ok=0;long long inv=inverse_mod(product%mod,mod,&ok);if(!ok)return 0;
#if defined(__SIZEOF_INT128__)
        __int128 delta=(__int128)norm_mod(residues[i],mod)-(x%mod);delta%=mod;if(delta<0)delta+=mod;
        __int128 factor=(delta*inv)%mod,combined=(__int128)x+(__int128)product*factor;
        if(combined>LLONG_MAX)return 0;x=(long long)combined;
#else
        long long delta=norm_mod(residues[i],mod)-x%mod;if(delta<0)delta+=mod;
        if(delta&&inv>LLONG_MAX/delta)return 0;long long factor=(delta*inv)%mod;
        if(factor&&product>(LLONG_MAX-x)/factor)return 0;x+=product*factor;
#endif
        product*=mod;
    }
    *result=x;return 1;
}

#include "string_number_theory.h"
#include <assert.h>
#include <limits.h>
#include <stdio.h>
static void test_strings(void){
 const char *t="ABABDABACDABABCABAB",*p="ABABCABAB";
 assert(string_match_naive(t,p)==10);assert(string_match_rabin_karp(t,p)==10);
 assert(string_match_automaton(t,p)==10);assert(string_match_kmp(t,p)==10);
 assert(string_match_naive("aaaaa","b")==SIZE_MAX);
 assert(string_match_rabin_karp("aaaaa","aaa")==0);
 assert(string_match_automaton("abc","")==0);
 assert(string_match_kmp("short","longer")==SIZE_MAX);
 assert(string_match_kmp("mississippi","issip")==4);
 assert(string_match_automaton("ababaca","abaca")==2);
}
static void test_crt(void){
 long long r[]={2,3,2},m[]={3,5,7},x=-1;
 assert(crt_solve(r,m,3,&x)&&x==23);
 long long rn[]={-1,2},mn[]={3,5};assert(crt_solve(rn,mn,2,&x)&&x==14);
 long long mb[]={4,6};assert(!crt_solve(r,mb,2,&x));
 long long mo[]={LLONG_MAX,2},ro[]={0,0};assert(!crt_solve(ro,mo,2,&x));
}
int main(void){test_strings();test_crt();puts("Phase 8 tests passed.");return 0;}

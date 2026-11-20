#ifndef STRING_NUMBER_THEORY_H
#define STRING_NUMBER_THEORY_H
#include <stddef.h>
size_t string_match_kmp(const char *text,const char *pattern);
int crt_solve(const long long *residues,const long long *moduli,size_t count,long long *result);
#endif

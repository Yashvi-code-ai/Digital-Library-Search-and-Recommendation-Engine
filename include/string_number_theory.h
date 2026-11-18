#ifndef STRING_NUMBER_THEORY_H
#define STRING_NUMBER_THEORY_H
#include <stddef.h>
#include <stdint.h>
size_t string_match_naive(const char *text, const char *pattern);
size_t string_match_rabin_karp(const char *text, const char *pattern);
size_t string_match_automaton(const char *text, const char *pattern);
size_t string_match_kmp(const char *text, const char *pattern);
/* Pairwise-coprime positive moduli; returns 1 on success, 0 on invalid input/non-coprime/overflow. */
int crt_solve(const long long *residues, const long long *moduli, size_t count, long long *result);
#endif

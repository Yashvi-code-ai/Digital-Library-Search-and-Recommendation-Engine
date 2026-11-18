# Phase 8: String Matching and Chinese Remainder Theorem

## String matching workflow

Choose Phase 8, select one of the four methods, enter the text, then enter the pattern. The program reports the first match using a zero-based index, or reports that no match exists. An empty pattern matches at index 0.

| Algorithm | Main idea | Time complexity | Extra space |
|---|---|---:|---:|
| Naive | Try each possible starting position | O(nm) worst case | O(1) |
| Rabin-Karp | Rolling hash, then verify characters | O(n+m) expected; O(nm) worst case | O(1) |
| Finite automaton | Precompute transitions for each byte and pattern state | O(256m+n) | O(256m) |
| KMP | LPS table skips comparisons already known | O(n+m) | O(m) |

n is text length and m is pattern length. Rabin-Karp verifies a hash match character by character, so collisions cannot create false results. The automaton supports all byte values.

## Chinese Remainder Theorem workflow

Enter the number of equations, then enter each remainder and its positive modulus. The program combines the equations and prints the least non-negative solution. The implementation requires pairwise-coprime moduli and checks invalid inputs and integer overflow.

Example:
- x = 2 (mod 3)
- x = 3 (mod 5)
- x = 2 (mod 7)

The answer is x = 23.

The CRT implementation uses modular inverses from the Extended Euclidean Algorithm. Its time is approximately O(k log M), for k equations and modulus sizes bounded by M.

## Files added

- include/string_number_theory.h — function declarations.
- src/string_number_theory.c — four matching methods and CRT.
- tests/test_string_number_theory.c — standard, missing, empty-pattern, negative-remainder, non-coprime, and overflow tests.
- docs/PHASE8_STRING_MATCHING_CRT.md — workflow and complexity.

## Build and test

Run make, then make test, then ./digital_library. On Windows, use the MinGW commands in the main README.

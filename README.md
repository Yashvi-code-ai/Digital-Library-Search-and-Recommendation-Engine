# Digital Library Search and Recommendation Engine

A compact C17 command-line digital library and Design and Analysis of Algorithms project.

## Library features

- Add, list, search, update and delete books.
- Store records in a dynamically growing array.
- Load and save book records as CSV.

## Core algorithms retained

| DAA topic | Retained algorithms |
|---|---|
| Searching | Linear Search, Binary Search |
| Sorting | Merge Sort |
| Divide and conquer | Maximum Subarray |
| Greedy | Activity Selection, Dijkstra |
| Dynamic programming | 0/1 Knapsack |
| Backtracking | N-Queens, Subset Sum |
| Graph algorithms | Ford-Fulkerson with BFS augmenting paths (Edmonds-Karp method) |
| String matching | Knuth-Morris-Pratt (KMP) |
| Number theory | Chinese Remainder Theorem (using Extended Euclidean Algorithm for modular inverses) |
| Complexity theory | P, NP, NP-complete, NP-hard, and Independent Set to Vertex Cover reduction |

This focused selection keeps one or two clear examples from each major DAA design technique. Extra algorithms and duplicate variants such as multiple sorting methods, additional shortest-path/MST methods, extra string matchers, and advanced DP/backtracking variants are not part of this compact version.

## Project size

The current implementation contains approximately **703 physical lines** across the `src/*.c` and `include/*.h` files. This count excludes tests, documentation, the Makefile, and the CSV dataset. The test program is kept separately in `tests/test_core.c`.

The aim is readable, explainable implementations—not artificially shortened or minified code.

## Build and run

Using GCC and Make:

```bash
make
make run
```

Windows PowerShell:

```powershell
gcc -std=c17 -Wall -Wextra -Wpedantic -Iinclude src/main.c src/book.c src/library.c src/searching.c src/sorting.c src/divide_conquer.c src/greedy.c src/dp.c src/backtracking.c src/flow_matching.c src/string_number_theory.c src/analysis.c -o digital_library.exe
.\\digital_library.exe
```

Run the program from the repository root so it can find `data/books.csv`.

## Run tests

```bash
make test
```

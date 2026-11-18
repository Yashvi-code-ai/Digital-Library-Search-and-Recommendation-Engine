# Digital Library Search and Recommendation Engine

A beginner-friendly **C17 command-line digital library** built incrementally for a Design and Analysis of Algorithms (DAA) project.

## Completed phases

### Phase 1: Library foundation

- Book records with ID, title, author, category, keywords, citations, and popularity.
- Add, list, search, update, and delete operations.
- Dynamically growing array storage.
- Case-insensitive contains-text title search.
- CSV loading at startup and saving on demand/exit.

### Phase 2: Searching and sorting

- Linear Search (exact, case-insensitive title).
- Iterative Binary Search.
- Recursive Binary Search.
- Merge Sort.
- Quick Sort.
- Binary Search checks the sorted-input requirement and automatically runs Merge Sort if needed.
- Sorts complete Book records, preserving all book details.

### Phase 3: Divide and conquer

- Maximum Subarray using divide-and-conquer; reports the sum and zero-based range.
- Fast Powering using binary exponentiation, with overflow detection.
- Celebrity Problem using recursive candidate elimination and final verification.
- Classical square matrix multiplication.
- Strassen square matrix multiplication; pads non-power-of-two dimensions internally.
- A separate Phase 3 menu and dedicated unit tests.

### Phase 4: Greedy algorithms

- Activity Selection and Interval Partitioning for scheduling.
- Huffman Coding for prefix-free compression codes.
- Dijkstra shortest paths for non-negative weighted graphs.
- Prim and Kruskal minimum spanning trees.
- Fractional Knapsack using value-to-weight ratios.
- Separate Phase 4 menu, documentation, and unit tests.

### Phase 5: Dynamic Programming\n\n- 0/1 Knapsack, Matrix Chain Multiplication, LCS, and Optimal BST.\n- Bellman-Ford and Floyd-Warshall shortest-path algorithms.\n- Exact bounded Traveling Salesperson Problem using Held-Karp DP.\n- Dedicated CLI menu, tests, and documentation.\n\n## Repository layout

```text
Digital-Library-Search-and-Recommendation-Engine/
├── include/
│   ├── book.h
│   ├── library.h
│   ├── algorithms.h
│   ├── divide_conquer.h
│   ├── greedy.h\n│   └── dp.h
├── src/
│   ├── main.c
│   ├── book.c
│   ├── library.c
│   ├── searching.c
│   ├── sorting.c
│   ├── divide_conquer.c
│   ├── greedy.c\n│   └── dp.c
├── data/
│   └── books.csv
├── tests/
│   ├── test_library.c
│   ├── test_search_sort.c
│   ├── test_divide_conquer.c
│   ├── test_greedy.c\n│   └── test_dp.c
├── docs/
│   ├── PHASE1_WORKFLOW.md
│   ├── PHASE2_SEARCH_SORT.md
│   ├── PHASE3_DIVIDE_CONQUER.md
│   ├── PHASE4_GREEDY.md\n│   └── PHASE5_DP.md
└── Makefile
```

## Build and run

From the repository root:

```bash
make
./digital_library
```

On Windows with MinGW:

```bash
mingw32-make
digital_library.exe
```

Run all available tests:

```bash
make test
```

The app reads and writes `data/books.csv`. Run it from the repository root so this relative path resolves correctly.

## Phase 5 menu\n\nChoose option **10** to access the Dynamic Programming algorithms. Read [Phase 5 documentation](docs/PHASE5_DP.md).\n\n## Phase 4 menu

Choose option **9** from the main menu to access Activity Selection, Interval Partitioning, Huffman Coding, Dijkstra, Prim, Kruskal, and Fractional Knapsack. See [Phase 4 greedy workflow](docs/PHASE4_GREEDY.md).

## Phase 3 menu

Choose option **8** from the main menu:

1. Maximum Subarray
2. Fast Powering
3. Celebrity Problem
4. Classical Matrix Multiplication
5. Strassen Matrix Multiplication (the app displays both results for comparison)
0. Return to main menu

See [Phase 1 workflow](docs/PHASE1_WORKFLOW.md), [Phase 2 searching and sorting workflow](docs/PHASE2_SEARCH_SORT.md), and [Phase 3 divide-and-conquer workflow](docs/PHASE3_DIVIDE_CONQUER.md).

## Planned next phases

Backtracking and branch-and-bound, graph/flow algorithms, string matching, CRT, expanded benchmarks, and complexity analysis will be added in separate modules.


## Phase 6: Backtracking and Branch-and-Bound

Choose option **11** in the main menu for N-Queens, Subset Sum, 0/1 Knapsack backtracking, and Knapsack Branch-and-Bound using LIFO, FIFO, or least-cost/best-bound node selection. See [Phase 6 documentation](docs/PHASE6_BACKTRACKING.md).


## Phase 7: Flow and Matching Algorithms

Choose option **12** for Ford-Fulkerson maximum flow (BFS augmenting paths / Edmonds-Karp) and maximum bipartite matching. See [Phase 7 documentation](docs/PHASE7_FLOW_MATCHING.md).


## Phase 8: String Matching and CRT

Choose option **13** from the main menu. This phase provides Naive, Rabin-Karp, finite-automaton, and KMP string matching, plus the Chinese Remainder Theorem for systems with pairwise-coprime moduli. See [Phase 8 workflow and complexity](docs/PHASE8_STRING_MATCHING_CRT.md).

The common `make test` command now also runs the Phase 8 test suite.

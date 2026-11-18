# Digital Library Search and Recommendation Engine

A beginner-friendly **C17 command-line digital library and algorithm toolkit** developed for a Design and Analysis of Algorithms (DAA) project.

## Features

### Library management
- Book records with ID, title, author, category, keywords, citations, and popularity.
- Add, list, search, update, and delete operations.
- Dynamically growing array storage.
- Case-insensitive title search.
- CSV loading at startup and saving on demand/exit.

### Searching and sorting
- Linear search, iterative binary search, and recursive binary search.
- Merge sort and quick sort.
- Binary search checks whether titles are sorted and runs merge sort when needed.

### Divide-and-conquer algorithms
- Maximum Subarray, fast powering, and Celebrity Problem.
- Classical and Strassen matrix multiplication.

### Greedy algorithms
- Activity Selection and Interval Partitioning.
- Huffman Coding.
- Dijkstra shortest paths, Prim and Kruskal minimum spanning trees.
- Fractional Knapsack.

### Dynamic programming
- 0/1 Knapsack, Matrix Chain Multiplication, LCS, and Optimal BST.
- Bellman-Ford and Floyd-Warshall shortest paths.
- Bounded Traveling Salesperson Problem using Held-Karp DP.

### Backtracking and branch-and-bound
- N-Queens, Subset Sum, and 0/1 Knapsack backtracking.
- Knapsack branch-and-bound with LIFO, FIFO, and least-cost/best-bound strategies.

### Flow and matching
- Ford-Fulkerson maximum flow using BFS augmenting paths (Edmonds-Karp).
- Maximum bipartite matching.

### String matching and number theory
- Naive, Rabin-Karp, finite-automaton, and KMP string matching.
- Chinese Remainder Theorem for pairwise-coprime moduli.

### Complexity theory and benchmarking
- Explanations of P, NP, NP-complete, and NP-hard.
- Independent Set to Vertex Cover polynomial-time reduction.
- Naive versus KMP string-matching benchmark with comparison counts, CPU time, and CSV output.

## Repository layout

```text
include/   Header files and public function declarations
src/       C implementations and command-line interface
data/      Sample book data and benchmark output
tests/     Unit test programs
docs/      Feature and algorithm documentation
Makefile   Build, test, run, and clean commands
```

## Build and run

Run these commands from the repository root:

```bash
make
make run
```

On Windows, if GNU Make is unavailable, compile directly with GCC:

```powershell
gcc -std=c17 -Wall -Wextra -Wpedantic -Iinclude src/main.c src/book.c src/library.c src/searching.c src/sorting.c src/divide_conquer.c src/greedy.c src/dp.c src/backtracking.c src/flow_matching.c src/string_number_theory.c src/analysis.c -o digital_library.exe
.\digital_library.exe
```

Run all unit tests:

```bash
make test
```

Remove generated executables:

```bash
make clean
```

The application reads and writes `data/books.csv`. Run it from the repository root so this relative path resolves correctly.

## Main menu

- Option 7: Searching and Sorting
- Option 8: Divide and Conquer
- Option 9: Greedy Algorithms
- Option 10: Dynamic Programming
- Option 11: Backtracking and Branch-and-Bound
- Option 12: Flow and Matching
- Option 13: String Matching and CRT
- Option 14: Complexity Theory and Benchmarking

## Documentation

- [Library management workflow](docs/LIBRARY_WORKFLOW.md)
- [Searching and sorting](docs/SEARCHING_AND_SORTING.md)
- [Divide and conquer](docs/DIVIDE_AND_CONQUER.md)
- [Greedy algorithms](docs/GREEDY_ALGORITHMS.md)
- [Dynamic programming](docs/DYNAMIC_PROGRAMMING.md)
- [Backtracking and branch-and-bound](docs/BACKTRACKING_AND_BRANCH_BOUND.md)
- [Flow and matching](docs/FLOW_AND_MATCHING.md)
- [String matching and CRT](docs/STRING_MATCHING_AND_CRT.md)
- [Complexity theory and benchmarking](docs/COMPLEXITY_AND_BENCHMARKING.md)

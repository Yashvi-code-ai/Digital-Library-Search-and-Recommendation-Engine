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

## Repository layout

```text
Digital-Library-Search-and-Recommendation-Engine/
├── include/
│   ├── book.h
│   ├── library.h
│   └── algorithms.h
├── src/
│   ├── main.c
│   ├── book.c
│   ├── library.c
│   ├── searching.c
│   └── sorting.c
├── data/
│   └── books.csv
├── tests/
│   ├── test_library.c
│   └── test_search_sort.c
├── docs/
│   ├── PHASE1_WORKFLOW.md
│   └── PHASE2_SEARCH_SORT.md
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

## Phase 2 menu

Choose option **7** from the main menu:

1. Linear Search (exact title)
2. Iterative Binary Search
3. Recursive Binary Search
4. Merge Sort
5. Quick Sort
6. Display current book order
0. Return to main menu

See [Phase 1 workflow](docs/PHASE1_WORKFLOW.md) and [Phase 2 searching and sorting workflow](docs/PHASE2_SEARCH_SORT.md).

## Planned next phases

Divide-and-conquer, greedy methods, dynamic programming, backtracking and branch-and-bound, graph/flow algorithms, string matching, CRT, expanded tests, and benchmarking will be added in separate modules.

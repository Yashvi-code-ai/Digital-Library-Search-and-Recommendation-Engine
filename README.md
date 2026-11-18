# Digital Library Search and Recommendation Engine

A beginner-friendly **C17 command-line digital library** built incrementally for a Design and Analysis of Algorithms (DAA) project.

## Phase 1: working library foundation

- Book records with ID, title, author, category, keywords, citations, and popularity.
- Add, list, search by title, update, and delete operations.
- Dynamically growing array storage.
- Case-insensitive linear title search.
- CSV loading at startup and saving on demand/exit.
- Input validation and duplicate-ID protection.

## Repository layout

```text
Digital-Library-Search-and-Recommendation-Engine/
├── include/
│   ├── book.h
│   └── library.h
├── src/
│   ├── book.c
│   ├── library.c
│   └── main.c
├── data/
│   └── books.csv
├── docs/
│   └── PHASE1_WORKFLOW.md
├── Makefile
└── README.md
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

The app reads and writes `data/books.csv`. Run it from the repository root so this relative path resolves correctly.

## Menu

1. Add a book
2. List all books
3. Search books by title
4. Update a book
5. Delete a book
6. Save library
0. Save and exit

See [Phase 1 workflow and complexity notes](docs/PHASE1_WORKFLOW.md).

## Planned next phases

Searching/sorting algorithms, divide-and-conquer, greedy methods, dynamic programming, backtracking and branch-and-bound, graph/flow algorithms, string matching, CRT, tests, and benchmarking will be added in separate modules.

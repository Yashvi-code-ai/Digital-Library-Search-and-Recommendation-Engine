# Digital Library Search and Recommendation Engine

A beginner-friendly C17 command-line project that combines a working digital library with selected Design and Analysis of Algorithms (DAA) implementations.

## Library features

- Add, view, search, update and delete book records.
- Store books in a dynamically growing array.
- Load and save the library using a CSV file.
- Search book titles and sort the library alphabetically.

## Algorithms retained

The project keeps **10 algorithms** that demonstrate the main DAA techniques without making the application unnecessarily difficult to understand.

| DAA topic | Algorithms |
|---|---|
| Searching | Linear Search, Binary Search |
| Sorting | Merge Sort |
| Divide and Conquer | Maximum Subarray |
| Greedy | Activity Selection, Dijkstra's Shortest Path |
| Dynamic Programming | 0/1 Knapsack |
| Backtracking | N-Queens, Subset Sum |
| String Matching | Knuth-Morris-Pratt (KMP) |

## What was left out and why

The extra implementations for maximum flow, Chinese Remainder Theorem, and the Independent Set-to-Vertex Cover reduction have been removed from the application. They are useful topics, but they add separate concepts and code that are not essential to demonstrate the main DAA techniques in this library project.

Other advanced or overlapping variants—such as multiple sorting methods, additional shortest-path and minimum-spanning-tree algorithms, extra string matchers, and larger dynamic-programming problems—are also intentionally not included.

**Important:** This is a focused selection, not a claim that the removed algorithms are unimportant. If your instructor's written requirements explicitly name any of them, they should be restored.

## How the application is organized

1. The main menu handles library operations.
2. The DAA Algorithms menu contains the algorithm demonstrations.
3. Book records are stored in `data/books.csv`.
4. Algorithm tests are kept separately in `tests/test_core.c`.

## Build and run

Using GCC and Make:

```bash
make
make run
```

Windows PowerShell:

```powershell
gcc -std=c17 -Wall -Wextra -Wpedantic -Iinclude src/main.c src/book.c src/library.c src/searching.c src/sorting.c src/divide_conquer.c src/greedy.c src/dp.c src/backtracking.c src/string_number_theory.c -o digital_library.exe
.\digital_library.exe
```

Run the program from the repository root so it can find `data/books.csv`.

## Run tests

```bash
make test
```

The tests cover the retained algorithms with small example inputs.

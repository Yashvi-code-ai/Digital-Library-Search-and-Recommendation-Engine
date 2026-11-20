# Digital Library Search and Recommendation Engine

A beginner-friendly C17 command-line digital library project with five selected Design and Analysis of Algorithms (DAA) demonstrations.

## Library features

- Add, list, search, update and delete book records.
- Store books in a dynamically growing array.
- Load and save records using `data/books.csv`.
- Search within titles and sort the library alphabetically.

## Five DAA algorithms

| DAA area | Algorithm | What it does | Time complexity |
|---|---|---|---|
| Searching | Linear Search | Checks book titles one by one. | O(n) |
| Sorting / Divide and Conquer | Merge Sort | Splits the book list, sorts each half and merges them. | O(n log n) |
| Greedy | Activity Selection | Selects the largest compatible set of activities. | O(n²) in this implementation |
| Dynamic Programming | 0/1 Knapsack | Finds the maximum value that fits within a capacity. | O(nW) |
| Backtracking | N-Queens | Counts valid ways to place N queens without attacks. | Exponential |

Here, `n` is the number of books or activities and `W` is the knapsack capacity.

## Why these five?

The selected algorithms cover five useful DAA ideas while keeping the project manageable to build, demonstrate and explain:

- Linear Search demonstrates a basic search.
- Merge Sort demonstrates sorting and divide-and-conquer.
- Activity Selection demonstrates a greedy choice.
- 0/1 Knapsack demonstrates dynamic programming.
- N-Queens demonstrates backtracking.

Binary Search, Maximum Subarray, Dijkstra, Subset Sum and KMP were removed from the active project to reduce the number of concepts and input workflows.

## Application workflow

1. The program starts and loads books from `data/books.csv`.
2. The main menu provides book management, title search, sorting and saving.
3. The DAA Algorithms menu provides the five demonstrations listed above.
4. The program saves the library on request and automatically on exit.
5. Dynamically allocated memory is freed before the program closes.

## Build and run

Using GCC and Make:

```bash
make
make run
```

Windows PowerShell with MinGW GCC:

```powershell
gcc -std=c17 -Wall -Wextra -Wpedantic -Iinclude src/main.c src/book.c src/library.c src/searching.c src/sorting.c src/greedy.c src/dp.c src/backtracking.c -o digital_library.exe
.\digital_library.exe
```

Run the executable from the repository root so it can find `data/books.csv`.

## Run tests

```bash
make test
```

The test suite checks all five DAA algorithms and the separate library storage workflow.

## Scope note

The current application manages and searches a digital library and demonstrates five DAA algorithms. It does not yet generate personalized book recommendations from a reader's preferences or history; that can be added as a future feature.

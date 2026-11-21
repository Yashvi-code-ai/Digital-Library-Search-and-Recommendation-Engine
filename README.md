# Digital Library Search and Recommendation Engine

A beginner-friendly C17 command-line digital library project with five selected Design and Analysis of Algorithms (DAA) demonstrations and a simple category-based book recommendation feature.

## Library features

- Add, list, search, update and delete book records.
- Store books in a dynamically growing array.
- Load and save records using `data/books.csv`.
- Search within titles and sort the library alphabetically.
- Recommend books by matching the reader's preferred category with book categories in the library (case-insensitive).

## Five DAA algorithms

| DAA area | Algorithm | What it does | Time complexity |
|---|---|---|---|
| Searching | Linear Search | Checks book titles one by one. | O(n) |
| Sorting / Divide and Conquer | Merge Sort | Splits the book list, sorts each half and merges them. | O(n log n) |
| Greedy | Activity Selection | Selects the largest compatible set of activities. | O(n²) in this implementation |
| Dynamic Programming | 0/1 Knapsack | Finds the maximum value that fits within a capacity. | O(nW) |
| Backtracking | N-Queens | Counts valid ways to place N queens without attacks. | Exponential |

Here, `n` is the number of books or activities and `W` is the knapsack capacity.

## Simple recommendation feature

The user chooses a preferred category, such as `Programming` or `Computer Science`. The program scans the stored books and displays books whose category matches the selected category, ignoring uppercase/lowercase differences. This is a basic category-based recommendation method; it does not learn from user accounts, ratings or reading history.

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
2. The main menu provides book management, title search, sorting, category-based recommendations and saving.
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

The test suite checks all five DAA algorithms, the category recommendation feature and the library storage workflow.

## Scope note

The application includes a basic category-based recommendation feature. More advanced personalized recommendations based on user preferences, ratings or reading history can be future improvements.

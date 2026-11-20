# Digital Library Search and Recommendation Engine

A compact C17 command-line digital library and DAA project.

## Library features
- Add, list, search, update and delete books.
- Store records in a dynamically growing array.
- Load and save book records as CSV.

## Core algorithms retained

| DAA topic | Algorithms |
|---|---|
| Searching and sorting | Linear Search, Binary Search, Merge Sort |
| Divide and conquer | Maximum Subarray |
| Greedy | Activity Selection, Dijkstra |
| Dynamic programming | 0/1 Knapsack |
| Backtracking | N-Queens, Subset Sum |
| Graph algorithms | Ford-Fulkerson maximum flow using BFS augmenting paths |
| String matching | Knuth-Morris-Pratt (KMP) |
| Number theory | Chinese Remainder Theorem with Extended Euclidean Algorithm |
| Complexity theory | P, NP, NP-complete, NP-hard and Independent Set to Vertex Cover reduction |

Extra algorithms and duplicate variants have been removed to make the implementation shorter and easier to explain. The retained algorithms still demonstrate the major DAA design techniques.

## Build and run

Using GCC and Make:
```bash
make
make run
```

Windows PowerShell:
```powershell
gcc -std=c17 -Wall -Wextra -Wpedantic -Iinclude src/main.c src/book.c src/library.c src/searching.c src/sorting.c src/divide_conquer.c src/greedy.c src/dp.c src/backtracking.c src/flow_matching.c src/string_number_theory.c src/analysis.c -o digital_library.exe
.\digital_library.exe
```

Run the program from the repository root so it can find `data/books.csv`.

# Searching and sorting: Searching and Sorting

## Goal

Searching and sorting adds the core searching and sorting algorithms to the Library management library. The algorithms operate directly on the existing dynamic array of `Book` records and compare titles without case sensitivity.

## Algorithms implemented

### Searching

- **Linear Search:** checks titles one by one and returns the matching array index. It works even when the books are not sorted.
- **Iterative Binary Search:** repeatedly halves the search range using a loop. The array must already be sorted by title.
- **Recursive Binary Search:** performs the same range-halving process through recursive function calls. The array must already be sorted by title.

All three Searching and sorting search functions look for an exact complete title, ignoring uppercase/lowercase differences. The Library management menu's contains-text title search remains available separately.

### Sorting

- **Merge Sort:** divides the array into two halves, sorts each half, and merges them. It is stable and uses an additional temporary array.
- **Quick Sort:** partitions the array around a middle-element title pivot and recursively sorts the two partitions. It sorts the Book records in place.

Sorting moves complete `Book` structures, so IDs, authors, categories, keywords, citation counts, and popularity scores stay attached to the correct title.

## Application workflow

1. Start the program. Library management loads the records from `data/books.csv`.
2. Select menu option **7: Searching and sorting Searching and Sorting Algorithms**.
3. Choose Linear Search, Iterative Binary Search, or Recursive Binary Search and enter the complete title.
4. Linear Search scans the current array directly.
5. Before either Binary Search runs, the menu checks whether titles are sorted. If they are not, it runs Merge Sort automatically. This satisfies Binary Search's sorted-input requirement.
6. Choose Merge Sort or Quick Sort to alphabetically reorder the library.
7. Use **Display current book order** to inspect the current order.
8. Return to the main menu and save, or exit; the existing CSV save process stores the current order.

## Complexity analysis

Let `n` be the number of books.

| Algorithm | Best case | Average case | Worst case | Extra space |
|---|---:|---:|---:|---:|
| Linear Search | O(1) | O(n) | O(n) | O(1) |
| Iterative Binary Search | O(1) | O(log n) | O(log n) | O(1) |
| Recursive Binary Search | O(1) | O(log n) | O(log n) | O(log n) call stack |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) | O(n) |
| Quick Sort | O(n log n) | O(n log n) | O(n²) | O(log n) average stack; O(n) worst stack |

Binary Search's time bound assumes the array is already sorted. If sorting is needed first, the total operation also includes the sorting cost. Merge Sort guarantees O(n log n) time. Quick Sort is typically fast, but its worst case is O(n²).

## Build and test

Build the application:

```bash
make
```

Run the application:

```bash
./digital_library
```

Run both Library management and Searching and sorting tests:

```bash
make test
```

The Searching and sorting test checks case-insensitive exact title search, missing titles, merge-sort ordering, quick-sort ordering, and successful binary searches on sorted data.

## Important distinction

The Library management title search supports finding a piece of text inside a title. The new Searching and sorting linear and binary search functions use exact complete-title matching so their search behavior can be compared fairly. Binary Search must never be applied to an unsorted array.

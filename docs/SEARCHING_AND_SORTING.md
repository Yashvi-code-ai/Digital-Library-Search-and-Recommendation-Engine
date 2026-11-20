# Searching and sorting

This project uses two algorithms to work with book titles.

## Linear Search

Linear Search checks each book title from the beginning until it finds an exact match. The comparison ignores uppercase and lowercase differences.

- Works even when books are not sorted.
- Worst-case time: O(n).
- Extra space: O(1).

## Merge Sort

Merge Sort divides the book array into smaller halves, sorts each half, and merges the sorted halves. It moves complete Book records, so each book's ID and other details remain attached to its title.

- Time: O(n log n).
- Extra space: O(n).
- The main menu's Sort Books option uses Merge Sort.

## Application workflow

1. Load books from `data/books.csv`.
2. Choose Search Titles to find text within titles, or use DAA Algorithms -> Linear Search for an exact title.
3. Choose Sort Books or DAA Algorithms -> Merge Sort to sort all book records alphabetically.
4. Save the library or exit; the sorted order is saved to the CSV file.

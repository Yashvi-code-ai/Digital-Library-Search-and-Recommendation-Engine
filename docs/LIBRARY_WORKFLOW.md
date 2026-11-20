# Library management workflow

## Goal
Build a small, usable digital library in C17 with a terminal menu. The DAA demonstrations are kept in separate modules.

## Data model
Each `Book` has an integer ID, title, author, category, keywords, citation count, and popularity score. A `Library` owns a dynamically allocated array of books. The array grows when it becomes full, so the project is not limited to a fixed number of records.

## User workflow
1. On startup, the program loads records from `data/books.csv`.
2. The menu lets the user add, list, search, update, or delete a book.
3. Adding assigns the next available ID and rejects empty titles/authors and duplicate IDs.
4. Title search is a case-insensitive linear scan.
5. Save writes the current records back to the CSV file. Exit also saves automatically.
6. The allocated array is freed before the program exits.

## Algorithms and complexity
- Find ID / duplicate check: linear search, O(n) time.
- Search title: linear scan, O(n * m) worst case for n titles and query length m.
- Add: amortized O(1) array append; O(n) when capacity growth reallocates.
- Update: O(n) to locate the ID, then O(1) replacement.
- Delete: O(n) to locate and shift following records.
- List and CSV save: O(n) records (plus the total number of characters written).
- CSV load: O(n) records (plus parsing cost).

## CSV format
The header is `id,title,author,category,keywords,citations,popularity`. Text fields are quoted and embedded double quotes are escaped by doubling them. Keep the CSV file in `data/books.csv` and run the executable from the repository root.

## Build and run
- Linux/macOS with GCC: `make`, then `./digital_library`.
- Windows with MinGW: `mingw32-make`, then `digital_library.exe`.
- Or compile manually: `gcc -std=c17 -Wall -Wextra -Wpedantic -Iinclude src/main.c src/book.c src/library.c -o digital_library`.

## Scope boundary
Library management includes title sorting through Merge Sort. Personalized recommendations based on reader preferences or reading history, user accounts, and reading histories are outside the current project scope and can be future improvements.

## Basic verification

Run `make test` to compile and execute the small unit test program. It checks insertion, duplicate-ID rejection, ID lookup, update, CSV save/load (including a comma in a title), and deletion. The test removes its temporary CSV file afterwards.

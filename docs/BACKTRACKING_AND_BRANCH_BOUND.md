# Backtracking: N-Queens

The N-Queens problem asks us to place N queens on an N by N chessboard so that no two queens attack each other.

A queen can attack along its row, column and diagonals. The program places one queen in each row and checks whether each position is safe.

## Workflow

1. Enter a board size from 1 to 14.
2. The program tries each column in the current row.
3. If a position is safe, it places a queen and moves to the next row.
4. If no safe position works, it goes back to the previous row and tries another column.
5. It counts and displays all valid arrangements.

This is backtracking because the algorithm builds a possible solution step by step and reverses a choice when it cannot lead to a valid solution.

The search has exponential worst-case time. The implementation limits the board size to 14 to keep the demonstration manageable.

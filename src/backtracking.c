#include "backtracking.h"
#include <stdlib.h>

static int safe(const int *queens, int row, int col) {
    for (int r = 0; r < row; r++) {
        if (queens[r] == col || abs(queens[r] - col) == row - r) return 0;
    }
    return 1;
}

static void place_queens(int n, int row, int *queens, long long *count) {
    if (row == n) {
        (*count)++;
        return;
    }
    for (int col = 0; col < n; col++) {
        if (safe(queens, row, col)) {
            queens[row] = col;
            place_queens(n, row + 1, queens, count);
        }
    }
}

long long bt_nqueens_count(int n) {
    if (n < 1 || n > 14) return -1;
    int *queens = malloc((size_t)n * sizeof(*queens));
    if (!queens) return -1;
    long long count = 0;
    place_queens(n, 0, queens, &count);
    free(queens);
    return count;
}

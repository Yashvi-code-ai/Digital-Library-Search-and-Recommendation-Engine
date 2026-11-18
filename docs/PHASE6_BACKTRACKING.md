# Phase 6: Backtracking and Branch-and-Bound

This phase adds exact search methods for combinatorial problems.

## Workflow

1. **N-Queens:** enter board size (1–14). Recursive backtracking places one queen per row, checks columns and diagonals, and counts complete valid boards.
2. **Subset Sum:** enter nonnegative values and a target. At each position, recursion explores including or excluding the value and stops when a valid sum is found.
3. **0/1 Knapsack Backtracking:** recursively explores exclude/include decisions and returns the best value.
4. **Knapsack Branch-and-Bound:** sorts items by value/weight ratio, computes an optimistic fractional upper bound, and prunes nodes that cannot beat the current best solution. Choose:
   - **LIFO:** stack-based depth-first expansion.
   - **FIFO:** queue-based breadth-first expansion.
   - **Least-cost / best-bound:** expands the live node with the strongest upper bound first.

## Complexity

| Algorithm | Worst-case time | Extra space |
|---|---:|---:|
| N-Queens | O(n!) | O(n) |
| Subset Sum | O(2ⁿ) | O(n) recursion |
| 0/1 Knapsack backtracking | O(2ⁿ) | O(n) recursion |
| Knapsack branch-and-bound | O(2ⁿ) | O(2ⁿ) live nodes |

Branch-and-bound can prune many nodes in practice, but its worst case remains exponential. This implementation limits N-Queens to 14 and knapsack branch-and-bound to 20 items.

## Build and run

```bash
make
make test
./digital_library
```

Choose main menu option 11 for Phase 6.

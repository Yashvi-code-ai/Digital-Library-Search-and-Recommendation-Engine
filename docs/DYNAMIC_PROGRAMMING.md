# Dynamic programming: 0/1 Knapsack

0/1 Knapsack chooses items to maximize total value without exceeding a bag's capacity. Each item can be selected once (1) or not selected (0); items cannot be split.

## Workflow

1. Enter the number of items.
2. Enter each item's weight and value.
3. Enter the bag capacity.
4. The program calculates and prints the maximum achievable value.

The implementation uses a one-dimensional dynamic-programming array. Capacities are processed from high to low for each item, which prevents selecting the same item more than once.

- Time complexity: O(nW).
- Space complexity: O(W).

Here, n is the number of items and W is the bag capacity.

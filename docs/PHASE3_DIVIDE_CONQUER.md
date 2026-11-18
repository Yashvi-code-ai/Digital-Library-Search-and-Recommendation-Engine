# Phase 3: Divide-and-Conquer Workflow

Phase 3 adds a separate menu for divide-and-conquer algorithms. These algorithms solve a problem by splitting it into smaller parts, solving those parts, and combining their results.

## Features and workflow

1. **Maximum Subarray** – enter a sequence of integers. The program divides the sequence into left and right halves, also checks the best subarray crossing the middle, and returns the maximum sum with its starting and ending indices. Indices are zero-based.
2. **Fast Powering** – enter a base and a non-negative exponent. Binary exponentiation repeatedly squares the base and halves the exponent, so it needs O(log n) multiplications. It reports overflow instead of returning an invalid result.
3. **Celebrity Problem** – enter an n-by-n relationship matrix. A value of 1 at row i, column j means person i knows person j. The algorithm recursively eliminates candidates, then verifies that the remaining candidate knows nobody and everybody else knows them. It returns a zero-based index or -1.
4. **Classical Matrix Multiplication** – enter two square matrices of the same dimension and multiply them with the standard three-loop method.
5. **Strassen Matrix Multiplication** – multiply the same kind of square matrices using seven recursive products instead of eight. Non-power-of-two dimensions are padded internally and the displayed result is cropped back to the requested size. Small subproblems use classical multiplication.

## Complexity

| Algorithm | Time complexity | Extra space |
|---|---:|---:|
| Maximum Subarray (divide and conquer) | O(n log n) | O(log n) recursion |
| Fast Powering | O(log exponent) | O(1) |
| Celebrity candidate reduction + verification | O(n) | O(n) recursion |
| Classical n x n matrix multiplication | O(n^3) | O(1) excluding output |
| Strassen matrix multiplication | O(n^log2(7)) ≈ O(n^2.807) | O(n^2) temporary storage, plus recursion |

## Notes and limitations

- Matrix values and intermediate results must fit in the C `long long` type. The program checks allocation and dimension-size failures, but does not perform per-cell arithmetic overflow checking for matrix multiplication.
- Fast Powering checks multiplication overflow and only accepts non-negative exponents.
- The maximum-subarray function requires at least one value.
- The celebrity matrix must contain 0/1 values. The program assumes this input convention.
- The recursive maximum-subarray algorithm is intended to demonstrate divide-and-conquer; its crossing scan makes its total time O(n log n).

## Build and test

```bash
make
make test
./digital_library
```

Choose **8** from the main menu to open Phase 3.

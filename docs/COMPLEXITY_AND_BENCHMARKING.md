# Complexity and benchmarking: Complexity Theory and Benchmarking

## 1. Complexity classes

This module introduces the main complexity classes for decision problems:

- **P:** problems that can be solved in polynomial time by a deterministic algorithm.
- **NP:** problems for which a proposed YES-solution can be verified in polynomial time.
- **NP-complete:** problems that are in NP and are at least as hard as every problem in NP.
- **NP-hard:** problems at least as hard as every problem in NP; they do not have to be in NP or even be decision problems.

Important relationship: every NP-complete problem is both NP and NP-hard. P is contained in NP. Whether P equals NP is an open question.

Examples from this project:
- The decision version of 0/1 Knapsack ("is there a selection with value at least V and weight at most W?") is NP-complete.
- The decision version of TSP ("is there a tour with total cost at most B?") is NP-complete; the optimization version is NP-hard.
- The bounded exact TSP implementation is practical only for small inputs; it does not make the general problem polynomial-time.

## 2. Polynomial-time reduction: Independent Set to Vertex Cover

A reduction transforms an instance of one decision problem into an equivalent instance of another in polynomial time.

For an undirected graph G with n vertices:
- Independent Set asks whether G contains at least k vertices with no edges between them.
- Vertex Cover asks whether G contains at most q vertices touching every edge.

The transformation is:
**(G, k) -> (G, n-k)**

The graph stays the same; only the target number changes. A set S is independent exactly when its complement V-S is a vertex cover. Therefore G has an independent set of size at least k exactly when it has a vertex cover of size at most n-k.

The CLI demonstrates this transformation. Example: n=5 and k=3 maps to a Vertex Cover instance with q=2. The transformation takes O(1) arithmetic time after n and k are known, so it is polynomial time.

## 3. Benchmark workflow

Choose Complexity and benchmarking -> Run String Matching Benchmark. The program:
1. Creates deterministic test strings at lengths 500, 1000, 2000, and 4000.
2. Uses a repeated-'a' text and an almost-matching pattern ending in 'b' to create a challenging no-match case.
3. Runs Naive and KMP matching on the same input.
4. Counts character comparisons and measures CPU time with the C `clock()` function.
5. Prints a comparison table and saves a CSV report to `data/module9_benchmark.csv`.

CSV columns: algorithm, text length, pattern length, character comparisons, CPU time in milliseconds, and result. Times are machine/compiler dependent; comparison counts are generally more repeatable. Run on the same machine, compiler, and build settings when comparing results. This is an educational benchmark, not a universal performance ranking.

## 4. Files added

- `include/analysis.h`: reduction and benchmark interfaces.
- `src/analysis.c`: reduction mapping and benchmark runner.
- `tests/test_analysis.c`: reduction tests.
- `docs/PHASE9_COMPLEXITY_BENCHMARKS.md`: concepts, proof, and benchmark instructions.

## 5. Run

Build the app with `make`, run it, and choose main menu option 14. Run the complete test suite with `make test`.

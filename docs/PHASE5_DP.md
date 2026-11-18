# Phase 5: Dynamic Programming

This phase adds a DP submenu and algorithms that solve overlapping subproblems and reuse table results.

- **0/1 Knapsack:** weights, values, capacity; each item can be selected once. O(nW).
- **Matrix Chain Multiplication:** dimensions, optimize scalar multiplication order. O(n³).
- **LCS:** two strings; calculate longest common subsequence length. O(mn).
- **Optimal BST:** ordered key frequencies, minimize weighted search cost. O(n³).
- **Bellman-Ford:** edge triples and source; supports negative edges and detects reachable negative cycles. O(VE).
- **Floyd-Warshall:** all-pairs shortest distances with negative-edge support; detects negative cycles. O(V³).
- **Bounded TSP (Held-Karp):** exact minimum tour from/to vertex 0, limited to 16 vertices. O(n² 2ⁿ).

Graph vertices are zero-based. Bellman-Ford edge input is (from,to,weight). TSP matrix uses zero for absent edges and positive weights for edges. The TSP solver is exact but exponential, so its input is deliberately bounded.

Build/run: `make`, `make test`, `./digital_library`. Choose main menu option 10 for Phase 5.

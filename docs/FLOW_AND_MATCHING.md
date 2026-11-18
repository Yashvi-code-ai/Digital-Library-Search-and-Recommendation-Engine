# Flow and matching: Flow Networks and Bipartite Matching

This module implements two graph optimization algorithms.

## Workflow

1. **Ford-Fulkerson maximum flow:** enter a directed capacity matrix, source, and sink. The program copies capacities into a residual graph, searches for an augmenting path using BFS, pushes the bottleneck capacity, updates forward and reverse residual edges, and repeats until no augmenting path remains. The BFS variant is commonly called Edmonds-Karp.
2. **Maximum Bipartite Matching:** enter a 0/1 adjacency matrix connecting left-side vertices to right-side vertices. For each left vertex, DFS tries to find an available right vertex; if occupied, it recursively attempts to reassign the existing match. The program reports the maximum matching and each matched pair.

## Complexity

| Algorithm | Time | Space |
|---|---:|---:|
| Ford-Fulkerson with BFS (Edmonds-Karp) | O(VE²) | O(V²) |
| DFS augmenting-path bipartite matching | O(VE) | O(V+E) |

## Input rules

- Vertices are zero-based.
- Capacity matrix entries must be nonnegative; diagonal entries should be zero.
- Matching matrix entries must be 0 or 1.
- Each side is limited to 100 vertices for the interactive application.

## Build and run

`make`, `make test`, then `./digital_library`. Choose main menu option 12 for Flow and matching.

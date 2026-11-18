# Phase 4: Greedy Algorithms Workflow

Phase 4 introduces greedy algorithms. A greedy method repeatedly makes the best-looking local choice according to a rule. These choices are optimal for the specific problems below when their stated assumptions hold.

## Algorithms and user workflow

1. **Activity Selection** – enter activities as start/finish times. The program sorts by finish time and selects the largest compatible set. Activities are compatible when the next start is greater than or equal to the previous finish.
2. **Interval Partitioning** – enter start/finish times. Activities are sorted by start time and assigned to the first room that is free. The number of rooms returned is the minimum required.
3. **Huffman Coding** – enter symbols and their frequencies. Repeatedly combine the two least-frequent nodes to build a prefix-free binary code. Each symbol receives a 0/1 code.
4. **Dijkstra Shortest Paths** – enter a weighted adjacency matrix and source vertex. The program repeatedly finalizes the closest unvisited vertex and relaxes its outgoing edges. Edge weight 0 means no edge; negative weights are not supported.
5. **Prim Minimum Spanning Tree** – enter an undirected weighted adjacency matrix. The algorithm grows a tree from vertex 0 by choosing the lightest edge that connects a new vertex.
6. **Kruskal Minimum Spanning Tree** – enter an edge list. Edges are sorted by weight and accepted when they connect different components using Disjoint Set Union.
7. **Fractional Knapsack** – enter item weights, values, and capacity. Items are sorted by value/weight ratio; fractions of items may be selected.

## Complexity

| Algorithm | Time complexity |
|---|---:|
| Activity Selection | O(n log n) |
| Interval Partitioning (this implementation) | O(n²) |
| Huffman Coding (simple minimum scan) | O(n²) |
| Dijkstra (adjacency matrix) | O(V²) |
| Prim (adjacency matrix) | O(V²) |
| Kruskal | O(E log E) |
| Fractional Knapsack | O(n log n) |

## Assumptions and notes

- Dijkstra requires non-negative edge weights. In adjacency matrices, 0 denotes no edge, so zero-weight edges cannot be represented.
- Prim expects a connected, undirected graph. Kruskal reports failure if the graph is disconnected.
- Matrix/edge graph vertex indices are zero-based.
- Fractional Knapsack permits taking part of an item; it is not the 0/1 Knapsack algorithm.
- Huffman symbols should be unique; frequencies should be positive for a meaningful code.
- Activity intervals use half-open scheduling convention: an activity ending at time t can be followed by one starting at t.

## Build and test

```bash
make
make test
./digital_library
```

Choose **9** from the main menu to open Phase 4.

# DSA Fundamentals

## Big-O Reasoning

Big-O describes how resource usage grows as input size $n$ grows. Ignore constants and lower-order terms when comparing growth rates.

| Complexity | Common example |
|---|---|
| $O(1)$ | Array access, stack push |
| $O(\log n)$ | Binary search |
| $O(n)$ | One pass through an array |
| $O(n \log n)$ | Merge sort, heap sort |
| $O(n^2)$ | Comparing every pair |
| $O(2^n)$ | Enumerating subsets recursively |
| $O(n!)$ | Enumerating permutations |

Nested loops are not automatically $O(n^2)$. Count how often each loop actually advances. Two pointers that each move only forward are usually $O(n)$.

## Choosing a Data Structure

| Need | Useful structure |
|---|---|
| Fast access by index | `vector` / array |
| Last-in-first-out | Stack |
| First-in-first-out | Queue |
| Fast membership by value | Hash set |
| Key to value mapping | Hash map |
| Sorted values | `set`, `map`, or sorted `vector` |
| Repeated minimum or maximum | Heap / priority queue |
| Prefix queries | Trie |
| Connectivity between components | Disjoint Set Union |

## Core Invariants

An invariant is a fact that remains true throughout a loop or recursion.

- Two pointers: everything outside the active window has already been processed.
- Sliding window: the current window satisfies the required condition.
- Binary search: the answer, if it exists, remains inside the search interval.
- BFS: nodes are processed in nondecreasing distance from the source.
- DFS: the recursion stack represents the current path.

## Recursion Checklist

Every recursive solution needs:

1. A base case that stops recursion.
2. A smaller subproblem.
3. Progress toward the base case.
4. Correct handling of the returned result.

For backtracking, make a choice, recurse, then undo the choice.

## Graph Traversal

For an adjacency list, both BFS and DFS take $O(V + E)$ time and $O(V)$ auxiliary space.

```cpp
vector<int> distance(n, -1);
queue<int> q;
distance[source] = 0;
q.push(source);

while (!q.empty()) {
    int node = q.front();
    q.pop();

    for (int neighbor : graph[node]) {
        if (distance[neighbor] == -1) {
            distance[neighbor] = distance[node] + 1;
            q.push(neighbor);
        }
    }
}
```

## Testing Strategy

Always check:

- Empty and singleton inputs
- Already sorted and reverse-sorted inputs
- Duplicate values
- Negative and zero values
- The smallest and largest valid input
- A target that does not exist

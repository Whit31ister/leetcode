# Sorting Algorithms

Sorting often simplifies a problem by making duplicates adjacent, enabling two pointers, or allowing binary search.

## Comparison Sorts

| Algorithm | Best | Average | Worst | Extra space | Stable |
|---|---:|---:|---:|---:|---|
| Bubble sort | $O(n)$ | $O(n^2)$ | $O(n^2)$ | $O(1)$ | Yes |
| Insertion sort | $O(n)$ | $O(n^2)$ | $O(n^2)$ | $O(1)$ | Yes |
| Selection sort | $O(n^2)$ | $O(n^2)$ | $O(n^2)$ | $O(1)$ | No |
| Merge sort | $O(n \log n)$ | $O(n \log n)$ | $O(n \log n)$ | $O(n)$ | Yes |
| Quick sort | $O(n \log n)$ | $O(n \log n)$ | $O(n^2)$ | $O(\log n)$ average | Usually no |
| Heap sort | $O(n \log n)$ | $O(n \log n)$ | $O(n \log n)$ | $O(1)$ | No |

In contest code, prefer `std::sort` unless the problem asks for a specific algorithm or stability matters.

## Counting Sort

Use counting sort when values lie in a small known range. Its complexity is $O(n + k)$, where $k$ is the value range.

```cpp
vector<int> frequency(maxValue + 1, 0);
for (int value : values) {
    frequency[value]++;
}

vector<int> sorted;
for (int value = 0; value <= maxValue; value++) {
    while (frequency[value]-- > 0) {
        sorted.push_back(value);
    }
}
```

It is not appropriate when values are very large or spread out.

## Custom Sorting

```cpp
sort(items.begin(), items.end(), [](const Item& left, const Item& right) {
    if (left.score != right.score) {
        return left.score > right.score;
    }
    return left.name < right.name;
});
```

The comparator must define a consistent strict ordering. Avoid returning `left.score <= right.score`.

## Sorting-Based Patterns

- Sort, then use two pointers for pair or triplet sums.
- Sort, then skip adjacent duplicates.
- Sort intervals by start time before merging.
- Sort by end time for greedy interval selection.
- Sort values and use `lower_bound` for rank or insertion position.

## Common Mistakes

- Forgetting that `std::sort` changes the input.
- Using subtraction in a comparator, which can overflow.
- Applying binary search before sorting.
- Assuming sorting preserves original indices; store `(value, index)` when needed.
- Using $O(n \log n)$ sorting when a bounded counting approach gives $O(n + k)$.

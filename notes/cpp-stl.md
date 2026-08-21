# C++ STL Dictionary

Include only what is needed when possible. `#include <bits/stdc++.h>` is convenient for practice, but individual headers are better for portable code.

## Containers

| Type | Main use | Typical operation |
|---|---|---:|
| `vector<T>` | Resizable contiguous array | Index: $O(1)$, append: amortized $O(1)$ |
| `deque<T>` | Insert/remove at both ends | End operations: $O(1)$ |
| `list<T>` | Linked-list insertion with an iterator | Insert/erase at iterator: $O(1)$ |
| `stack<T>` | LIFO access | Push/pop/top: $O(1)$ |
| `queue<T>` | FIFO access | Push/pop/front: $O(1)$ |
| `priority_queue<T>` | Maximum heap by default | Push/pop: $O(\log n)$ |
| `set<T>` | Sorted unique values | Insert/find/erase: $O(\log n)$ |
| `unordered_set<T>` | Unique values without ordering | Average insert/find/erase: $O(1)$ |
| `map<K, V>` | Sorted key-value pairs | Insert/find/erase: $O(\log n)$ |
| `unordered_map<K, V>` | Hash-based key-value pairs | Average insert/find/erase: $O(1)$ |

## `vector`

```cpp
vector<int> values = {4, 1, 3};
values.push_back(8);
values.emplace_back(13);
values.pop_back();

sort(values.begin(), values.end());
reverse(values.begin(), values.end());

for (int value : values) {
    cout << value << ' ';
}
```

Use `values.empty()` before accessing `front()`, `back()`, or an index.

## `map` and `unordered_map`

```cpp
unordered_map<int, int> frequency;
for (int value : values) {
    frequency[value]++;
}

if (frequency.find(target) != frequency.end()) {
    cout << frequency[target];
}
```

Use `map` when sorted key order is needed. Use `unordered_map` for average constant-time lookup when order does not matter.

## `set` and `unordered_set`

```cpp
unordered_set<int> seen;
for (int value : values) {
    if (seen.count(value)) {
        return true;
    }
    seen.insert(value);
}
```

`count(value)` returns `0` or `1` for a set. `erase(value)` removes the value if present.

## Algorithms

```cpp
sort(values.begin(), values.end());
int count = count_if(values.begin(), values.end(), [](int value) {
    return value > 0;
});

bool exists = binary_search(values.begin(), values.end(), target);
auto first = lower_bound(values.begin(), values.end(), target);
auto after = upper_bound(values.begin(), values.end(), target);
```

`lower_bound` returns the first position whose value is at least the target. `upper_bound` returns the first position whose value is greater than the target. Both require sorted data.

## Useful Idioms

```cpp
// Maximum heap
priority_queue<int> maxHeap;

// Minimum heap
priority_queue<int, vector<int>, greater<int>> minHeap;

// Sort pairs by second value
sort(pairs.begin(), pairs.end(), [](const auto& left, const auto& right) {
    return left.second < right.second;
});

// Remove duplicate values from a sorted vector
values.erase(unique(values.begin(), values.end()), values.end());
```

## Iterator Safety

After `vector` growth, iterators and references may be invalidated. Do not keep an iterator across `push_back` unless the vector capacity is known to remain sufficient. Prefer indices or range-based loops when mutation is not needed.

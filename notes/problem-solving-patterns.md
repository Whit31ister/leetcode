# Problem-Solving Patterns

## A Reliable Workflow

1. Read the constraints before choosing an algorithm.
2. Write a brute-force solution mentally to clarify the requirement.
3. Find repeated work, then replace it with sorting, hashing, prefix data, or a better traversal.
4. State the loop invariant and prove why each pointer or state transition is valid.
5. Test edge cases and calculate complexity.

## Two Sum and Hashing

Store values already seen and query the complement before inserting the current value. This prevents using the same element twice.

```cpp
unordered_map<int, int> indexOf;
for (int index = 0; index < nums.size(); index++) {
    int needed = target - nums[index];
    if (indexOf.count(needed)) {
        return {indexOf[needed], index};
    }
    indexOf[nums[index]] = index;
}
```

## Two Pointers

Sort first when the order of the original array does not matter. Move the left pointer when the sum is too small and the right pointer when it is too large.

Typical problems: Two Sum II, 3Sum, 4Sum, removing duplicates, and container area.

## Sliding Window

Maintain a window `[left, right]`. Expand with `right`; while the window violates the condition, remove values from the left.

```cpp
int left = 0;
for (int right = 0; right < nums.size(); right++) {
    add(nums[right]);
    while (!valid()) {
        remove(nums[left]);
        left++;
    }
    answer = max(answer, right - left + 1);
}
```

## Prefix Sum

Let `prefix[i]` represent the sum before index `i`. A range sum from `left` through `right` is `prefix[right + 1] - prefix[left]`.

For subarray-sum targets, store counts of previous prefix sums in a hash map.

## Binary Search on the Answer

Use this when feasibility is monotonic: once a value works, every larger or smaller value also works. Define a clear predicate such as `canFinish(limit)` and search its first true value.

## Intervals

Sort intervals by start. Merge when the next start is at most the current end; otherwise, save the current interval and begin a new one.

## BFS and DFS

- BFS is useful for shortest paths in unweighted graphs and level-order processing.
- DFS is useful for connected components, cycle checks, and exhaustive exploration.
- Mark a node when it is discovered, not when it is removed, to avoid duplicate work.

## Dynamic Programming

1. Define the state in one sentence.
2. Define the transition from smaller states.
3. Set base cases.
4. Choose memoization or bottom-up iteration.
5. Reduce memory only after the transition is correct.

A good state contains enough information to determine all future decisions, but no unnecessary history.

## Backtracking

```cpp
void search(int start) {
    if (complete()) {
        answers.push_back(current);
        return;
    }

    for (int choice = start; choice < options.size(); choice++) {
        current.push_back(options[choice]);
        search(choice + 1);
        current.pop_back();
    }
}
```

Skip duplicate choices at the same recursion depth after sorting.

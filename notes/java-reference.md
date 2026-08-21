# Java LeetCode Reference

## Standard Solution Shape

```java
import java.util.*;

class Solution {
    public int[] solve(int[] nums) {
        return new int[0];
    }
}
```

LeetCode supplies the input and calls the method, so submissions usually do not need a `main` method. Keep each practice file independent when several files define a class named `Solution`.

## Common Collections

| Java type | Use | Typical complexity |
|---|---|---:|
| `int[]` | Fixed-size primitive array | Index access: $O(1)$ |
| `ArrayList<E>` | Resizable list | Access: $O(1)$, append: amortized $O(1)$ |
| `HashSet<E>` | Fast membership and uniqueness | Average add/contains: $O(1)$ |
| `HashMap<K, V>` | Key-value lookup | Average put/get: $O(1)$ |
| `TreeSet<E>` | Sorted unique values | Add/contains: $O(\log n)$ |
| `TreeMap<K, V>` | Sorted key-value pairs | Put/get: $O(\log n)$ |
| `ArrayDeque<E>` | Stack or queue behavior | End operations: $O(1)$ |
| `PriorityQueue<E>` | Min-heap by default | Add/remove: $O(\log n)$ |

## Arrays and Lists

```java
Arrays.sort(nums);
int[] copy = nums.clone();
List<Integer> values = new ArrayList<>();
values.add(5);
values.remove(values.size() - 1);

for (int value : nums) {
    System.out.println(value);
}
```

Use `Arrays.asList(a, b, c)` for a fixed-size list view when boxing is acceptable. For a mutable list, use `new ArrayList<>(Arrays.asList(a, b, c))`.

## Hash Maps and Sets

```java
Map<Integer, Integer> frequency = new HashMap<>();
for (int value : nums) {
    frequency.put(value, frequency.getOrDefault(value, 0) + 1);
}

Set<Integer> seen = new HashSet<>();
if (!seen.add(value)) {
    // value was already present
}
```

`HashMap` and `HashSet` do not guarantee iteration order. Use `TreeMap` or `TreeSet` when sorted order is part of the result.

## Queues, Stacks, and Heaps

```java
Deque<Integer> queue = new ArrayDeque<>();
queue.addLast(source);
int node = queue.removeFirst();

Deque<Integer> stack = new ArrayDeque<>();
stack.push(node);
int top = stack.pop();

PriorityQueue<Integer> minHeap = new PriorityQueue<>();
PriorityQueue<Integer> maxHeap = new PriorityQueue<>(Collections.reverseOrder());
```

Avoid using `Stack`; `ArrayDeque` is the usual choice for stack behavior.

## Sorting and Searching

```java
Arrays.sort(nums);
Arrays.sort(intervals, (left, right) -> Integer.compare(left[0], right[0]));

Collections.sort(values);
values.sort((left, right) -> Integer.compare(right, left));
```

Use `Integer.compare` instead of subtracting values in comparators, because subtraction can overflow.

## Integer Safety

Use `long` before arithmetic that may exceed the range of `int`.

```java
long sum = (long) left + right + middle;
long expected = (long) n * (n + 1) / 2;
```

Use `Math.abs` carefully: `Math.abs(Integer.MIN_VALUE)` still overflows because the positive value cannot fit in an `int`.

## Common Patterns

- Use `HashMap` for complements, frequencies, and prefix-sum counts.
- Sort arrays before two-pointer searches or duplicate skipping.
- Use `ArrayDeque` for BFS and DFS.
- Use `PriorityQueue` for repeatedly selecting the smallest or largest item.
- Use `StringBuilder` when building strings inside a loop.
- Prefer primitive arrays when performance and memory matter.

## Compile Locally

```bash
javac -d out Java/Array/2_Two_Sum.java
```

Because LeetCode files commonly use the same class name, compile one solution file at a time unless the classes have been renamed.

# LeetCode C++ Reference

## Standard Function Shape

```cpp
class Solution {
public:
    vector<int> solve(vector<int>& nums) {
        return {};
    }
};
```

Use the function signature required by the problem. LeetCode supplies the input and calls the method, so a `main` function is usually unnecessary in submissions.

## Common Headers

```cpp
#include <algorithm>
#include <cmath>
#include <deque>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
```

`using namespace std;` is convenient for practice. In larger projects, prefer explicit names such as `std::vector`.

## Integer Safety

Use `long long` before arithmetic can exceed `int`.

```cpp
long long total = 1LL * leftValue + rightValue;
long long expected = 1LL * n * (n + 1) / 2;
```

Do not rely on `abs(INT_MIN)`, because its positive value cannot be represented by `int`.

## Useful Initialization

```cpp
vector<int> distance(n, -1);
vector<vector<int>> graph(n);
vector<vector<int>> matrix(rows, vector<int>(columns, 0));
```

## Input and Output for Local Tests

```cpp
int n;
cin >> n;
vector<int> nums(n);
for (int& value : nums) {
    cin >> value;
}

for (int value : nums) {
    cout << value << ' ';
}
cout << '\n';
```

## Debugging Checklist

- Verify the loop bounds, especially `i + 1`, `n - 1`, and empty input.
- Check whether the input is allowed to be modified.
- Check duplicate handling at every recursion depth or pointer movement.
- Use `long long` for sums and products.
- Confirm that a hash lookup happens before insertion when solving Two Sum.
- Compile with warnings during local practice:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic solution.cpp -o solution
```

## Complexity Template

At the end of each solution, record:

```text
Time: O(...)
Space: O(...)
```

State auxiliary space separately from space used for the returned result when that distinction matters.

## Boundary Test Cases

For array problems, try `[]`, `[x]`, all equal values, already sorted values, reverse order, negative values, the largest allowed values, and a case with no valid answer.

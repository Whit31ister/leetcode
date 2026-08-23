#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <cmath>
#include <climits>
using namespace std;

// Fast I/O Optimization
auto init = []() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return 0;
}();

// Data Structures for Local Compilation
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// ==========================================
// 1. BRUTE FORCE SOLUTION
// Time Complexity:  O(N^2)
// Space Complexity: O(1)
// ==========================================
class SolutionBrute {
public:
    int solve(vector<int>& nums) {
        
        return {};
    }
};

// ==========================================
// 2. OPTIMAL SOLUTION (Submit to LeetCode)
// Time Complexity:  O(N)
// Space Complexity: O(1)
// ==========================================
class Solution {
public:
    int solve(vector<int>& nums) {
        
        return {};
    }
};

#ifndef ONLINE_JUDGE
int main() {
    SolutionBrute bruteSol;
    Solution optSol;

    // Example Local Test
    // vector<int> nums = {1, 2, 3};
    // cout << "Brute Force Result: " << bruteSol.solve(nums) << endl;
    // cout << "Optimal Result:     " << optSol.solve(nums) << endl;

    return 0;
}
#endif
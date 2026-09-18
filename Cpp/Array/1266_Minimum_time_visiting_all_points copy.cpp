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
    int solve(vector<vector<int>>& points) {
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
    int solve(vector<vector<int>>& points) {
        int total_time = 0;
        int n = points.size();

        // Loop through the points
        for(int i = 0; i < n - 1; i++){
            int x1 = points[i][0];
            int y1 = points[i][1];

            int x2 = points[i + 1][0];
            int y2 = points[i + 1][1];
            
            // segment logic using abs() and max ()
            
            int delta_x = abs(x2 - x1);
            int delta_y = abs(y2 - y1);

            total_time += max(delta_x, delta_y);
        }        
        return total_time;
    }
};

#ifndef ONLINE_JUDGE
int main() {
    SolutionBrute bruteSol;
    Solution optSol;
    vector<vector<int>> points = {{1, 1}, {3, 4}, {-1, 0}};

    cout << optSol.solve(points);

    return 0;
}
#endif
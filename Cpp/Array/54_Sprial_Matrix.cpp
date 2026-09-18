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
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        return {};
    }
};

// ==========================================
// 2. OPTIMAL SOLUTION (Submit to LeetCode)
// Time Complexity:  O(N)
// Space Complexity: O(1)
// ==========================================
class SolutionOptimal {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int order_n;
        int order_m;

        order_n = matrix[0].size();
        order_m = matrix.size(); 

        int top = 0;
        int bottom = (order_m - 1);
        int left = 0;
        int right = (order_n - 1);

        vector<int> spiral_list = {}; 

        while(top <= bottom && left <= right){
            for(int j = left ;  j <= right; j++){
                spiral_list.push_back(matrix[top][j]);
            }
            top++;
            for(int k = top ; k <= bottom; k++){
                spiral_list.push_back(matrix[k][right]);
            }
            right--;
            if (top <= bottom) {
                for (int j = right; j >= left; --j) {
                    spiral_list.push_back(matrix[bottom][j]);
                }
                bottom--;
            }

            if (left <= right) {
                for (int i = bottom; i >= top; --i) {
                    spiral_list.push_back(matrix[i][left]);
                }
                left++; 
            }}
        return spiral_list;
    }
};

#ifndef ONLINE_JUDGE
int main() {
    SolutionBrute bruteSol;
    SolutionOptimal optSol;

    // this is a test matrix 
    vector<vector<int>> test_matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    
    for(const auto& element : test_matrix){
        for(int num : element){
            cout << num << " ";
        }
        cout << endl; 
    }

    vector<int> result = optSol.spiralOrder(test_matrix);

    for(int num : result){
        cout << num << " ";
    }

    cout << endl; 

    return 0;
}
#endif
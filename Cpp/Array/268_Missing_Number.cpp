#include <vector>
#include <algorithm>

using namespace std;

// Brute Force Solution
class Solution_BruteForce {
public:
    int missingNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        
        for (int i = 0; i < nums.size(); i++) {
            if (i != nums[i]) {
                return i;
            }
        }
        
        return nums.size(); // Missing number is the last one
    }
};

// Optimal Solution - Sum Formula
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        long long expectedSum = (long long)n * (n + 1) / 2;
        long long actualSum = 0;
        
        for (int num : nums) {
            actualSum += num;
        }
        
        return expectedSum - actualSum;
    }
};

// Alternative Optimal Solution - XOR
class Solution_XOR {
public:
    int missingNumber(vector<int>& nums) {
        int xorResult = 0;
        
        // XOR all numbers in the array
        for (int num : nums) {
            xorResult ^= num;
        }
        
        // XOR with all numbers from 0 to n
        for (int i = 0; i <= nums.size(); i++) {
            xorResult ^= i;
        }
        
        return xorResult;
    }
};

// Local Testing
int main() {
    Solution sol;
    Solution_BruteForce sol_brute;
    Solution_XOR sol_xor;
    
    vector<int> array1 = {0, 1, 2, 3, 5}; // Missing: 4
    vector<int> array2 = {0, 1, 2, 3, 4, 5, 7, 8}; // Missing: 6
    
    int result1 = sol.missingNumber(array1);
    int result2 = sol.missingNumber(array2);
    
    return 0;
}

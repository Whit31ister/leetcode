#include <vector>
#include <unordered_set>

using namespace std;

// Brute Force Solution - O(n log n)
class Solution_Brute {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        
        vector<int> missing;
        int expected = 1;
        
        for (int num : nums) {
            // Gap - fill missing numbers
            while (num > expected) {
                missing.push_back(expected);
                expected++;
            }
            // Matched expected
            if (num == expected) {
                expected++;
            }
        }
        
        // Add remaining missing numbers
        while (expected <= nums.size()) {
            missing.push_back(expected);
            expected++;
        }
        
        return missing;
    }
};

// Optimal Solution - Hash Set O(n)
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        unordered_set<int> numSet(nums.begin(), nums.end());
        vector<int> result;
        
        for (int i = 1; i <= nums.size(); i++) {
            if (numSet.find(i) == numSet.end()) {
                result.push_back(i);
            }
        }
        
        return result;
    }
};

// Alternative Optimal Solution - In-place marking
class Solution_InPlace {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        // Mark numbers as negative to indicate they exist
        for (int num : nums) {
            int index = abs(num) - 1;
            if (nums[index] > 0) {
                nums[index] = -nums[index];
            }
        }
        
        vector<int> result;
        
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] > 0) {
                result.push_back(i + 1);
            }
        }
        
        return result;
    }
};

// Local Testing
int main() {
    Solution sol;
    Solution_Brute sol_brute;
    Solution_InPlace sol_inplace;
    
    vector<int> array1 = {4, 3, 2, 7, 8, 2, 3, 1};
    
    vector<int> result = sol.findDisappearedNumbers(array1);
    
    return 0;
}

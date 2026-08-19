#include <vector>
#include <unordered_set>

using namespace std;

// Brute Force Solution - O(n^2)
class Solution_Brute {
public:
    bool containsDuplicate(vector<int>& nums) {
        int n = nums.size();
        
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (nums[i] == nums[j]) {
                    return true;
                }
            }
        }
        
        return false;
    }
};

// Optimal Solution - Hash Set
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> seen;
        
        for (int num : nums) {
            if (seen.find(num) != seen.end()) {
                return true;
            }
            seen.insert(num);
        }
        
        return false;
    }
};

// Alternative Optimal Solution - Compare sizes
class Solution_SetCompare {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> uniqueNums(nums.begin(), nums.end());
        return uniqueNums.size() != nums.size();
    }
};

// Local Testing
int main() {
    Solution sol;
    Solution_Brute sol_brute;
    Solution_SetCompare sol_compare;
    
    vector<int> nums1 = {12, 4};
    vector<int> nums2 = {1, 2, 3, 4, 5};
    vector<int> nums3 = {1, 1, 1, 1};
    
    bool result1 = sol.containsDuplicate(nums1);
    bool result2 = sol.containsDuplicate(nums2);
    bool result3 = sol.containsDuplicate(nums3);
    
    return 0;
}

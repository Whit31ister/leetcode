#include <vector>
#include <algorithm>

using namespace std;

// Brute Force Solution
class Solution_Brute {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        set<vector<int>> uniqueTriples; // To store unique triplets
        
        sort(nums.begin(), nums.end());
        int n = nums.size();
        
        for (int i = 0; i < n - 2; i++) {
            if (nums[i] > 0) {
                break; // Optimization: if the smallest number is positive, no solution
            }
            
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue; // Skip duplicate values for the fixed element
            }
            
            int left = i + 1;
            int right = n - 1;
            
            while (left < right) {
                int total = nums[i] + nums[left] + nums[right];
                
                if (total == 0) {
                    uniqueTriples.insert({nums[i], nums[left], nums[right]});
                    
                    // Skip duplicate values for left pointer
                    while (left < right && nums[left] == nums[left + 1]) {
                        left++;
                    }
                    
                    // Skip duplicate values for right pointer
                    while (left < right && nums[right] == nums[right - 1]) {
                        right--;
                    }
                    
                    left++;
                    right--;
                } else if (total < 0) {
                    left++; // Need a larger sum
                } else {
                    right--; // Need a smaller sum
                }
            }
        }
        
        for (const auto& triplet : uniqueTriples) {
            res.push_back(triplet);
        }
        
        return res;
    }
};

// Optimal Solution
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        
        sort(nums.begin(), nums.end());
        int n = nums.size();
        
        for (int i = 0; i < n - 2; i++) {
            if (nums[i] > 0) {
                break;
            }
            
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            
            int left = i + 1;
            int right = n - 1;
            
            while (left < right) {
                int total = nums[i] + nums[left] + nums[right];
                
                if (total == 0) {
                    res.push_back({nums[i], nums[left], nums[right]});
                    
                    while (left < right && nums[left] == nums[left + 1]) {
                        left++;
                    }
                    while (left < right && nums[right] == nums[right - 1]) {
                        right--;
                    }
                    
                    left++;
                    right--;
                } else if (total < 0) {
                    left++;
                } else {
                    right--;
                }
            }
        }
        
        return res;
    }
};

// Local Testing
int main() {
    Solution sol;
    Solution_Brute sol_brute;
    vector<int> array1 = {-1, 0, 1, 2, -1, -4};
    
    vector<vector<int>> result = sol.threeSum(array1);
    
    return 0;
}

#include <vector>
#include <algorithm>
#include <set>

using namespace std;

// Brute Force Solution - O(n^4)
class Solution_Brute {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        set<vector<int>> quadSet;
        
        for (int a = 0; a < n - 3; a++) {
            for (int b = a + 1; b < n - 2; b++) {
                for (int c = b + 1; c < n - 1; c++) {
                    for (int d = c + 1; d < n; d++) {
                        if (nums[a] + nums[b] + nums[c] + nums[d] == target) {
                            quadSet.insert({nums[a], nums[b], nums[c], nums[d]});
                        }
                    }
                }
            }
        }
        
        vector<vector<int>> res;
        for (const auto& quad : quadSet) {
            res.push_back(quad);
        }
        return res;
    }
};

// Optimal Solution - O(n^3)
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        vector<vector<int>> res;
        
        for (int i = 0; i < n - 3; i++) {
            // Skip duplicates for the first element
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            
            for (int j = i + 1; j < n - 2; j++) {
                // Skip duplicates for the second element
                if (j > i + 1 && nums[j] == nums[j - 1]) {
                    continue;
                }
                
                int left = j + 1;
                int right = n - 1;
                
                while (left < right) {
                    long long total = (long long)nums[i] + nums[j] + nums[left] + nums[right];
                    
                    if (total == target) {
                        res.push_back({nums[i], nums[j], nums[left], nums[right]});
                        
                        while (left < right && nums[left] == nums[left + 1]) {
                            left++;
                        }
                        while (left < right && nums[right] == nums[right - 1]) {
                            right--;
                        }
                        
                        left++;
                        right--;
                    } else if (total < target) {
                        left++;
                    } else {
                        right--;
                    }
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
    vector<int> array1 = {1, 0, -1, 0, -2, 2};
    int target = 0;
    
    vector<vector<int>> result = sol.fourSum(array1, target);
    
    return 0;
}

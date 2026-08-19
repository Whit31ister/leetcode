#include <vector>
#include <unordered_map>

using namespace std;

// Optimal Solution - Hash Map
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hashMap; // value -> index
        
        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            
            if (hashMap.find(complement) != hashMap.end()) {
                return {hashMap[complement], i};
            }
            
            hashMap[nums[i]] = i;
        }
        
        return {}; // No solution found
    }
};

// Brute Force Solution - Two nested loops O(n^2)
class Solution_Brute {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                if (nums[i] + nums[j] == target) {
                    return {i, j};
                }
            }
        }
        return {}; // No solution found
    }
};

// Local Testing
int main() {
    Solution sol;
    Solution_Brute sol_brute;
    vector<int> array1 = {2, 7, 11, 15};
    int target = 9;
    
    vector<int> result = sol.twoSum(array1, target);
    
    return 0;
}

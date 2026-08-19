#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
        vector<int> res;
        
        // For each number, count how many numbers are smaller
        for (int i = 0; i < nums.size(); i++) {
            int count = 0;
            for (int j = 0; j < nums.size(); j++) {
                if (nums[j] < nums[i]) {
                    count++;
                }
            }
            res.push_back(count);
        }
        
        return res;
    }
};

// Optimal Solution - O(n log n) using sorting
class Solution_Optimal {
public:
    vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
        vector<pair<int, int>> sortedNums; // (value, original_index)
        
        for (int i = 0; i < nums.size(); i++) {
            sortedNums.push_back({nums[i], i});
        }
        
        sort(sortedNums.begin(), sortedNums.end());
        
        vector<int> res(nums.size());
        
        for (int i = 0; i < sortedNums.size(); i++) {
            res[sortedNums[i].second] = i;
        }
        
        return res;
    }
};

// Local Testing
int main() {
    Solution sol;
    Solution_Optimal sol_opt;
    vector<int> array1 = {8, 1, 2, 2, 3};
    
    vector<int> result1 = sol.smallerNumbersThanCurrent(array1);
    vector<int> result2 = sol_opt.smallerNumbersThanCurrent(array1);
    
    return 0;
}

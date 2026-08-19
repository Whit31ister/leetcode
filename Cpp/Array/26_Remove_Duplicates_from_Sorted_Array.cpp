#include <vector>
#include <algorithm>
#include <set>

using namespace std;

// Brute Force Solution
class Solution_Brute {
public:
    int removeDuplicates(vector<int>& nums) {
        set<int> uniqueSet(nums.begin(), nums.end());
        vector<int> unique(uniqueSet.begin(), uniqueSet.end());
        sort(unique.begin(), unique.end());
        
        for (int i = 0; i < unique.size(); i++) {
            nums[i] = unique[i];
        }
        
        return unique.size();
    }
};

// Optimal Solution - Two Pointers
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }
        
        int i = 0; // Slow pointer
        
        for (int j = 1; j < nums.size(); j++) {
            if (nums[j] != nums[i]) {
                i++;
                nums[i] = nums[j];
            }
        }
        
        return i + 1;
    }
};

// Local Testing
int main() {
    Solution sol;
    Solution_Brute sol_brute;
    
    vector<int> array1 = {1, 2, 2, 2, 2, 2, 2, 3, 4, 5, 6, 7, 8};
    vector<int> array2 = {1, 2, 3, 4, 4, 4, 4, 4, 5, 6, 7, 8};
    
    int result1 = sol_brute.removeDuplicates(array1);
    int result2 = sol.removeDuplicates(array2);
    
    return 0;
}

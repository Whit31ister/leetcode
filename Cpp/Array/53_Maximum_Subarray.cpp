#include <algorithm>
#include <vector>

using namespace std;

class Solution_Brute {
public:
    int maxSubArray(vector<int>& nums) {
        int bestSum = nums[0];

        for (size_t start = 0; start < nums.size(); start++) {
            int currentSum = 0;
            for (size_t end = start; end < nums.size(); end++) {
                currentSum += nums[end];
                bestSum = max(bestSum, currentSum);
            }
        }

        return bestSum;
    }
};

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int currentSum = nums[0];
        int bestSum = nums[0];

        for (size_t i = 1; i < nums.size(); i++) {
            currentSum = max(nums[i], currentSum + nums[i]);
            bestSum = max(bestSum, currentSum);
        }

        return bestSum;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int result = sol.maxSubArray(nums);
    (void)result;
    return 0;
}

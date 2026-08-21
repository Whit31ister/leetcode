# Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
# Output: 6

# Brute Force
class Solution_Brute:
    def maxSubArray(self, nums: list[int]) -> int:
        best_sum = nums[0]

        for start in range(len(nums)):
            current_sum = 0
            for end in range(start, len(nums)):
                current_sum += nums[end]
                best_sum = max(best_sum, current_sum)

        return best_sum


# Optimal Solution - Kadane's Algorithm
class Solution:
    def maxSubArray(self, nums: list[int]) -> int:
        best_sum = nums[0]
        current_sum = nums[0]

        for num in nums[1:]:
            current_sum = max(num, current_sum + num)
            best_sum = max(best_sum, current_sum)

        return best_sum


# Local Testing
nums = [-2, 1, -3, 4, -1, 2, 1, -5, 4]
sol = Solution()
print(sol.maxSubArray(nums))

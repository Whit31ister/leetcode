# Input: nums = [-1,0,3,5,9,12], target = 9
# Output: 4

# Reference Solution - Linear Search
class Solution_Brute:
    def search(self, nums: list[int], target: int) -> int:
        for index, value in enumerate(nums):
            if value == target:
                return index
        return -1


# Optimal Solution - Binary Search
class Solution:
    def search(self, nums: list[int], target: int) -> int:
        left = 0
        right = len(nums) - 1

        while left <= right:
            middle = left + (right - left) // 2

            if nums[middle] == target:
                return middle
            if nums[middle] < target:
                left = middle + 1
            else:
                right = middle - 1

        return -1


# Local Testing
nums = [-1, 0, 3, 5, 9, 12]
sol = Solution()
print(sol.search(nums, 9))

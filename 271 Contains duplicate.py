# Brute Force

# class Solution:
#     def containsDuplicate(self, nums: nums[int]) -> bool:
#         n = len(nums)
#         for i in range(n):
#             for j in range(i+1, n):
#                 if nums[i] == nums[j]:
#                     return True
#                     print("Returned True")
#         return False
#         print("Returned False")

# Good complexity

class Solution:
    def containsDuplicate(self, nums: nums[int]) -> bool:
        length_list = len(nums)
        length_set = len(set(nums))
        if length_list == length_set:
            return False
        else:
            return True

            
#Local Testing
nums = [12,4]
sol = Solution()
print(sol.containsDuplicate(nums))
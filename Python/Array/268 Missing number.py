# Brute force
class Solution1:
    def missingNumber(self, nums: List[int]) -> int:
        nums.sort()
        for i,v in enumerate(nums):
            if ( i != v):
                return v-1
            
            if v == len(nums) - 1:
                return v + 1

sol1 = Solution1()
array1 = [0,1,2,3,5] # 4
print(sol1.missingNumber(array1))

# Good complexity
class Solution:
    def missingNumber(self, nums: List[int]) -> int:
        return sum(range(len(nums) + 1)) - sum(nums)
    
sol = Solution()
array2 = [0,1,2,3,4,5,7,8] # 6
print(sol.missingNumber(array2))

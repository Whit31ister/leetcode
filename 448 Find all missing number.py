# Brute Force

# Input: nums = [4,3,2,7,8,2,3,1]
# Output: [5,6]

from typing import List

class Solution_Brute:
    def findDisappearedNumbers(self, nums: List[int]) -> List[int]:
        nums.sort
        
        n = len(nums)
        missing = []
        expected = 1
        
        for num in nums:
            # Gap
            while num > expected:
                missing.append(expected)
                expected += 1
            # Matched expected
            if num == expected:
                expected += 1
        while expected <= n:
            missing.append(expected)
            expected += 1
        return missing        
        
        
# Local Testing
# sol_brute = Solution_Brute()
array1 = [4,3,2,7,8,2,3,1]
# print(sol_brute.findDisappearedNumbers(array1))

# Optimal Solution

class Solution_Optimal:
    def findDisappearedNumbers(self, nums: List[int]) -> List[int]:
        set_nums = set(nums)
        ret =[]
        for i in range(1, len(nums)+1):
            if i not in set_nums:
                ret.append(i)
        return ret
        
        
# Local Testing
sol_optimal = Solution_Optimal()
array2 = array1
print(sol_optimal.findDisappearedNumbers(array2))
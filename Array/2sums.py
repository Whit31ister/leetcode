from typing import List
# Optimal Sol

# Input: nums = [2,7,11,15], target = 9
# Output: [0,1]

class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        hash_map = {}
        
        for i, v in enumerate(nums):
            
            if target-v in hash_map:
                
                return [i, hash_map[target-v]]
            
            else:
                hash_map[v] = i
            
        
        
#Local Testing
sol = Solution()
array1 , target = [2,7,11,15] , 9
print(sol.twoSum(array1, target))
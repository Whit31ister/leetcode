from typing import List


# Input: nums = [1,0,-1,0,-2,2], target = 0
# Output: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]

#Brute Force Sol
class Solution_Brute:
    def fourSum(self, nums: List[int], target: int) -> List[List[int]]:
        nums.sort()
        n = len(nums)
        quad = set()
        
        for a in range(0 , n - 3):
            for b in range(a + 1 , n - 2):
                for c in range(b + 1 , n - 1):
                    for d in range(c + 1, n):
                        if (nums[a] + nums[b] + nums[c] + nums[d] == target):
                            quad.add((nums[a], nums[b], nums[c], nums[d]))
                            
        return [list(quad) for quad in quad]
        
#Local Testing
sol_brute = Solution_Brute()
array1 = [1,0,-1,0,-2,2]
target = 0
# print(sol_brute.fourSum(array1, target))

#Optimal Sol
class Solution_Optimal:
    def fourSum(self, nums: List[int], target: int) -> List[List[int]]:
        nums.sort()
        n = len(nums)
        res = []
        for i in range(n - 3):
            # Skip duplicates for the first element
            if i > 0 and nums[i] == nums[i - 1]:
                continue

            for j in range(i + 1, n - 2):
                # Skip duplicates for the second element
                if j > i + 1 and nums[j] == nums[j - 1]:
                    continue

                left = j + 1
                right = n - 1

                while left < right:
                    total = nums[i] + nums[j] + nums[left] + nums[right]

                    if total == target:
                        res.append(
                            [nums[i], nums[j], nums[left], nums[right]]
                        )
                        left += 1
                        right -= 1

                        # Skip duplicates for the third element
                        while left < right and nums[left] == nums[left - 1]:
                            left += 1

                        # Skip duplicates for the fourth element
                        while left < right and nums[right] == nums[right + 1]:
                            right -= 1

                    elif total < target:
                        left += 1
                    else:
                        right -= 1

        return res        
        
        
        
#Local testing
sol_optimal = Solution_Optimal()
print(sol_optimal.fourSum(array1, target))
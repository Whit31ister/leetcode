# Input: nums = [-1,0,1,2,-1,-4]
# Output: [[-1,-1,2],[-1,0,1]]        

#Brute Force

class Solution_Brute:
    def threeSum(self, nums: list[int]) -> list[list[int]]:
        res = []       
        nums.sort() # Sorting the array
        n = len(nums)
        
        for i in range(n-2):
            if nums[i] > 0: # Optimization for an impossible case 
                break
            
            if (i > 0) and (nums[i] == nums[i-1]): # skip duplicates for the fixed element
                continue
            
            left, right = i+1, n-1
            
            while (left < right):
                total_sum = nums[i] + nums[left] + nums[right]
                
                if total_sum == 0:
                    res.append([nums[i], nums[left], nums[right]]) 
                    
                    # Skip duplicate values for left pointer
                    while left < right and nums[left] == nums[left + 1]:
                        left += 1

                    # Skip duplicate values for right pointer
                    while left < right and nums[right] == nums[right - 1]:
                        right -= 1

                    left += 1
                    right -= 1

                elif total_sum < 0:
                    left += 1  # Need a larger sum

                else:
                    right -= 1 # Need a smaller sum
                    
        return res
                    

sol_brute = Solution_Brute()
array1 = [-1,0,1,2,-1,-4]
print(array1)
print(sol_brute.threeSum(array1))

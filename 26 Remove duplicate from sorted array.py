# Brute Force
class Solution_Brute:
    def removeDuplicates(self, nums: List[int]) -> int:
        unique_el = sorted(list(set(nums)))
        
        for i in range(len(unique_el)):
            nums[i] = unique_el[i]
        
        return len(unique_el)

# Local testing
array1 = [1,2,2,2,2,2,2,3,4,5,6,7,8]
sol_brute = Solution_Brute()
print(sol_brute.removeDuplicates(array1))
print(array1)

# Optimal Sol
class Solution_Optimal:
    def removeDuplicates(self, nums: List[int]) -> int:
        if not nums:
            return 0;
        
        # slow pointer
        i = 0
        for j in range(len(nums)):
            if nums[j] != nums[i]:
                i += 1
                nums[i] = nums[j]
            
        return i + 1
    
array2 = [1,2,3,4,4,4,4,4,5,6,7,8]
sol_optimal = Solution_Optimal()
sol_optimal.removeDuplicates(array2)
print(array2)          
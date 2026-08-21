import java.util.Arrays;

class SolutionBrute {
    public int missingNumber(int[] nums) {
        Arrays.sort(nums);
        for (int i = 0; i < nums.length; i++) {
            if (nums[i] != i) return i;
        }
        return nums.length;
    }
}

class Solution {
    public int missingNumber(int[] nums) {
        long expected = (long) nums.length * (nums.length + 1) / 2;
        long actual = 0;
        for (int num : nums) actual += num;
        return (int) (expected - actual);
    }
}

class SolutionXor {
    public int missingNumber(int[] nums) {
        int result = nums.length;
        for (int i = 0; i < nums.length; i++) {
            result ^= i ^ nums[i];
        }
        return result;
    }
}

class SolutionBrute {
    public int maxSubArray(int[] nums) {
        int bestSum = nums[0];

        for (int start = 0; start < nums.length; start++) {
            int currentSum = 0;
            for (int end = start; end < nums.length; end++) {
                currentSum += nums[end];
                bestSum = Math.max(bestSum, currentSum);
            }
        }
        return bestSum;
    }
}

class Solution {
    public int maxSubArray(int[] nums) {
        int currentSum = nums[0];
        int bestSum = nums[0];

        for (int i = 1; i < nums.length; i++) {
            currentSum = Math.max(nums[i], currentSum + nums[i]);
            bestSum = Math.max(bestSum, currentSum);
        }
        return bestSum;
    }
}

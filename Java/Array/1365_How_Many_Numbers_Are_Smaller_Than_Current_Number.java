import java.util.Arrays;

class Solution {
    public int[] smallerNumbersThanCurrent(int[] nums) {
        int[] sorted = nums.clone();
        Arrays.sort(sorted);
        int[] result = new int[nums.length];

        for (int i = 0; i < nums.length; i++) {
            int index = 0;
            while (sorted[index] < nums[i]) {
                index++;
            }
            result[i] = index;
        }

        return result;
    }
}

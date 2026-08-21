import java.util.Arrays;
import java.util.TreeSet;

class SolutionBrute {
    public int removeDuplicates(int[] nums) {
        TreeSet<Integer> unique = new TreeSet<>();
        for (int num : nums) unique.add(num);

        int index = 0;
        for (int num : unique) nums[index++] = num;
        return unique.size();
    }
}

class Solution {
    public int removeDuplicates(int[] nums) {
        if (nums.length == 0) return 0;

        int write = 1;
        for (int read = 1; read < nums.length; read++) {
            if (nums[read] != nums[write - 1]) {
                nums[write++] = nums[read];
            }
        }
        return write;
    }
}

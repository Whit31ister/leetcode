import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

class SolutionBrute {
    public List<Integer> findDisappearedNumbers(int[] nums) {
        int[] sorted = nums.clone();
        java.util.Arrays.sort(sorted);
        List<Integer> result = new ArrayList<>();
        int expected = 1;

        for (int num : sorted) {
            while (num > expected) result.add(expected++);
            if (num == expected) expected++;
        }
        while (expected <= nums.length) result.add(expected++);
        return result;
    }
}

class Solution {
    public List<Integer> findDisappearedNumbers(int[] nums) {
        Set<Integer> present = new HashSet<>();
        for (int num : nums) present.add(num);

        List<Integer> result = new ArrayList<>();
        for (int value = 1; value <= nums.length; value++) {
            if (!present.contains(value)) result.add(value);
        }
        return result;
    }
}

class SolutionInPlace {
    public List<Integer> findDisappearedNumbers(int[] nums) {
        for (int num : nums) {
            int index = Math.abs(num) - 1;
            if (nums[index] > 0) nums[index] = -nums[index];
        }

        List<Integer> result = new ArrayList<>();
        for (int i = 0; i < nums.length; i++) {
            if (nums[i] > 0) result.add(i + 1);
        }
        return result;
    }
}

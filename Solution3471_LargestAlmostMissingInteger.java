// 3471. Find the Largest Almost Missing Integer
// https://leetcode.com/problems/find-the-largest-almost-missing-integer/

import java.util.*;

public class Solution3471_LargestAlmostMissingInteger {

    // ---------- Brute Force ----------
    static class SolutionBruteForce {
        public int largestInteger(int[] nums, int k) {
            int n = nums.length;
            Map<Integer, Integer> windowCount = new HashMap<>();

            for (int start = 0; start <= n - k; start++) {
                Set<Integer> distinctInWindow = new HashSet<>();
                for (int i = start; i < start + k; i++) distinctInWindow.add(nums[i]);
                for (int val : distinctInWindow) {
                    windowCount.put(val, windowCount.getOrDefault(val, 0) + 1);
                }
            }

            int best = -1;
            for (Map.Entry<Integer, Integer> e : windowCount.entrySet()) {
                if (e.getValue() == 1) best = Math.max(best, e.getKey());
            }
            return best;
        }
    }

    // ---------- Optimal: boundary-only check ----------
    static class SolutionOptimal {
        public int largestInteger(int[] nums, int k) {
            int n = nums.length;

            if (k == n) {
                int mx = nums[0];
                for (int x : nums) mx = Math.max(mx, x);
                return mx;
            }

            Map<Integer, Integer> count = new HashMap<>();
            for (int x : nums) count.put(x, count.getOrDefault(x, 0) + 1);

            if (k == 1) {
                int best = -1;
                for (int x : nums) {
                    if (count.get(x) == 1) best = Math.max(best, x);
                }
                return best;
            }

            int best = -1;
            if (count.get(nums[0]) == 1) best = Math.max(best, nums[0]);
            if (count.get(nums[n - 1]) == 1) best = Math.max(best, nums[n - 1]);
            return best;
        }
    }

    public static void main(String[] args) {
        SolutionOptimal s = new SolutionOptimal();
        System.out.println(s.largestInteger(new int[]{3,9,2,1,7}, 3)); // 7
        System.out.println(s.largestInteger(new int[]{3,9,7,2,1,7}, 4)); // 3
    }
}

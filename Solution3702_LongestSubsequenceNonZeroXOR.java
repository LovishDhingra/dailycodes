// 3702. Longest Subsequence With Non-Zero Bitwise XOR
// https://leetcode.com/problems/longest-subsequence-with-non-zero-bitwise-xor/

import java.util.*;

public class Solution3702_LongestSubsequenceNonZeroXOR {

    // ---------- Brute Force: enumerate all subsequences ----------
    static class SolutionBruteForce {
        public int longestSubsequence(int[] nums) {
            int n = nums.length;
            int best = 0;
            for (int mask = 1; mask < (1 << n); mask++) {
                int xorVal = 0, length = 0;
                for (int i = 0; i < n; i++) {
                    if ((mask & (1 << i)) != 0) {
                        xorVal ^= nums[i];
                        length++;
                    }
                }
                if (xorVal != 0) best = Math.max(best, length);
            }
            return best;
        }
    }

    // ---------- Optimal: XOR property observation ----------
    static class SolutionOptimal {
        public int longestSubsequence(int[] nums) {
            int n = nums.length;
            int xorVal = 0, countZero = 0;
            for (int x : nums) {
                xorVal ^= x;
                if (x == 0) countZero++;
            }

            if (xorVal != 0) return n;
            if (countZero == n) return 0;
            return n - 1;
        }
    }

    public static void main(String[] args) {
        SolutionOptimal s = new SolutionOptimal();
        System.out.println(s.longestSubsequence(new int[]{1,2,3}));   // 2
        System.out.println(s.longestSubsequence(new int[]{2,3,4}));   // 3
    }
}

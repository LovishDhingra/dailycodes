// 1563. Stone Game V
// https://leetcode.com/problems/stone-game-v/

import java.util.*;

public class Solution1563_StoneGameV {

    // ---------- Brute Force: Pure Recursion (no memoization) ----------
    static class SolutionBruteForce {
        int[] prefix;

        private int rangeSum(int i, int j) {
            return prefix[j + 1] - prefix[i];
        }

        private int solve(int i, int j) {
            if (i == j) return 0;
            int best = 0;
            for (int k = i; k < j; k++) {
                int leftSum = rangeSum(i, k);
                int rightSum = rangeSum(k + 1, j);
                int cand;
                if (leftSum < rightSum) cand = leftSum + solve(i, k);
                else if (leftSum > rightSum) cand = rightSum + solve(k + 1, j);
                else cand = leftSum + Math.max(solve(i, k), solve(k + 1, j));
                best = Math.max(best, cand);
            }
            return best;
        }

        public int stoneGameV(int[] stoneValue) {
            int n = stoneValue.length;
            prefix = new int[n + 1];
            for (int i = 0; i < n; i++) prefix[i + 1] = prefix[i] + stoneValue[i];
            return solve(0, n - 1);
        }
    }

    // ---------- Optimal: Top-Down Memoization ----------
    static class SolutionMemo {
        int[] prefix;
        int[][] memo;

        private int rangeSum(int i, int j) {
            return prefix[j + 1] - prefix[i];
        }

        private int solve(int i, int j) {
            if (i == j) return 0;
            if (memo[i][j] != -1) return memo[i][j];
            int best = 0;
            for (int k = i; k < j; k++) {
                int leftSum = rangeSum(i, k);
                int rightSum = rangeSum(k + 1, j);
                int cand;
                if (leftSum < rightSum) cand = leftSum + solve(i, k);
                else if (leftSum > rightSum) cand = rightSum + solve(k + 1, j);
                else cand = leftSum + Math.max(solve(i, k), solve(k + 1, j));
                best = Math.max(best, cand);
            }
            return memo[i][j] = best;
        }

        public int stoneGameV(int[] stoneValue) {
            int n = stoneValue.length;
            prefix = new int[n + 1];
            for (int i = 0; i < n; i++) prefix[i + 1] = prefix[i] + stoneValue[i];
            memo = new int[n][n];
            for (int[] row : memo) Arrays.fill(row, -1);
            return solve(0, n - 1);
        }
    }

    public static void main(String[] args) {
        SolutionMemo s = new SolutionMemo();
        System.out.println(s.stoneGameV(new int[]{6,2,3,4,5,5})); // 18 (official example)
    }
}

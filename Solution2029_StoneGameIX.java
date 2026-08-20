// 2029. Stone Game IX
// https://leetcode.com/problems/stone-game-ix/
//
// Key idea: only stone[i] % 3 matters. Bucket into c0, c1, c2.
//   if c0 is even: Alice wins iff c1 >= 1 AND c2 >= 1
//   if c0 is odd:  Alice wins iff |c1 - c2| > 2

import java.util.*;

public class Solution2029_StoneGameIX {

    // ---------- Brute Force: simulate all orderings (small n only) ----------
    static class SolutionBruteForce {
        public boolean stoneGameIX(int[] stones) {
            return simulate(stones, new ArrayList<>(), 0);
        }

        // returns true if the player about to move (given remaining stones and
        // current running sum) can force a WIN for themself
        private boolean simulate(int[] stones, List<Integer> used, long sum) {
            List<Integer> remaining = new ArrayList<>();
            for (int i = 0; i < stones.length; i++) if (!used.contains(i)) remaining.add(i);

            if (remaining.isEmpty()) return false; // draw, not a win for the mover

            for (int idx : remaining) {
                long newSum = sum + stones[idx];
                used.add(idx);
                if (newSum % 3 == 0) {
                    used.remove(Integer.valueOf(idx));
                    continue; // this move makes the mover LOSE immediately, skip
                }
                boolean opponentWins = simulate(stones, used, newSum);
                used.remove(Integer.valueOf(idx));
                if (!opponentWins) return true; // found a move that traps opponent
            }
            return false;
        }
    }

    // ---------- Optimal: remainder-bucket formula ----------
    static class SolutionOptimal {
        public boolean stoneGameIX(int[] stones) {
            int c0 = 0, c1 = 0, c2 = 0;
            for (int s : stones) {
                int r = s % 3;
                if (r == 0) c0++;
                else if (r == 1) c1++;
                else c2++;
            }

            if (c0 % 2 == 0) {
                return c1 >= 1 && c2 >= 1;
            } else {
                return Math.abs(c1 - c2) > 2;
            }
        }
    }

    public static void main(String[] args) {
        SolutionOptimal s = new SolutionOptimal();
        System.out.println(s.stoneGameIX(new int[]{2,1}));           // true
        System.out.println(s.stoneGameIX(new int[]{2}));             // false
        System.out.println(s.stoneGameIX(new int[]{5,1,2,4,3}));     // false
    }
}

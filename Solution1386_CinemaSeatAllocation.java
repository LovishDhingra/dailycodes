// 1386. Cinema Seat Allocation
// https://leetcode.com/problems/cinema-seat-allocation/

import java.util.*;

public class Solution1386_CinemaSeatAllocation {

    // ---------- Brute Force: iterate every row explicitly ----------
    static class SolutionBruteForce {
        public int maxNumberOfFamilies(int n, int[][] reservedSeats) {
            Map<Integer, Set<Integer>> rows = new HashMap<>();
            for (int[] rs : reservedSeats) {
                rows.computeIfAbsent(rs[0], k -> new HashSet<>()).add(rs[1]);
            }

            int total = 0;
            for (int r = 1; r <= n; r++) {
                boolean[] seats = new boolean[11];
                Set<Integer> occupied = rows.getOrDefault(r, Collections.emptySet());
                for (int s : occupied) seats[s] = true;

                boolean free25 = !seats[2] && !seats[3] && !seats[4] && !seats[5];
                boolean free47 = !seats[4] && !seats[5] && !seats[6] && !seats[7];
                boolean free69 = !seats[6] && !seats[7] && !seats[8] && !seats[9];

                if (free25 && free69) total += 2;
                else if (free25 || free47 || free69) total += 1;
            }
            return total;
        }
    }

    // ---------- Optimal: Bitmask + only process reserved rows ----------
    static class SolutionOptimal {
        public int maxNumberOfFamilies(int n, int[][] reservedSeats) {
            Map<Integer, Integer> rowMask = new HashMap<>();
            for (int[] rs : reservedSeats) {
                rowMask.merge(rs[0], 1 << rs[1], (a, b) -> a | b);
            }

            final int MASK_2_5 = 0b0000111100;
            final int MASK_4_7 = 0b0011110000; // bits for seats 4,5,6,7
            final int MASK_6_9 = 0b1111000000; // bits for seats 6,7,8,9

            long total = 2L * (n - rowMask.size());

            for (int mask : rowMask.values()) {
                boolean free25 = (mask & MASK_2_5) == 0;
                boolean free47 = (mask & MASK_4_7) == 0;
                boolean free69 = (mask & MASK_6_9) == 0;

                if (free25 && free69) total += 2;
                else if (free25 || free47 || free69) total += 1;
            }

            return (int) total;
        }
    }

    public static void main(String[] args) {
        SolutionOptimal s = new SolutionOptimal();
        int[][] reserved = {{1,2},{1,3},{1,8},{2,6},{3,1},{3,10}};
        System.out.println(s.maxNumberOfFamilies(3, reserved)); // 4
    }
}

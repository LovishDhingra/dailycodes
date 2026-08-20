// 3090. Maximum Length Substring With Two Occurrences
// https://leetcode.com/problems/maximum-length-substring-with-two-occurrences/

import java.util.*;

public class Solution3090_MaxLengthSubstringTwoOccurrences {

    // ---------- Brute Force ----------
    static class SolutionBruteForce {
        public int maximumLengthSubstring(String s) {
            int n = s.length();
            int best = 0;
            for (int i = 0; i < n; i++) {
                Map<Character, Integer> freq = new HashMap<>();
                for (int j = i; j < n; j++) {
                    char c = s.charAt(j);
                    freq.put(c, freq.getOrDefault(c, 0) + 1);
                    if (freq.get(c) > 2) break;
                    best = Math.max(best, j - i + 1);
                }
            }
            return best;
        }
    }

    // ---------- Optimal: Sliding Window (fixed 26-slot array) ----------
    static class SolutionOptimal {
        public int maximumLengthSubstring(String s) {
            int[] freq = new int[26];
            int left = 0;
            int best = 0;

            for (int right = 0; right < s.length(); right++) {
                int idx = s.charAt(right) - 'a';
                freq[idx]++;

                while (freq[idx] > 2) {
                    freq[s.charAt(left) - 'a']--;
                    left++;
                }

                best = Math.max(best, right - left + 1);
            }

            return best;
        }
    }

    public static void main(String[] args) {
        SolutionOptimal s = new SolutionOptimal();
        System.out.println(s.maximumLengthSubstring("bcbbbcba")); // 4
        System.out.println(s.maximumLengthSubstring("aaaa"));     // 2
    }
}

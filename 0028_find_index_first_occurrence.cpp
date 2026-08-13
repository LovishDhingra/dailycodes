// 28. Find the Index of the First Occurrence in a String
// https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/

#include <bits/stdc++.h>
using namespace std;

// ---------- Brute Force ----------
class SolutionBruteForce {
public:
    int strStr(string haystack, string needle) {
        int n = haystack.size(), m = needle.size();
        for (int i = 0; i <= n - m; i++) {
            if (haystack.substr(i, m) == needle) {
                return i;
            }
        }
        return -1;
    }
};

// ---------- Optimal: KMP (Knuth-Morris-Pratt) ----------
class SolutionKMP {
public:
    int strStr(string haystack, string needle) {
        int n = haystack.size(), m = needle.size();
        if (m == 0) return 0;

        vector<int> lps(m, 0);
        int length = 0, i = 1;
        while (i < m) {
            if (needle[i] == needle[length]) {
                length++;
                lps[i] = length;
                i++;
            } else if (length > 0) {
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }

        i = 0;
        int j = 0;
        while (i < n) {
            if (haystack[i] == needle[j]) {
                i++;
                j++;
                if (j == m) return i - j;
            } else if (j > 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }

        return -1;
    }
};

int main() {
    SolutionKMP s;
    cout << s.strStr("sadbutsad", "sad") << endl;  // 0
    cout << s.strStr("leetcode", "leeto") << endl; // -1
    return 0;
}

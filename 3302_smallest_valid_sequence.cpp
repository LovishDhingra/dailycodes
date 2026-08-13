// 3302. Find the Lexicographically Smallest Valid Sequence
// https://leetcode.com/problems/find-the-lexicographically-smallest-valid-sequence/
// NOTE: this is the CORRECTED version (see conversation - original had a bug
// where exact matches were incorrectly gated behind a feasibility check).

#include <bits/stdc++.h>
using namespace std;

// ---------- Brute Force: feasibility via unmemoized recursion ----------
class SolutionBruteForce {
public:
    string w1, w2;
    int n, m;

    bool canComplete(int i, int j, bool usedChange) {
        if (j == m) return true;
        if (i == n) return false;
        if (w1[i] == w2[j]) {
            if (canComplete(i + 1, j + 1, usedChange)) return true;
        } else {
            if (!usedChange && canComplete(i + 1, j + 1, true)) return true;
        }
        return canComplete(i + 1, j, usedChange);
    }

    vector<int> validSequence(string word1, string word2) {
        w1 = word1; w2 = word2;
        n = w1.size(); m = w2.size();
        vector<int> result;
        int i = 0; bool usedChange = false;
        for (int j = 0; j < m; j++) {
            bool found = false;
            while (i < n) {
                if (w1[i] == w2[j]) {
                    if (canComplete(i + 1, j + 1, usedChange)) {
                        result.push_back(i); i++; found = true; break;
                    }
                } else {
                    if (!usedChange && canComplete(i + 1, j + 1, true)) {
                        result.push_back(i); i++; usedChange = true; found = true; break;
                    }
                }
                i++;
            }
            if (!found) return {};
        }
        return result;
    }
};

// ---------- Optimal: Suffix Precompute + Greedy Two-Pointer (CORRECTED) ----------
class SolutionOptimal {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size(), m = word2.size();
        vector<int> suf(n + 1, 0);
        for (int i = n - 1; i >= 0; i--) {
            if (suf[i+1] < m && word1[i] == word2[m - 1 - suf[i+1]]) {
                suf[i] = suf[i+1] + 1;
            } else {
                suf[i] = suf[i+1];
            }
        }

        vector<int> result(m);
        int i = 0, j = 0;
        bool usedChange = false;

        while (i < n && j < m) {
            if (word1[i] == word2[j]) {
                // exact match: ALWAYS take immediately, no feasibility check needed
                result[j] = i;
                j++; i++;
            } else if (!usedChange && suf[i+1] >= m - 1 - j) {
                result[j] = i;
                j++; i++;
                usedChange = true;
            } else {
                i++;
            }
        }

        if (j < m) return {};
        return result;
    }
};

int main() {
    SolutionOptimal s;

    vector<int> r1 = s.validSequence("vbcca", "abc");
    for (int x : r1) cout << x << " "; cout << endl; // 0 1 2

    vector<int> r2 = s.validSequence("bacdc", "abc");
    for (int x : r2) cout << x << " "; cout << endl; // 1 2 4

    vector<int> r3 = s.validSequence("bbeigiibhjafjig", "iihhj");
    for (int x : r3) cout << x << " "; cout << endl; // 3 5 6 8 9

    return 0;
}

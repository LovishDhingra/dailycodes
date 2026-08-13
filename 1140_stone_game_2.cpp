// 1140. Stone Game II
// https://leetcode.com/problems/stone-game-ii/

#include <bits/stdc++.h>
using namespace std;

// ---------- Brute Force: Pure Recursion (no memoization) ----------
class SolutionBruteForce {
public:
    int n;
    vector<int> suffix;

    int solve(int i, int M) {
        if (2 * M >= n - i) return suffix[i];
        int best = 0;
        for (int X = 1; X <= 2 * M && i + X <= n; X++) {
            best = max(best, suffix[i] - solve(i + X, max(M, X)));
        }
        return best;
    }

    int stoneGameII(vector<int>& piles) {
        n = piles.size();
        suffix.assign(n + 1, 0);
        for (int i = n - 1; i >= 0; i--) suffix[i] = suffix[i + 1] + piles[i];
        return solve(0, 1);
    }
};

// ---------- Optimized: Top-Down Memoization ----------
class SolutionMemo {
public:
    int n;
    vector<int> suffix;
    vector<vector<int>> memo;

    int solve(int i, int M) {
        if (2 * M >= n - i) return suffix[i];
        if (memo[i][M] != -1) return memo[i][M];
        int best = 0;
        for (int X = 1; X <= 2 * M && i + X <= n; X++) {
            best = max(best, suffix[i] - solve(i + X, max(M, X)));
        }
        return memo[i][M] = best;
    }

    int stoneGameII(vector<int>& piles) {
        n = piles.size();
        suffix.assign(n + 1, 0);
        for (int i = n - 1; i >= 0; i--) suffix[i] = suffix[i + 1] + piles[i];
        memo.assign(n + 1, vector<int>(n + 1, -1));
        return solve(0, 1);
    }
};

// ---------- Optimized: Bottom-Up Tabulation ----------
class SolutionTabulation {
public:
    int stoneGameII(vector<int>& piles) {
        int n = piles.size();
        vector<int> suffix(n + 1, 0);
        for (int i = n - 1; i >= 0; i--) suffix[i] = suffix[i + 1] + piles[i];

        vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));

        for (int i = n; i >= 0; i--) {
            for (int M = n; M >= 1; M--) {
                if (2 * M >= n - i) {
                    dp[i][M] = suffix[i];
                } else {
                    for (int X = 1; X <= 2 * M && i + X <= n; X++) {
                        dp[i][M] = max(dp[i][M], suffix[i] - dp[i + X][max(M, X)]);
                    }
                }
            }
        }

        return dp[0][1];
    }
};

int main() {
    SolutionTabulation s;
    vector<int> piles = {2, 7, 9, 4, 4};
    cout << s.stoneGameII(piles) << endl; // 10
    return 0;
}

// 877. Stone Game
// https://leetcode.com/problems/stone-game/

#include <bits/stdc++.h>
using namespace std;

// ---------- Brute Force: Pure Recursion ----------
class SolutionBruteForce {
public:
    int solve(vector<int>& piles, int i, int j) {
        if (i == j) return piles[i];
        int takeLeft = piles[i] - solve(piles, i + 1, j);
        int takeRight = piles[j] - solve(piles, i, j - 1);
        return max(takeLeft, takeRight);
    }

    bool stoneGame(vector<int>& piles) {
        return solve(piles, 0, piles.size() - 1) > 0;
    }
};

// ---------- Optimized: Top-Down Memoization ----------
class SolutionMemo {
public:
    vector<vector<int>> memo;

    int solve(vector<int>& piles, int i, int j) {
        if (i == j) return piles[i];
        if (memo[i][j] != INT_MIN) return memo[i][j];
        int takeLeft = piles[i] - solve(piles, i + 1, j);
        int takeRight = piles[j] - solve(piles, i, j - 1);
        return memo[i][j] = max(takeLeft, takeRight);
    }

    bool stoneGame(vector<int>& piles) {
        int n = piles.size();
        memo.assign(n, vector<int>(n, INT_MIN));
        return solve(piles, 0, n - 1) > 0;
    }
};

// ---------- Optimized: Bottom-Up Tabulation ----------
class SolutionTabulation {
public:
    bool stoneGame(vector<int>& piles) {
        int n = piles.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));

        for (int i = 0; i < n; i++) dp[i][i] = piles[i];

        for (int length = 2; length <= n; length++) {
            for (int i = 0; i + length - 1 < n; i++) {
                int j = i + length - 1;
                int takeLeft = piles[i] - dp[i+1][j];
                int takeRight = piles[j] - dp[i][j-1];
                dp[i][j] = max(takeLeft, takeRight);
            }
        }

        return dp[0][n-1] > 0;
    }
};

// ---------- Optimal (given constraints): Math Shortcut ----------
class SolutionMathShortcut {
public:
    bool stoneGame(vector<int>& piles) {
        return true; // valid because n is always even and total sum is always odd
    }
};

int main() {
    SolutionTabulation s;
    vector<int> piles = {5, 3, 4, 5};
    cout << (s.stoneGame(piles) ? "true" : "false") << endl; // true
    return 0;
}

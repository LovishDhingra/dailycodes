// 1510. Stone Game IV
// https://leetcode.com/problems/stone-game-iv/

#include <bits/stdc++.h>
using namespace std;

// ---------- Brute Force: Pure Recursion ----------
class SolutionBruteForce {
public:
    bool canWin(int remaining) {
        if (remaining == 0) return false;
        for (int k = 1; k * k <= remaining; k++) {
            if (!canWin(remaining - k * k)) return true;
        }
        return false;
    }

    bool winnerSquareGame(int n) {
        return canWin(n);
    }
};

// ---------- Optimized: Top-Down Memoization ----------
class SolutionMemo {
public:
    vector<int> memo; // 0 = unknown, 1 = true, -1 = false

    bool canWin(int remaining) {
        if (remaining == 0) return false;
        if (memo[remaining] != 0) return memo[remaining] == 1;
        bool result = false;
        for (int k = 1; k * k <= remaining; k++) {
            if (!canWin(remaining - k * k)) {
                result = true;
                break;
            }
        }
        memo[remaining] = result ? 1 : -1;
        return result;
    }

    bool winnerSquareGame(int n) {
        memo.assign(n + 1, 0);
        return canWin(n);
    }
};

// ---------- Optimized: Bottom-Up Tabulation ----------
class SolutionTabulation {
public:
    bool winnerSquareGame(int n) {
        vector<bool> dp(n + 1, false);
        for (int i = 1; i <= n; i++) {
            for (int k = 1; k * k <= i; k++) {
                if (!dp[i - k * k]) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[n];
    }
};

int main() {
    SolutionTabulation s;
    cout << (s.winnerSquareGame(4) ? "true" : "false") << endl; // true
    cout << (s.winnerSquareGame(2) ? "true" : "false") << endl; // false
    cout << (s.winnerSquareGame(6) ? "true" : "false") << endl; // true
    return 0;
}

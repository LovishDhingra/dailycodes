// 4010. Maximize Pair Strength Using GCD
// https://leetcode.com/problems/maximize-pair-strength-using-gcd/

#include <bits/stdc++.h>
using namespace std;

// ---------- Brute Force: naive GCD (no Euclidean algorithm) ----------
class SolutionBruteForce {
public:
    int naiveGcd(int a, int b) {
        for (int d = min(a, b); d >= 1; d--) {
            if (a % d == 0 && b % d == 0) return d;
        }
        return 1;
    }

    long long maxStrength(vector<int>& nums) {
        int n = nums.size();
        long long best = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int g = naiveGcd(nums[i], nums[j]);
                long long strength = (long long)nums[i] * nums[j] / ((long long)g * g);
                best = max(best, strength);
            }
        }
        return best;
    }
};

// ---------- Optimal: All Pairs + Euclidean GCD ----------
class SolutionOptimal {
public:
    long long maxStrength(vector<int>& nums) {
        int n = nums.size();
        long long best = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int g = __gcd(nums[i], nums[j]);
                long long strength = (long long)nums[i] * nums[j] / ((long long)g * g);
                best = max(best, strength);
            }
        }
        return best;
    }
};

int main() {
    SolutionOptimal s;
    vector<int> nums = {4, 6, 8};
    cout << s.maxStrength(nums) << endl; // 12
    return 0;
}

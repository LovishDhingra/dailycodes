// 3403. Smallest Palindromic Rearrangement I
// https://leetcode.com/problems/smallest-palindromic-rearrangement-i/

#include <bits/stdc++.h>
using namespace std;

// ---------- Brute Force ----------
class SolutionBruteForce {
public:
    string smallestPalindrome(string s) {
        sort(s.begin(), s.end());
        string best = "";
        bool found = false;
        string current = s;
        do {
            string rev = current;
            reverse(rev.begin(), rev.end());
            if (current == rev) {
                if (!found || current < best) {
                    best = current;
                    found = true;
                }
            }
        } while (next_permutation(current.begin(), current.end()));
        return best;
    }
};

// ---------- Optimal: Greedy counting ----------
class SolutionOptimal {
public:
    string smallestPalindrome(string s) {
        vector<int> count(26, 0);
        for (char ch : s) count[ch - 'a']++;

        string left = "";
        char mid = 0;
        for (int i = 0; i < 26; i++) {
            left += string(count[i] / 2, 'a' + i);
            if (count[i] % 2 == 1) mid = 'a' + i;
        }

        string right = left;
        reverse(right.begin(), right.end());

        string result = left;
        if (mid != 0) result += mid;
        result += right;
        return result;
    }
};

int main() {
    SolutionOptimal s;
    cout << s.smallestPalindrome("babab") << endl;   // abbba
    cout << s.smallestPalindrome("daccad") << endl;  // acddca
    return 0;
}

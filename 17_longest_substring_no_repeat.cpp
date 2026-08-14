// Problem: Longest Substring Without Repeating Characters
// Approach: Sliding window with a hashmap tracking last-seen index of chars.
// Time: O(n)   Space: O(min(n, charset size))

#include <bits/stdc++.h>
using namespace std;

int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> lastSeen;
    int maxLen = 0;
    int windowStart = 0;

    for (int i = 0; i < (int)s.size(); i++) {
        char c = s[i];
        if (lastSeen.count(c) && lastSeen[c] >= windowStart) {
            windowStart = lastSeen[c] + 1;
        }
        lastSeen[c] = i;
        maxLen = max(maxLen, i - windowStart + 1);
    }
    return maxLen;
}

int main() {
    cout << lengthOfLongestSubstring("abcabcbb") << endl; // 3
    cout << lengthOfLongestSubstring("bbbbb") << endl;     // 1
    cout << lengthOfLongestSubstring("pwwkew") << endl;    // 3
    return 0;
}

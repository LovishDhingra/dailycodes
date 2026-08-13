// 2958. Length of Longest Subarray With at Most K Frequency
// https://leetcode.com/problems/length-of-longest-subarray-with-at-most-k-frequency/

#include <bits/stdc++.h>
using namespace std;

// ---------- Brute Force ----------
class SolutionBruteForce {
public:
    int maxSubarrayLength(vector<int>& nums, int k) {
        int n = nums.size();
        int best = 0;
        for (int i = 0; i < n; i++) {
            unordered_map<int, int> freq;
            for (int j = i; j < n; j++) {
                freq[nums[j]]++;
                if (freq[nums[j]] > k) break;
                best = max(best, j - i + 1);
            }
        }
        return best;
    }
};

// ---------- Optimal: Sliding Window ----------
class SolutionSlidingWindow {
public:
    int maxSubarrayLength(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        int left = 0;
        int best = 0;

        for (int right = 0; right < (int)nums.size(); right++) {
            freq[nums[right]]++;

            while (freq[nums[right]] > k) {
                freq[nums[left]]--;
                left++;
            }

            best = max(best, right - left + 1);
        }

        return best;
    }
};

int main() {
    SolutionSlidingWindow s;
    vector<int> nums = {1,2,3,1,2,3,1,2};
    cout << s.maxSubarrayLength(nums, 2) << endl; // 6
    return 0;
}

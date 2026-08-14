// Problem: Two Sum
// Given an array of integers and a target, return indices of the two
// numbers such that they add up to target.
// Approach: Single-pass hashmap storing value -> index.
// Time: O(n)   Space: O(n)

#include <bits/stdc++.h>
using namespace std;

vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> seen; // value -> index
    for (int i = 0; i < (int)nums.size(); i++) {
        int need = target - nums[i];
        if (seen.count(need)) return {seen[need], i};
        seen[nums[i]] = i;
    }
    return {-1, -1}; // no solution
}

int main() {
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;
    auto res = twoSum(nums, target);
    cout << "Indices: " << res[0] << ", " << res[1] << endl;
    return 0;
}

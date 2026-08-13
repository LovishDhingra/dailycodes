// 2996. Smallest Missing Integer Greater Than Sequential Prefix Sum
// https://leetcode.com/problems/smallest-missing-integer-greater-than-sequential-prefix-sum/

#include <bits/stdc++.h>
using namespace std;

// ---------- Brute Force ----------
class SolutionBruteForce {
public:
    int missingInteger(vector<int>& nums) {
        int i = 1;
        while (i < (int)nums.size() && nums[i] == nums[i-1] + 1) i++;

        int target = 0;
        for (int j = 0; j < i; j++) target += nums[j];

        while (true) {
            bool found = false;
            for (int x : nums) {
                if (x == target) { found = true; break; }
            }
            if (!found) return target;
            target++;
        }
    }
};

// ---------- Optimal 1: HashSet Membership ----------
class SolutionHashSet {
public:
    int missingInteger(vector<int>& nums) {
        int i = 1;
        while (i < (int)nums.size() && nums[i] == nums[i-1] + 1) i++;

        int target = 0;
        for (int j = 0; j < i; j++) target += nums[j];

        unordered_set<int> present(nums.begin(), nums.end());
        while (present.count(target)) target++;

        return target;
    }
};

// ---------- Optimal 2: Fixed-Size Boolean Array ----------
class SolutionBoolArray {
public:
    int missingInteger(vector<int>& nums) {
        int i = 1;
        while (i < (int)nums.size() && nums[i] == nums[i-1] + 1) i++;

        int target = 0;
        for (int j = 0; j < i; j++) target += nums[j];

        vector<bool> present(200, false); // safely covers max possible target + values
        for (int x : nums) present[x] = true;

        while (target < 200 && present[target]) target++;

        return target;
    }
};

// ---------- Optimal 3: Sort + Two-Pointer Walk ----------
class SolutionSortTwoPointer {
public:
    int missingInteger(vector<int>& nums) {
        int i = 1;
        while (i < (int)nums.size() && nums[i] == nums[i-1] + 1) i++;

        int target = 0;
        for (int j = 0; j < i; j++) target += nums[j];

        vector<int> sorted_nums = nums;
        sort(sorted_nums.begin(), sorted_nums.end());

        int p = 0;
        while (p < (int)sorted_nums.size()) {
            if (sorted_nums[p] == target) {
                target++;
                p++;
            } else if (sorted_nums[p] < target) {
                p++;
            } else {
                break;
            }
        }

        return target;
    }
};

int main() {
    SolutionHashSet s;
    vector<int> nums = {3,4,5,1,12,14,13};
    cout << s.missingInteger(nums) << endl; // 15
    return 0;
}

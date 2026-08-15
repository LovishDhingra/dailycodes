// Problem: Merge Intervals
// Given a list of intervals, merge all overlapping intervals.
// Approach: Sort by start time, then sweep and merge overlapping ranges.
// Time: O(n log n)   Space: O(n)

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> merge(vector<vector<int>>& intervals) {
    if (intervals.empty()) return {};
    sort(intervals.begin(), intervals.end());

    vector<vector<int>> result;
    result.push_back(intervals[0]);

    for (int i = 1; i < (int)intervals.size(); i++) {
        if (intervals[i][0] <= result.back()[1]) {
            result.back()[1] = max(result.back()[1], intervals[i][1]);
        } else {
            result.push_back(intervals[i]);
        }
    }
    return result;
}

int main() {
    vector<vector<int>> intervals = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
    auto merged = merge(intervals);
    for (auto& iv : merged) cout << "[" << iv[0] << "," << iv[1] << "] ";
    cout << endl;
    return 0;
}

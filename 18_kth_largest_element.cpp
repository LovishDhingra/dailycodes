// Problem: Kth Largest Element in an Array
// Approach: Maintain a min-heap of size k; the heap top is the kth largest.
// Time: O(n log k)   Space: O(k)

#include <bits/stdc++.h>
using namespace std;

int findKthLargest(vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> minHeap; // min-heap

    for (int num : nums) {
        minHeap.push(num);
        if ((int)minHeap.size() > k) minHeap.pop();
    }
    return minHeap.top();
}

int main() {
    vector<int> nums = {3, 2, 1, 5, 6, 4};
    int k = 2;
    cout << "Kth largest: " << findKthLargest(nums, k) << endl; // expected 5
    return 0;
}

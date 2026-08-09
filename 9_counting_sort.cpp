#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Counting Sort: O(n + k) where k = max element
// Space: O(k), Stable: YES (with modification)
// Best for: Non-negative integers with small range
// Use when: k (range) << n (array size)
void countingSort(vector<int>& arr) {
    if (arr.empty()) return;
    
    // Find maximum element
    int maxVal = *max_element(arr.begin(), arr.end());
    
    // Create count array
    vector<int> count(maxVal + 1, 0);
    
    // Count occurrences of each element
    for (int num : arr) {
        count[num]++;
    }
    
    // Reconstruct sorted array
    int idx = 0;
    for (int i = 0; i <= maxVal; i++) {
        while (count[i] > 0) {
            arr[idx++] = i;
            count[i]--;
        }
    }
}

void printArray(vector<int>& arr) {
    for (int x : arr) cout << x << " ";
    cout << endl;
}

int main() {
    vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    
    cout << "Original: ";
    printArray(arr);
    
    countingSort(arr);
    
    cout << "Sorted: ";
    printArray(arr);
    
    // Example with duplicates
    vector<int> arr2 = {5, 2, 8, 2, 9, 1, 5, 5};
    cout << "\nWith duplicates: ";
    printArray(arr2);
    countingSort(arr2);
    cout << "Sorted: ";
    printArray(arr2);
    
    return 0;
}

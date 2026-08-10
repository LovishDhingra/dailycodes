#include <iostream>
#include <vector>
using namespace std;

// Binary Search (Iterative): O(log n) time, O(1) space
// Requires SORTED array
int binarySearch(vector<int>& arr, int target) {
    int low = 0, high = arr.size() - 1;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

// Binary Search (Recursive)
int binarySearchRecursive(vector<int>& arr, int target, int low, int high) {
    if (low > high) return -1;
    
    int mid = low + (high - low) / 2;
    if (arr[mid] == target) return mid;
    else if (arr[mid] < target) return binarySearchRecursive(arr, target, mid + 1, high);
    else return binarySearchRecursive(arr, target, low, mid - 1);
}

int main() {
    vector<int> arr = {11, 12, 22, 25, 34, 64, 90};
    int target = 25;
    
    int result1 = binarySearch(arr, target);
    int result2 = binarySearchRecursive(arr, target, 0, arr.size() - 1);
    
    cout << "Binary Search (Iterative): " << result1 << endl;
    cout << "Binary Search (Recursive): " << result2 << endl;
    
    return 0;
}

#include <iostream>
#include <vector>
using namespace std;

// Heap Sort: O(n log n) all cases
// Space: O(1), Stable: NO
// Best for: Guaranteed O(n log n), in-place
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    // Find largest among root, left child, right child
    if (left < n && arr[left] > arr[largest])
        largest = left;
    
    if (right < n && arr[right] > arr[largest])
        largest = right;
    
    // If largest is not root, swap and heapify
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();
    
    // Build max heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    
    // Extract elements from heap one by one
    for (int i = n - 1; i > 0; i--) {
        // Move current root (max) to end
        swap(arr[0], arr[i]);
        // Heapify reduced heap
        heapify(arr, i, 0);
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
    
    heapSort(arr);
    
    cout << "Sorted: ";
    printArray(arr);
    
    return 0;
}

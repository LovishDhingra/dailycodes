#include <iostream>
#include <vector>
using namespace std;

// Bubble Sort (Optimized): O(n²) worst/avg, O(n) best
// Space: O(1), Stable: YES
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    
    for (int i = 0; i < n; i++) {
        bool swapped = false;
        
        // Last i elements are already in place
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        
        // If no swaps, array is sorted
        if (!swapped) break;
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
    
    bubbleSort(arr);
    
    cout << "Sorted: ";
    printArray(arr);
    
    return 0;
}

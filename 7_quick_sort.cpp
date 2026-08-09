#include <iostream>
#include <vector>
using namespace std;

// Quick Sort: O(n log n) avg, O(n²) worst
// Space: O(log n), Stable: NO
// Best for: FASTEST average case, default choice
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    // Partition: elements < pivot on left, > pivot on right
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
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
    
    quickSort(arr, 0, arr.size() - 1);
    
    cout << "Sorted: ";
    printArray(arr);
    
    return 0;
}

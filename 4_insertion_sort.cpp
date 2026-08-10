#include <iostream>
#include <vector>
using namespace std;

// Insertion Sort: O(n²) worst/avg, O(n) best
// Space: O(1), Stable: YES
// Best for: Nearly sorted data, online sorting
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        
        // Shift elements greater than key one position ahead
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        
        arr[j + 1] = key;
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
    
    insertionSort(arr);
    
    cout << "Sorted: ";
    printArray(arr);
    
    return 0;
}

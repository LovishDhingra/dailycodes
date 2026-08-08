# QuickSort - Complete Implementation Guide

## Concept
QuickSort is a **divide-and-conquer** sorting algorithm that works by:
1. Selecting a **pivot** element
2. **Partitioning** the array so elements < pivot are left, elements > pivot are right
3. **Recursively** sorting the left and right sub-arrays

## Complexity Analysis
| Aspect | Time | Space |
|--------|------|-------|
| Best Case | O(n log n) | O(log n) - call stack |
| Average Case | O(n log n) | O(log n) |
| Worst Case | O(n²) | O(log n) |
| Space | - | O(log n) - recursive stack |

---

## Approach 1: BRUTE FORCE (Simple but Extra Space)

### Concept
Create separate arrays for elements smaller, equal, and greater than pivot.

### C++ Implementation
```cpp
#include <iostream>
#include <vector>
using namespace std;

vector<int> quickSortBruteForce(vector<int> arr) {
    if (arr.size() <= 1) return arr;
    
    int pivot = arr[0];
    vector<int> left, middle, right;
    
    for (int num : arr) {
        if (num < pivot) left.push_back(num);
        else if (num == pivot) middle.push_back(num);
        else right.push_back(num);
    }
    
    vector<int> result;
    auto leftSorted = quickSortBruteForce(left);
    auto rightSorted = quickSortBruteForce(right);
    
    result.insert(result.end(), leftSorted.begin(), leftSorted.end());
    result.insert(result.end(), middle.begin(), middle.end());
    result.insert(result.end(), rightSorted.begin(), rightSorted.end());
    
    return result;
}

int main() {
    vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    auto result = quickSortBruteForce(arr);
    
    for (int x : result) cout << x << " ";
    cout << endl;
    
    return 0;
}
```

### Java Implementation
```java
import java.util.*;

public class QuickSortBruteForce {
    static List<Integer> quickSortBruteForce(List<Integer> arr) {
        if (arr.size() <= 1) return arr;
        
        int pivot = arr.get(0);
        List<Integer> left = new ArrayList<>();
        List<Integer> middle = new ArrayList<>();
        List<Integer> right = new ArrayList<>();
        
        for (int num : arr) {
            if (num < pivot) left.add(num);
            else if (num == pivot) middle.add(num);
            else right.add(num);
        }
        
        List<Integer> result = new ArrayList<>();
        result.addAll(quickSortBruteForce(left));
        result.addAll(middle);
        result.addAll(quickSortBruteForce(right));
        
        return result;
    }
    
    public static void main(String[] args) {
        List<Integer> arr = Arrays.asList(64, 34, 25, 12, 22, 11, 90);
        System.out.println(quickSortBruteForce(arr));
    }
}
```

### Python Implementation
```python
def quicksort_bruteforce(arr):
    if len(arr) <= 1:
        return arr
    
    pivot = arr[0]
    left = [x for x in arr if x < pivot]
    middle = [x for x in arr if x == pivot]
    right = [x for x in arr if x > pivot]
    
    return quicksort_bruteforce(left) + middle + quicksort_bruteforce(right)

arr = [64, 34, 25, 12, 22, 11, 90]
print(quicksort_bruteforce(arr))
```

**Pros:** Simple, easy to understand  
**Cons:** O(n) extra space, inefficient memory usage

---

## Approach 2: OPTIMIZED (In-Place Partitioning)

### Concept
Use **Lomuto** or **Hoare** partition scheme to partition in-place, then recursively sort.

### C++ Implementation (Lomuto Partition)
```cpp
#include <iostream>
#include <vector>
using namespace std;

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
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

int main() {
    vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    quickSort(arr, 0, arr.size() - 1);
    
    for (int x : arr) cout << x << " ";
    cout << endl;
    
    return 0;
}
```

### Java Implementation (Lomuto Partition)
```java
public class QuickSortOptimized {
    static int partition(int[] arr, int low, int high) {
        int pivot = arr[high];
        int i = low - 1;
        
        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                // Swap
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        // Swap pivot to correct position
        int temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;
        return i + 1;
    }
    
    static void quickSort(int[] arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }
    
    public static void main(String[] args) {
        int[] arr = {64, 34, 25, 12, 22, 11, 90};
        quickSort(arr, 0, arr.length - 1);
        
        for (int x : arr) System.out.print(x + " ");
        System.out.println();
    }
}
```

### Python Implementation (Lomuto Partition)
```python
def partition(arr, low, high):
    pivot = arr[high]
    i = low - 1
    
    for j in range(low, high):
        if arr[j] < pivot:
            i += 1
            arr[i], arr[j] = arr[j], arr[i]
    
    arr[i + 1], arr[high] = arr[high], arr[i + 1]
    return i + 1

def quicksort(arr, low, high):
    if low < high:
        pi = partition(arr, low, high)
        quicksort(arr, low, pi - 1)
        quicksort(arr, pi + 1, high)

arr = [64, 34, 25, 12, 22, 11, 90]
quicksort(arr, 0, len(arr) - 1)
print(arr)
```

---

## DRY RUN (Optimized In-Place QuickSort)

### Example Array: [64, 34, 25, 12, 22, 11, 90]

```
Initial: [64, 34, 25, 12, 22, 11, 90]
Pivot = 90 (last element)

Partition Pass 1:
i = -1
j=0: 64 < 90? YES → i=0, swap(arr[0], arr[0]) → [64, 34, 25, 12, 22, 11, 90]
j=1: 34 < 90? YES → i=1, swap(arr[1], arr[1]) → [64, 34, 25, 12, 22, 11, 90]
j=2: 25 < 90? YES → i=2, swap(arr[2], arr[2]) → [64, 34, 25, 12, 22, 11, 90]
j=3: 12 < 90? YES → i=3, swap(arr[3], arr[3]) → [64, 34, 25, 12, 22, 11, 90]
j=4: 22 < 90? YES → i=4, swap(arr[4], arr[4]) → [64, 34, 25, 12, 22, 11, 90]
j=5: 11 < 90? YES → i=5, swap(arr[5], arr[5]) → [64, 34, 25, 12, 22, 11, 90]
Final pivot position: i+1 = 6, swap(arr[6], arr[6]) → [64, 34, 25, 12, 22, 11, 90]
After partition: [64, 34, 25, 12, 22, 11, 90] (pivot at index 6)

Left subarray: [64, 34, 25, 12, 22, 11] (indices 0-5)
Right subarray: [] (nothing after pivot)

Recursively sort left [64, 34, 25, 12, 22, 11]:
Pivot = 11

Partition Pass 2:
i = -1
j=0: 64 < 11? NO
j=1: 34 < 11? NO
j=2: 25 < 11? NO
j=3: 12 < 11? NO
j=4: 22 < 11? NO
Final: i+1 = 0, swap(arr[0], arr[5]) → [11, 34, 25, 12, 22, 64, 90]
Pivot position: 0

Left: [] (nothing before pivot)
Right: [34, 25, 12, 22, 64]

Continue sorting right [34, 25, 12, 22, 64]:
Pivot = 64
After partition: [34, 25, 12, 22, 64]
Pivot at index 4

Left: [34, 25, 12, 22]
... (continue recursively)

Final: [11, 12, 22, 25, 34, 64, 90]
```

---

## Hoare Partition (Alternative)

### C++ Implementation
```cpp
int partitionHoare(vector<int>& arr, int low, int high) {
    int pivot = arr[low];
    int i = low - 1, j = high + 1;
    
    while (true) {
        do {
            i++;
        } while (arr[i] < pivot);
        
        do {
            j--;
        } while (arr[j] > pivot);
        
        if (i >= j) return j;
        swap(arr[i], arr[j]);
    }
}

void quickSortHoare(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partitionHoare(arr, low, high);
        quickSortHoare(arr, low, pi);
        quickSortHoare(arr, pi + 1, high);
    }
}
```

**Hoare Advantage:** Fewer swaps on average (3x less than Lomuto)

---

## Key Points

✅ **In-place sorting** - O(log n) space for recursion stack  
✅ **Average O(n log n)** - Very fast in practice  
✅ **Not stable** - Relative order of equal elements may change  
✅ **Cache-friendly** - Good locality of reference  
⚠️ **Worst case O(n²)** - Can happen with poor pivot selection  

### Pivot Selection Strategies
1. **First/Last element** - Simple but risky (worst case on sorted arrays)
2. **Random pivot** - Good average case, randomized guarantee
3. **Median-of-three** - Pick median of first, middle, last (reduces worst case)
4. **Randomized median-of-three** - Best practical choice

---

## Output
```
Brute Force: 11 12 22 25 34 64 90
Optimized: 11 12 22 25 34 64 90
```

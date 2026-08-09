# DSA QUICK REFERENCE - INTERVIEW CHEAT SHEET

## 🔍 SEARCHING TEMPLATES

### Linear Search (Unordered Array)
**Copy-Paste Time: 10 seconds | Use: Finding first/all occurrences**

**C++**
```cpp
int linearSearch(vector<int>& arr, int target) {
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == target) return i;
    }
    return -1;
}
```

**Java**
```java
static int linearSearch(int[] arr, int target) {
    for (int i = 0; i < arr.length; i++) {
        if (arr[i] == target) return i;
    }
    return -1;
}
```

**Python**
```python
def linear_search(arr, target):
    for i in range(len(arr)):
        if arr[i] == target:
            return i
    return -1
```

---

### Binary Search Iterative (Sorted Array)
**Copy-Paste Time: 15 seconds | Use: Finding element in sorted array**

**C++**
```cpp
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
```

**Java**
```java
static int binarySearch(int[] arr, int target) {
    int low = 0, high = arr.length - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}
```

**Python**
```python
def binary_search(arr, target):
    low, high = 0, len(arr) - 1
    while low <= high:
        mid = (low + high) // 2
        if arr[mid] == target:
            return mid
        elif arr[mid] < target:
            low = mid + 1
        else:
            high = mid - 1
    return -1
```

---

## 🔄 SORTING TEMPLATES

### Bubble Sort (Simple, Optimized)
**Copy-Paste Time: 20 seconds | Use: Small arrays, nearly-sorted data**

**C++**
```cpp
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}
```

**Java**
```java
static void bubbleSort(int[] arr) {
    int n = arr.length;
    for (int i = 0; i < n; i++) {
        boolean swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}
```

---

### Insertion Sort
**Copy-Paste Time: 20 seconds | Use: Nearly-sorted data, online sorting**

**C++**
```cpp
void insertionSort(vector<int>& arr) {
    for (int i = 1; i < arr.size(); i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
```

**Java**
```java
static void insertionSort(int[] arr) {
    for (int i = 1; i < arr.length; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
```

---

### Selection Sort
**Copy-Paste Time: 20 seconds | Use: Minimal swaps, small arrays**

**C++**
```cpp
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) minIdx = j;
        }
        if (minIdx != i) swap(arr[i], arr[minIdx]);
    }
}
```

---

### Merge Sort
**Copy-Paste Time: 45 seconds | Use: Guaranteed O(n log n), stable, linked lists**

**C++**
```cpp
void merge(vector<int>& arr, int low, int mid, int high) {
    vector<int> left(arr.begin() + low, arr.begin() + mid + 1);
    vector<int> right(arr.begin() + mid + 1, arr.begin() + high + 1);
    
    int i = 0, j = 0, k = low;
    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j]) arr[k++] = left[i++];
        else arr[k++] = right[j++];
    }
    while (i < left.size()) arr[k++] = left[i++];
    while (j < right.size()) arr[k++] = right[j++];
}

void mergeSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}
```

**Java**
```java
static void merge(int[] arr, int low, int mid, int high) {
    int[] left = new int[mid - low + 1];
    int[] right = new int[high - mid];
    
    System.arraycopy(arr, low, left, 0, mid - low + 1);
    System.arraycopy(arr, mid + 1, right, 0, high - mid);
    
    int i = 0, j = 0, k = low;
    while (i < left.length && j < right.length) {
        if (left[i] <= right[j]) arr[k++] = left[i++];
        else arr[k++] = right[j++];
    }
    while (i < left.length) arr[k++] = left[i++];
    while (j < right.length) arr[k++] = right[j++];
}

static void mergeSort(int[] arr, int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}
```

---

### Quick Sort (Most Important!)
**Copy-Paste Time: 30 seconds | Use: Fastest average O(n log n), in-place**

**C++**
```cpp
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
```

**Java**
```java
static int partition(int[] arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i]; arr[i] = arr[j]; arr[j] = temp;
        }
    }
    int temp = arr[i + 1]; arr[i + 1] = arr[high]; arr[high] = temp;
    return i + 1;
}

static void quickSort(int[] arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
```

---

### Heap Sort
**Copy-Paste Time: 40 seconds | Use: Guaranteed O(n log n), in-place**

**C++**
```cpp
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1, right = 2 * i + 2;
    
    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;
    
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}
```

---

### Counting Sort (For small range)
**Copy-Paste Time: 25 seconds | Use: Non-negative integers, small range**

**C++**
```cpp
void countingSort(vector<int>& arr) {
    if (arr.empty()) return;
    int maxVal = *max_element(arr.begin(), arr.end());
    vector<int> count(maxVal + 1, 0);
    
    for (int num : arr) count[num]++;
    
    int idx = 0;
    for (int i = 0; i <= maxVal; i++) {
        while (count[i] > 0) {
            arr[idx++] = i;
            count[i]--;
        }
    }
}
```

---

### Radix Sort (For multi-digit numbers)
**Copy-Paste Time: 40 seconds | Use: Multi-digit numbers**

**C++**
```cpp
void countingSortForRadix(vector<int>& arr, int exp) {
    vector<int> output(arr.size());
    vector<int> count(10, 0);
    
    for (int num : arr) count[(num / exp) % 10]++;
    for (int i = 1; i < 10; i++) count[i] += count[i - 1];
    
    for (int i = arr.size() - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }
    
    for (int i = 0; i < arr.size(); i++) arr[i] = output[i];
}

void radixSort(vector<int>& arr) {
    if (arr.empty()) return;
    int maxVal = *max_element(arr.begin(), arr.end());
    
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        countingSortForRadix(arr, exp);
    }
}
```

---

## 🎯 WHEN TO USE WHICH ALGORITHM

```
Question: What's the data size?

Small (< 50):
  → INSERTION SORT or BUBBLE SORT (simple, fast enough)

Medium (50-1000):
  → QUICK SORT (fast, in-place)
  → INSERTION SORT (if nearly sorted)

Large (> 1000):
  → Must have O(n log n):
     ✓ QUICK SORT (fastest average)
     ✓ MERGE SORT (guaranteed, stable)
     ✓ HEAP SORT (guaranteed, in-place)

Sorted Array:
  → BINARY SEARCH (O(log n))

Searching General:
  → LINEAR SEARCH (O(n))

Small Range Values (0-100):
  → COUNTING SORT (O(n + k), faster!)

Many Digits (large numbers):
  → RADIX SORT (O(n * d))

Must be Stable:
  → MERGE SORT
  → COUNTING SORT
  → INSERTION SORT (on small)

Must be In-Place:
  → QUICK SORT
  → HEAP SORT
  → SELECTION SORT
```

---

## ⚡ INTERVIEW PREPARATION CHECKLIST

### Before Coding (1 minute)
- [ ] Ask: "Is array sorted?"
- [ ] Ask: "Can elements be negative?"
- [ ] Ask: "Does order of equal elements matter? (stability)"
- [ ] Ask: "Space constraints?"
- [ ] Ask: "Time constraints?"

### During Coding (5 minutes)
- [ ] Write pseudocode first
- [ ] Choose optimal algorithm based on constraints
- [ ] Handle edge cases:
  - Empty array
  - Single element
  - Two elements
  - All same elements
  - Already sorted
- [ ] Use correct swap/partition logic
- [ ] Off-by-one error checks

### After Coding (2 minutes)
- [ ] Trace through with example
- [ ] Verify time/space complexity
- [ ] Check edge cases work
- [ ] Ask: "Can this be optimized?"

---

## 🔥 MOST COMMON INTERVIEW MISTAKES

| Mistake | Fix |
|---------|-----|
| Off-by-one in loop | Use `i < n` not `i <= n` for length n |
| Wrong mid calculation | Use `mid = low + (high - low) / 2` (avoid overflow) |
| Forgetting base case | Check `if (low == high)` or `if (arr.empty())` |
| Stability confusion | Bubble/Insertion/Merge are stable; Selection/Quick/Heap are NOT |
| Space analysis | Count extra arrays (merge sort O(n)), recursion stack (O(log n)) |
| Worst case ignorance | Quick sort can be O(n²), randomize pivot! |
| Not testing edge cases | Always test empty, size 1, duplicates |

---

## ✅ QUICK VALIDATION

Test every algorithm with:
```
arr = [64, 34, 25, 12, 22, 11, 90]
Expected: [11, 12, 22, 25, 34, 64, 90]

arr = [1]           // Single element
arr = []            // Empty
arr = [5, 5, 5, 5]  // All duplicates
arr = [1, 2, 3]     // Already sorted
arr = [3, 2, 1]     // Reverse sorted
```

---

## 📊 ALGORITHM SELECTION QUICK MATRIX

|  | Time | Space | Stable | In-Place | Use Case |
|---|------|-------|--------|----------|----------|
| Linear | O(n) | O(1) | - | ✓ | Unsorted, small |
| Binary | O(log n) | O(1) | - | ✓ | Sorted, large |
| Bubble | O(n²) | O(1) | ✓ | ✓ | Learning only |
| Insert | O(n²) | O(1) | ✓ | ✓ | Nearly sorted |
| Select | O(n²) | O(1) | ✗ | ✓ | Min swaps |
| Merge | O(n log n) | O(n) | ✓ | ✗ | Guaranteed perf |
| Quick | O(n log n)* | O(log n) | ✗ | ✓ | **Default choice** |
| Heap | O(n log n) | O(1) | ✗ | ✓ | Guaranteed, strict |
| Count | O(n+k) | O(k) | ✓ | ✗ | Small range |
| Radix | O(n*d) | O(n) | ✓ | ✗ | Large numbers |

\* Average case; worst case O(n²)

---

## 💡 MEMORY TIPS

- **QUICK SORT**: "divide and conquer with pivot" → Fastest average
- **MERGE SORT**: "divide and merge" → Stable, guaranteed
- **HEAP SORT**: "build heap, extract max repeatedly" → In-place guaranteed
- **COUNTING SORT**: "count occurrences, reconstruct" → For small ranges only
- **RADIX SORT**: "sort digit by digit" → For large numbers


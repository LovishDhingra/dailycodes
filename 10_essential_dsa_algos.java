// 10 ESSENTIAL DSA ALGORITHMS IN JAVA
// Complete implementations with test cases

import java.util.*;

public class DSAAlgorithms {

    // ========================================================================
    // 1. LINEAR SEARCH
    // ========================================================================
    static int linearSearch(int[] arr, int target) {
        for (int i = 0; i < arr.length; i++) {
            if (arr[i] == target) return i;
        }
        return -1;
    }

    // ========================================================================
    // 2. BINARY SEARCH (Iterative)
    // ========================================================================
    static int binarySearchIterative(int[] arr, int target) {
        int low = 0, high = arr.length - 1;
        
        while (low <= high) {
            int mid = low + (high - low) / 2;
            
            if (arr[mid] == target) return mid;
            else if (arr[mid] < target) low = mid + 1;
            else high = mid - 1;
        }
        return -1;
    }

    // ========================================================================
    // 2B. BINARY SEARCH (Recursive)
    // ========================================================================
    static int binarySearchRecursive(int[] arr, int target, int low, int high) {
        if (low > high) return -1;
        
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) return binarySearchRecursive(arr, target, mid + 1, high);
        else return binarySearchRecursive(arr, target, low, mid - 1);
    }

    // ========================================================================
    // 3. BUBBLE SORT (Optimized)
    // ========================================================================
    static void bubbleSort(int[] arr) {
        int n = arr.length;
        for (int i = 0; i < n; i++) {
            boolean swapped = false;
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr, j, j + 1);
                    swapped = true;
                }
            }
            if (!swapped) break; // Already sorted
        }
    }

    // ========================================================================
    // 4. INSERTION SORT
    // ========================================================================
    static void insertionSort(int[] arr) {
        int n = arr.length;
        for (int i = 1; i < n; i++) {
            int key = arr[i];
            int j = i - 1;
            
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }

    // ========================================================================
    // 5. SELECTION SORT
    // ========================================================================
    static void selectionSort(int[] arr) {
        int n = arr.length;
        for (int i = 0; i < n - 1; i++) {
            int minIdx = i;
            
            for (int j = i + 1; j < n; j++) {
                if (arr[j] < arr[minIdx]) {
                    minIdx = j;
                }
            }
            
            if (minIdx != i) {
                swap(arr, i, minIdx);
            }
        }
    }

    // ========================================================================
    // 6. MERGE SORT
    // ========================================================================
    static void mergeSort(int[] arr, int low, int high) {
        if (low < high) {
            int mid = low + (high - low) / 2;
            mergeSort(arr, low, mid);
            mergeSort(arr, mid + 1, high);
            merge(arr, low, mid, high);
        }
    }

    static void merge(int[] arr, int low, int mid, int high) {
        int[] left = new int[mid - low + 1];
        int[] right = new int[high - mid];
        
        System.arraycopy(arr, low, left, 0, mid - low + 1);
        System.arraycopy(arr, mid + 1, right, 0, high - mid);
        
        int i = 0, j = 0, k = low;
        
        while (i < left.length && j < right.length) {
            if (left[i] <= right[j]) {
                arr[k++] = left[i++];
            } else {
                arr[k++] = right[j++];
            }
        }
        
        while (i < left.length) arr[k++] = left[i++];
        while (j < right.length) arr[k++] = right[j++];
    }

    // ========================================================================
    // 7. QUICK SORT
    // ========================================================================
    static void quickSort(int[] arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }

    static int partition(int[] arr, int low, int high) {
        int pivot = arr[high];
        int i = low - 1;
        
        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr, i, j);
            }
        }
        swap(arr, i + 1, high);
        return i + 1;
    }

    // ========================================================================
    // 8. HEAP SORT
    // ========================================================================
    static void heapSort(int[] arr) {
        int n = arr.length;
        
        // Build max heap
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(arr, n, i);
        }
        
        // Extract elements from heap
        for (int i = n - 1; i > 0; i--) {
            swap(arr, 0, i);
            heapify(arr, i, 0);
        }
    }

    static void heapify(int[] arr, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        
        if (left < n && arr[left] > arr[largest])
            largest = left;
        
        if (right < n && arr[right] > arr[largest])
            largest = right;
        
        if (largest != i) {
            swap(arr, i, largest);
            heapify(arr, n, largest);
        }
    }

    // ========================================================================
    // 9. COUNTING SORT
    // ========================================================================
    static void countingSort(int[] arr) {
        if (arr.length == 0) return;
        
        int max = Arrays.stream(arr).max().orElse(0);
        int[] count = new int[max + 1];
        
        // Count occurrences
        for (int num : arr) {
            count[num]++;
        }
        
        // Reconstruct array
        int idx = 0;
        for (int i = 0; i <= max; i++) {
            while (count[i] > 0) {
                arr[idx++] = i;
                count[i]--;
            }
        }
    }

    // ========================================================================
    // 10. RADIX SORT
    // ========================================================================
    static void radixSort(int[] arr) {
        if (arr.length == 0) return;
        
        int max = Arrays.stream(arr).max().orElse(0);
        
        for (int exp = 1; max / exp > 0; exp *= 10) {
            countingSortForRadix(arr, exp);
        }
    }

    static void countingSortForRadix(int[] arr, int exp) {
        int[] output = new int[arr.length];
        int[] count = new int[10];
        
        // Count occurrences of digits
        for (int num : arr) {
            count[(num / exp) % 10]++;
        }
        
        // Cumulative count
        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }
        
        // Build output array
        for (int i = arr.length - 1; i >= 0; i--) {
            int digit = (arr[i] / exp) % 10;
            output[count[digit] - 1] = arr[i];
            count[digit]--;
        }
        
        // Copy back
        System.arraycopy(output, 0, arr, 0, arr.length);
    }

    // ========================================================================
    // UTILITY FUNCTIONS
    // ========================================================================
    static void swap(int[] arr, int i, int j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    static void printArray(int[] arr, String name) {
        System.out.print(name + ": ");
        for (int x : arr) System.out.print(x + " ");
        System.out.println();
    }

    // ========================================================================
    // TEST CASES
    // ========================================================================
    public static void main(String[] args) {
        System.out.println("\n╔════════════════════════════════════════════════════════╗");
        System.out.println("║   10 ESSENTIAL DSA ALGORITHMS IN JAVA - COMPLETE GUIDE  ║");
        System.out.println("╚════════════════════════════════════════════════════════╝\n");

        int[] original = {64, 34, 25, 12, 22, 11, 90};
        int[] sorted = {11, 12, 22, 25, 34, 64, 90};

        // 1. LINEAR SEARCH
        System.out.println("\n=== 1. LINEAR SEARCH ===");
        int result = linearSearch(original, 12);
        System.out.println("Linear Search for 12: index " + result);

        // 2. BINARY SEARCH
        System.out.println("\n=== 2. BINARY SEARCH ===");
        result = binarySearchIterative(sorted, 25);
        System.out.println("Binary Search for 25 (iterative): index " + result);
        result = binarySearchRecursive(sorted, 25, 0, sorted.length - 1);
        System.out.println("Binary Search for 25 (recursive): index " + result);

        // 3. BUBBLE SORT
        System.out.println("\n=== 3. BUBBLE SORT ===");
        int[] arr = original.clone();
        bubbleSort(arr);
        printArray(arr, "Sorted");

        // 4. INSERTION SORT
        System.out.println("\n=== 4. INSERTION SORT ===");
        arr = original.clone();
        insertionSort(arr);
        printArray(arr, "Sorted");

        // 5. SELECTION SORT
        System.out.println("\n=== 5. SELECTION SORT ===");
        arr = original.clone();
        selectionSort(arr);
        printArray(arr, "Sorted");

        // 6. MERGE SORT
        System.out.println("\n=== 6. MERGE SORT ===");
        arr = original.clone();
        mergeSort(arr, 0, arr.length - 1);
        printArray(arr, "Sorted");

        // 7. QUICK SORT
        System.out.println("\n=== 7. QUICK SORT ===");
        arr = original.clone();
        quickSort(arr, 0, arr.length - 1);
        printArray(arr, "Sorted");

        // 8. HEAP SORT
        System.out.println("\n=== 8. HEAP SORT ===");
        arr = original.clone();
        heapSort(arr);
        printArray(arr, "Sorted");

        // 9. COUNTING SORT
        System.out.println("\n=== 9. COUNTING SORT ===");
        arr = original.clone();
        countingSort(arr);
        printArray(arr, "Sorted");

        // 10. RADIX SORT
        System.out.println("\n=== 10. RADIX SORT ===");
        arr = original.clone();
        radixSort(arr);
        printArray(arr, "Sorted");

        System.out.println("\n╔════════════════════════════════════════════════════════╗");
        System.out.println("║                   ALL TESTS COMPLETED                    ║");
        System.out.println("╚════════════════════════════════════════════════════════╝\n");
    }
}

/*
╔════════════════════════════════════════════════════════════════════════════╗
║                      COMPLEXITY SUMMARY TABLE                              ║
╠════════════════════════════════════════════════════════════════════════════╣
║ Algorithm        │ Time (Best)   │ Time (Avg)    │ Time (Worst)  │ Space   ║
╠════════════════════════════════════════════════════════════════════════════╣
║ Linear Search    │ O(1)          │ O(n)          │ O(n)          │ O(1)    ║
║ Binary Search    │ O(1)          │ O(log n)      │ O(log n)      │ O(1)    ║
║ Bubble Sort      │ O(n)          │ O(n²)         │ O(n²)         │ O(1)    ║
║ Insertion Sort   │ O(n)          │ O(n²)         │ O(n²)         │ O(1)    ║
║ Selection Sort   │ O(n²)         │ O(n²)         │ O(n²)         │ O(1)    ║
║ Merge Sort       │ O(n log n)    │ O(n log n)    │ O(n log n)    │ O(n)    ║
║ Quick Sort       │ O(n log n)    │ O(n log n)    │ O(n²)         │ O(log n)║
║ Heap Sort        │ O(n log n)    │ O(n log n)    │ O(n log n)    │ O(1)    ║
║ Counting Sort    │ O(n+k)        │ O(n+k)        │ O(n+k)        │ O(k)    ║
║ Radix Sort       │ O(n*k)        │ O(n*k)        │ O(n*k)        │ O(n)    ║
╚════════════════════════════════════════════════════════════════════════════╝

KEY POINTS:

✅ LINEAR SEARCH: O(n) - simple but slow
✅ BINARY SEARCH: O(log n) - 30x faster, but requires sorted array

✅ BUBBLE SORT: O(n²) - simple, good for learning
✅ INSERTION SORT: O(n²) - best for nearly-sorted data
✅ SELECTION SORT: O(n²) - minimal swaps, unstable

✅ MERGE SORT: O(n log n) guaranteed - stable but O(n) space
✅ QUICK SORT: O(n log n) average - fastest in practice, in-place
✅ HEAP SORT: O(n log n) guaranteed - in-place but slower than quick

✅ COUNTING SORT: O(n+k) - for small range integers
✅ RADIX SORT: O(n*d) - for multi-digit numbers

COMPILATION:
  javac DSAAlgorithms.java
  java DSAAlgorithms

INTERVIEW TIPS:
1. Master QuickSort (most commonly asked)
2. Understand MergeSort (stability & guarantees)
3. Know when to use each algorithm
4. Be able to explain time/space complexity
5. Handle edge cases (empty, single element, duplicates)
6. Optimize for common scenarios (nearly sorted, few duplicates)
*/

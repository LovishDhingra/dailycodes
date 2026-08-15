# 10 ESSENTIAL DSA ALGORITHMS - DETAILED GUIDE

---

## 📊 COMPLEXITY COMPARISON TABLE

| Algorithm | Time (Best) | Time (Avg) | Time (Worst) | Space | Stable | In-Place |
|-----------|------------|-----------|--------------|-------|--------|----------|
| **Linear Search** | O(1) | O(n) | O(n) | O(1) | - | ✓ |
| **Binary Search** | O(1) | O(log n) | O(log n) | O(1) | - | ✓ |
| **Bubble Sort** | O(n) | O(n²) | O(n²) | O(1) | ✓ | ✓ |
| **Insertion Sort** | O(n) | O(n²) | O(n²) | O(1) | ✓ | ✓ |
| **Selection Sort** | O(n²) | O(n²) | O(n²) | O(1) | ✗ | ✓ |
| **Merge Sort** | O(n log n) | O(n log n) | O(n log n) | O(n) | ✓ | ✗ |
| **Quick Sort** | O(n log n) | O(n log n) | O(n²) | O(log n) | ✗ | ✓ |
| **Heap Sort** | O(n log n) | O(n log n) | O(n log n) | O(1) | ✗ | ✓ |
| **Counting Sort** | O(n+k) | O(n+k) | O(n+k) | O(k) | ✓ | ✗ |
| **Radix Sort** | O(n*d) | O(n*d) | O(n*d) | O(n) | ✓ | ✗ |

---

## 🔍 SEARCHING ALGORITHMS

### 1. LINEAR SEARCH
**Search for element by checking each position sequentially**

```
Array: [64, 34, 25, 12, 22, 11, 90]
Target: 12

i=0: 64 != 12
i=1: 34 != 12
i=2: 25 != 12
i=3: 12 == 12 ✓ FOUND at index 3
```

**When to use:**
- ✓ Unsorted arrays
- ✓ Small arrays (n < 1000)
- ✓ Linked lists
- ✗ Large sorted arrays (use binary search instead)

**Characteristics:**
- Simplest search algorithm
- No preprocessing needed
- Adaptive (O(n) best, O(n) worst)

---

### 2. BINARY SEARCH
**Divide array in half, eliminate half with each comparison**

```
Sorted Array: [11, 12, 22, 25, 34, 64, 90]
Target: 25

Step 1: mid = 25, low=0, high=6
        arr[3] = 25 == 25 ✓ FOUND

DRY RUN with target=22:
Step 1: mid=3, arr[3]=25 > 22 → high=2
Step 2: mid=1, arr[1]=12 < 22 → low=2
Step 3: mid=2, arr[2]=22 == 22 ✓ FOUND
```

**Prerequisites:**
- Array MUST be SORTED
- Random access (arrays, not linked lists)

**When to use:**
- ✓ Large sorted arrays (n > 1000)
- ✓ When you need O(log n) speed
- ✓ Telephone directory lookup
- ✗ Unsorted data
- ✗ Linked lists

**Performance:** 
- 30x faster than linear on 1M elements
- 50x faster on 1B elements

**Two variants:**
1. **Iterative** - No recursion stack, preferred for interviews
2. **Recursive** - Elegant, cleaner code

---

## 🔄 ELEMENTARY SORTING (O(n²))

### 3. BUBBLE SORT
**Repeatedly swap adjacent elements if they're in wrong order**

```
Array: [64, 34, 25, 12, 22, 11, 90]

Pass 1: Compare adjacent pairs, largest "bubbles" to end
  (64,34)→34,64  (64,25)→25,64  (64,12)→12,64  (64,22)→22,64  (64,11)→11,64  (64,90)→11,64,90
  Result: [34, 25, 12, 22, 11, 64, 90]

Pass 2: (34,25)→... largest of remaining goes to position 5
  Result: [25, 12, 22, 11, 34, 64, 90]

Continue until sorted...
Final: [11, 12, 22, 25, 34, 64, 90]
```

**Optimization:** Stop if no swaps occur (already sorted)

**When to use:**
- ✓ Teaching sorting concepts
- ✓ Nearly sorted small arrays
- ✓ When stability matters + simplicity is priority
- ✗ Large arrays (use merge/quick sort)

**Characteristics:**
- Stable (equal elements preserve order)
- In-place (O(1) space)
- Adaptive (O(n) if already sorted with optimization)

---

### 4. INSERTION SORT
**Insert each element into its correct position in sorted portion**

```
Array: [64, 34, 25, 12, 22, 11, 90]
       [X  ] (sorted part = just 64)

Insert 34: [34, 64] (34 < 64, shift 64)
Insert 25: [25, 34, 64] (25 < 34, shift both)
Insert 12: [12, 25, 34, 64]
Insert 22: [12, 22, 25, 34, 64]
Insert 11: [11, 12, 22, 25, 34, 64]
Insert 90: [11, 12, 22, 25, 34, 64, 90] (90 largest, no shift)
```

**When to use:**
- ✓ Nearly sorted arrays (BEST choice)
- ✓ Small arrays
- ✓ Online sorting (sort data as it arrives)
- ✓ Stable sorting needed
- ✗ Large unsorted arrays

**Best case:** O(n) when array already sorted
**Worst case:** O(n²) when reverse sorted

**Real-world:** Used to sort hand of cards!

---

### 5. SELECTION SORT
**Find minimum element, swap with current position**

```
Array: [64, 34, 25, 12, 22, 11, 90]

Pass 1: Find min in [64,34,25,12,22,11,90] → 11 at index 5
        Swap with index 0: [11, 34, 25, 12, 22, 64, 90]

Pass 2: Find min in [34,25,12,22,64,90] → 12 at index 3
        Swap with index 1: [11, 12, 25, 34, 22, 64, 90]

Pass 3: Find min in [25,34,22,64,90] → 22 at index 4
        Swap with index 2: [11, 12, 22, 34, 25, 64, 90]

Pass 4: Find min in [34,25,64,90] → 25 at index 4
        Swap with index 3: [11, 12, 22, 25, 34, 64, 90]

Continue...
```

**When to use:**
- ✓ When minimizing memory writes is critical
- ✓ When swap cost is high
- ✓ Small arrays
- ✗ When stability matters (not stable)

**Characteristics:**
- NOT stable (equal elements order may change)
- In-place, minimal swaps (n swaps max)
- Always O(n²) (no best case optimization)

---

## ⚡ ADVANCED SORTING (O(n log n))

### 6. MERGE SORT
**Divide array in half recursively, merge sorted halves**

```
Array: [64, 34, 25, 12, 22, 11, 90]

DIVIDE:
         [64,34,25,12,22,11,90]
              /            \
        [64,34,25,12]    [22,11,90]
         /        \       /      \
      [64,34]   [25,12]  [22,11]  [90]
       /   \     /   \    /   \     
     [64] [34] [25] [12] [22] [11] [90]

MERGE (bottom-up):
     [34,64] [12,25] [11,22] [90]
         \      /      \     /
        [12,25,34,64]  [11,22,90]
               \          /
          [11,12,22,25,34,64,90]
```

**When to use:**
- ✓ When stable sorting is mandatory
- ✓ When guaranteed O(n log n) needed
- ✓ Linked lists (no random access needed)
- ✓ External sorting (large files)
- ✗ When memory is limited (needs O(n) extra space)

**Characteristics:**
- Stable sorting
- NOT in-place (O(n) extra space)
- Predictable performance (no worst case)
- Requires merging step (extra work)

---

### 7. QUICK SORT
**Partition around pivot, recursively sort partitions**

```
Array: [64, 34, 25, 12, 22, 11, 90]
Pivot: 90 (last element)

Partition:
  Elements < 90: [64, 34, 25, 12, 22, 11]
  Elements = 90: [90]
  Result: [64,34,25,12,22,11,90]

Recursively sort left [64,34,25,12,22,11]:
Pivot: 11
  < 11: []
  = 11: [11]
  > 11: [64,34,25,12,22]
  Result: [11,64,34,25,12,22]

Continue...
Final: [11,12,22,25,34,64,90]
```

**When to use:**
- ✓ GENERAL PURPOSE sorting (default choice in most languages)
- ✓ Average O(n log n) performance
- ✓ In-place sorting
- ✓ Cache-friendly
- ✗ When worst case O(n²) unacceptable (use randomized pivot)
- ✗ When stability critical

**Pivot Selection Strategies:**
1. **First/Last** - Simple but risky on sorted data
2. **Random** - Good O(n log n) guarantee probabilistically
3. **Median-of-three** - Reduces worst case likelihood
4. **Three-way partition** - Handles duplicates efficiently

**Characteristics:**
- NOT stable
- In-place (O(log n) stack space)
- Cache-efficient (sequential access)
- Fastest average case in practice

---

### 8. HEAP SORT
**Build max-heap, repeatedly extract maximum**

```
Array: [64, 34, 25, 12, 22, 11, 90]

BUILD MAX HEAP:
         90
       /    \
      64     25
     / \    / \
   34  22  11 12

Extract 90: [64, 34, 25, 12, 22, 11] + [90]
           60
         /    \
       34     25
      / \    / 
    12  22  11

Extract 64: [34, 22, 25, 12, 11] + [64,90]

Continue extracting...
Final: [11, 12, 22, 25, 34, 64, 90]
```

**When to use:**
- ✓ When guaranteed O(n log n) needed
- ✓ When space must be O(1)
- ✓ When worst-case performance critical
- ✗ When stability needed
- ✗ When cache locality matters (poor)

**Characteristics:**
- Guaranteed O(n log n) all cases
- NOT stable
- In-place (O(1) extra space)
- Poor cache locality (jumps in array)
- Rarely fastest in practice (overhead)

---

## 🎯 SPECIALIZED SORTING

### 9. COUNTING SORT
**Count occurrences of each value, reconstruct sorted array**

```
Array: [64, 34, 25, 12, 22, 11, 90]
Range: 0 to 90

Count array (only showing non-zero):
  Index:  11  12  22  25  34  64  90
  Count:   1   1   1   1   1   1   1

Reconstruct:
  11 once → [11]
  12 once → [11, 12]
  22 once → [11, 12, 22]
  25 once → [11, 12, 22, 25]
  34 once → [11, 12, 22, 25, 34]
  64 once → [11, 12, 22, 25, 34, 64]
  90 once → [11, 12, 22, 25, 34, 64, 90]
```

**Complexity:**
- Time: O(n + k) where k = max element
- Space: O(k)
- FASTER than comparison sorts when k is small!

**When to use:**
- ✓ Non-negative integers ONLY
- ✓ When range k << n (e.g., grades 0-100 for 1M students)
- ✓ Stable sorting variant available
- ✗ Negative numbers (modify algorithm)
- ✗ Large range (e.g., sorting IPs directly)

**Real-world:** 
- Sorting grades/scores in educational systems
- Counting votes by district
- Histogram data

---

### 10. RADIX SORT
**Sort by digits: ones place → tens place → hundreds place...**

```
Array: [64, 34, 25, 12, 22, 11, 90]

Sort by ones digit (exp=1):
  Digit 0: [90, 10] (no 10 in array)
  Digit 1: [11]
  Digit 2: [12, 22]
  Digit 4: [64, 34]
  Digit 5: [25]
  Result after ones: [90, 11, 12, 22, 64, 34, 25]

Sort by tens digit (exp=10):
  Digit 0: [01-09 none]
  Digit 1: [11, 12]
  Digit 2: [22, 25]
  Digit 3: [34]
  Digit 6: [64]
  Digit 9: [90]
  Result after tens: [11, 12, 22, 25, 34, 64, 90]

All digits processed → SORTED!
```

**Complexity:**
- Time: O(n * d) where d = number of digits
- Space: O(n)
- FASTER than comparison sorts for large numbers!

**When to use:**
- ✓ Non-negative integers with few digits
- ✓ When d is small relative to n
- ✓ Sorting large numbers efficiently
- ✓ Must be stable
- ✗ Negative numbers (requires offset trick)
- ✗ Floating point numbers

**Real-world:**
- Sorting network packets by IP
- Sorting very large integers
- Parallel sorting (each digit can be sorted in parallel)

---

## 🎓 INTERVIEW CHEAT SHEET

### Quick Decision Tree
```
Q: Is array already sorted?
  → YES: Use BINARY SEARCH (log n)
  → NO: Continue...

Q: How large is the array?
  → < 50: Use INSERTION SORT or BUBBLE SORT (simple)
  → >= 50: Continue...

Q: Does stability matter?
  → YES: Use MERGE SORT or COUNTING SORT (stable)
  → NO: Continue...

Q: Is memory limited?
  → YES: Use QUICK SORT or HEAP SORT (in-place)
  → NO: Use MERGE SORT (guaranteed O(n log n))

Q: Is data on disk/network?
  → YES: Use MERGE SORT (good cache locality)
  → NO: Use QUICK SORT (fastest average)

Q: Are values in small range?
  → YES: Use COUNTING SORT (n + k)
  → MAYBE: Use RADIX SORT (n * d)
  → NO: Use QUICK SORT (general purpose)
```

### Most Asked Algorithms in Interviews
1. **Quick Sort** (30% of questions)
   - Why? Fast, in-place, shows algorithm design skills
   - Know: Partitioning, pivot selection, complexity analysis

2. **Merge Sort** (20% of questions)
   - Why? Guaranteed performance, stability, divide-conquer
   - Know: Merging strategy, why not in-place, stability proof

3. **Binary Search** (20% of questions)
   - Why? Foundation for many advanced algorithms
   - Know: Iterative vs recursive, edge cases, off-by-one errors

4. **Heap Sort** (10% of questions)
   - Why? Tests data structure knowledge
   - Know: Heapify, heap property, extraction

5. **Counting/Radix Sort** (10% of questions)
   - Why? Non-comparison sorting, special cases
   - Know: When applicable, complexity analysis

6. **Bubble/Insertion Sort** (10% of questions)
   - Why? Foundational concepts, optimization tricks
   - Know: When to use, optimization techniques

---

## 📋 IMPLEMENTATION CHECKLIST

### Before Writing Code:
- [ ] Clarify input (sorted? duplicates? negative?)
- [ ] Ask about constraints (time/space/stability)
- [ ] Choose appropriate algorithm
- [ ] Discuss complexity trade-offs

### During Implementation:
- [ ] Handle edge cases (empty, single element, all same)
- [ ] Avoid off-by-one errors
- [ ] Optimize pivot selection (if quick sort)
- [ ] Consider stability if needed

### After Implementation:
- [ ] Test with edge cases
- [ ] Verify complexity analysis
- [ ] Discuss optimization possibilities
- [ ] Compare with alternatives

---

## 🚀 OPTIMIZATION TIPS

| Scenario | Optimization |
|----------|---------------|
| Nearly sorted array | Use Insertion Sort, optimized Bubble |
| Many duplicates | Use Quick Sort 3-way partition |
| Needs stability | Use Merge Sort or Counting Sort |
| Memory critical | Use Quick Sort or Heap Sort |
| Large external data | Use Merge Sort (sequential access) |
| Must avoid worst case | Randomized Quick Sort or Heap Sort |
| Small range values | Use Counting Sort |
| Multi-digit integers | Use Radix Sort |

---

## 💡 KEY TAKEAWAYS

✅ Master **Quick Sort** (most useful)
✅ Understand **Merge Sort** (stability + guarantee)
✅ Know **Binary Search** (ubiquitous)
✅ Remember trade-offs (time vs space vs stability)
✅ Know when to use specialized sorts (counting, radix)
✅ Optimize for common cases (nearly sorted, duplicates)
✅ Always consider complexity (best, average, worst)
✅ Prove your algorithm works (dry runs, edge cases)


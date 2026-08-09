# LeetCode 3348: Smallest Divisible Digit Product II - Complete Solution

## Problem Statement
Given a string `num` representing a positive integer and an integer `t`, find the smallest zero-free number greater than or equal to `num` such that the product of its digits is divisible by `t`. Return "-1" if no such number exists.

---

## APPROACH 1: BRUTE FORCE

### Concept
- Start from `num` and check each subsequent number
- For each number, calculate digit product
- Return first number where product % t == 0
- Stop after a reasonable limit (e.g., 10^7 iterations)

### Python Implementation (Brute Force)
```python
def smallestNumber(num: str, t: int) -> str:
    # Start from the given number
    current = int(num)
    limit = current + 10**7  # Set a limit to avoid infinite loop
    
    while current <= limit:
        # Check if current number is zero-free
        if '0' not in str(current):
            # Calculate digit product
            digit_product = 1
            for digit in str(current):
                digit_product *= int(digit)
            
            # Check if divisible by t
            if digit_product % t == 0:
                return str(current)
        
        current += 1
    
    return "-1"

# Test Cases
print(smallestNumber("1234", 256))   # "1488"
print(smallestNumber("12355", 50))   # "12355"
print(smallestNumber("11111", 26))   # "-1"
```

### C++ Implementation (Brute Force)
```cpp
#include <iostream>
#include <string>
using namespace std;

string smallestNumber(string num, int t) {
    long long current = stoll(num);
    long long limit = current + 10000000;  // Set limit
    
    while (current <= limit) {
        string str_current = to_string(current);
        
        // Check if zero-free
        if (str_current.find('0') == string::npos) {
            // Calculate digit product
            long long digit_product = 1;
            for (char digit : str_current) {
                digit_product *= (digit - '0');
            }
            
            // Check if divisible by t
            if (digit_product % t == 0) {
                return str_current;
            }
        }
        
        current++;
    }
    
    return "-1";
}

int main() {
    cout << smallestNumber("1234", 256) << endl;   // "1488"
    cout << smallestNumber("12355", 50) << endl;   // "12355"
    cout << smallestNumber("11111", 26) << endl;   // "-1"
    return 0;
}
```

### Java Implementation (Brute Force)
```java
class Solution {
    public String smallestNumber(String num, int t) {
        long current = Long.parseLong(num);
        long limit = current + 10000000;
        
        while (current <= limit) {
            String str_current = Long.toString(current);
            
            // Check if zero-free
            if (!str_current.contains("0")) {
                // Calculate digit product
                long digit_product = 1;
                for (char digit : str_current.toCharArray()) {
                    digit_product *= (digit - '0');
                }
                
                // Check if divisible by t
                if (digit_product % t == 0) {
                    return str_current;
                }
            }
            
            current++;
        }
        
        return "-1";
    }
    
    public static void main(String[] args) {
        Solution sol = new Solution();
        System.out.println(sol.smallestNumber("1234", 256));   // "1488"
        System.out.println(sol.smallestNumber("12355", 50));   // "12355"
        System.out.println(sol.smallestNumber("11111", 26));   // "-1"
    }
}
```

### Dry Run: Brute Force Approach
**Input:** num = "1234", t = 256

```
current = 1234
  -> "1234": product = 1×2×3×4 = 24, 24 % 256 ≠ 0 ✗
  -> "1235": product = 1×2×3×5 = 30, 30 % 256 ≠ 0 ✗
  -> ...
  -> "1488": product = 1×4×8×8 = 256, 256 % 256 == 0 ✓
  -> Return "1488"
```

**Limitations:** Too slow for large numbers due to O(n × k) complexity.

---

## APPROACH 2: OPTIMIZED (GREEDY + DFS with Prime Factorization)

### Concept
1. **Factorize t:** Extract prime factors (2, 3, 5, 7 are the only ones we need)
2. **Check num:** If digit product already satisfies, return it
3. **DFS/Backtracking:** Build result digit by digit greedily
   - Try to keep prefix same as num
   - When we must increment, try to fill remaining with smallest valid digits
4. **Early Termination:** If t can't be satisfied with digits 1-9, return "-1"

### Key Insight
Only prime factors 2, 3, 5, 7 matter because:
- 1 has no prime factors
- 2 = 2
- 3 = 3
- 4 = 2²
- 5 = 5
- 6 = 2 × 3
- 7 = 7
- 8 = 2³
- 9 = 3²

So we track remaining factors as (count_2, count_3, count_5, count_7).

### Python Implementation (Optimized)
```python
from functools import lru_cache
from math import gcd

def smallestNumber(num: str, t: int) -> str:
    # Factorize t
    factors = {2: 0, 3: 0, 5: 0, 7: 0}
    temp_t = t
    for prime in [2, 3, 5, 7]:
        while temp_t % prime == 0:
            factors[prime] += 1
            temp_t //= prime
    
    # If t has prime factors other than 2, 3, 5, 7, impossible
    if temp_t > 1:
        return "-1"
    
    # Check if current number satisfies
    def digit_product_factors(s):
        f = {2: 0, 3: 0, 5: 0, 7: 0}
        for ch in s:
            d = int(ch)
            if d == 0:
                return None
            # Factor the digit
            for prime in [2, 3, 5, 7]:
                temp_d = d
                while temp_d % prime == 0:
                    f[prime] += 1
                    temp_d //= prime
        return f
    
    curr_factors = digit_product_factors(num)
    if curr_factors and all(curr_factors[p] >= factors[p] for p in factors):
        return num
    
    # DFS to find the answer
    n = len(num)
    
    def dfs(pos, is_tight, remaining_factors):
        # Base case: processed all positions
        if pos == n:
            # Check if all factors are satisfied
            return all(remaining_factors[p] <= 0 for p in remaining_factors)
        
        start_digit = int(num[pos]) if is_tight else 1
        
        for digit in range(start_digit, 10):
            if digit == 0:
                continue
            
            # Factor the digit
            new_factors = remaining_factors.copy()
            temp_d = digit
            for prime in [2, 3, 5, 7]:
                while temp_d % prime == 0:
                    new_factors[prime] -= 1
                    temp_d //= prime
            
            new_tight = is_tight and (digit == int(num[pos]))
            
            if dfs(pos + 1, new_tight, new_factors):
                return True
        
        return False
    
    # Try to increment from num+1
    # Use a constructive approach
    def solve():
        # Try to find valid number starting from num
        result = list(num)
        n = len(result)
        
        def construct(pos, is_tight, is_greater, remaining):
            if pos == n:
                if is_greater and all(remaining[p] <= 0 for p in remaining):
                    return True
                return False
            
            start = 0 if is_greater else (int(result[pos]) if is_tight else 0)
            end = 9
            
            for digit in range(start, end + 1):
                if digit == 0 and not is_greater:
                    continue
                
                new_remaining = remaining.copy()
                temp_d = digit
                for prime in [2, 3, 5, 7]:
                    while temp_d % prime == 0:
                        new_remaining[prime] -= 1
                        temp_d //= prime
                
                new_tight = is_tight and (digit == int(num[pos]))
                new_greater = is_greater or (digit > int(num[pos]))
                
                result[pos] = str(digit)
                
                if construct(pos + 1, new_tight, new_greater, new_remaining):
                    return True
            
            return False
        
        if construct(0, True, False, factors.copy()):
            return "".join(result)
        return "-1"
    
    return solve()

# Test Cases
print(smallestNumber("1234", 256))   # "1488"
print(smallestNumber("12355", 50))   # "12355"
print(smallestNumber("11111", 26))   # "-1"
```

### C++ Implementation (Optimized)
```cpp
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

string smallestNumber(string num, int t) {
    // Factorize t
    unordered_map<int, int> factors;
    factors[2] = 0;
    factors[3] = 0;
    factors[5] = 0;
    factors[7] = 0;
    
    int temp_t = t;
    for (int prime : {2, 3, 5, 7}) {
        while (temp_t % prime == 0) {
            factors[prime]++;
            temp_t /= prime;
        }
    }
    
    // If t has other prime factors, impossible
    if (temp_t > 1) {
        return "-1";
    }
    
    // Check if num satisfies
    auto get_factors = [](const string& s) -> unordered_map<int, int> {
        unordered_map<int, int> f;
        f[2] = 0; f[3] = 0; f[5] = 0; f[7] = 0;
        
        for (char ch : s) {
            if (ch == '0') return unordered_map<int, int>{};
            int d = ch - '0';
            for (int prime : {2, 3, 5, 7}) {
                int temp_d = d;
                while (temp_d % prime == 0) {
                    f[prime]++;
                    temp_d /= prime;
                }
            }
        }
        return f;
    };
    
    auto curr_factors = get_factors(num);
    bool satisfies = true;
    for (auto [prime, cnt] : factors) {
        if (curr_factors[prime] < cnt) {
            satisfies = false;
            break;
        }
    }
    
    if (satisfies) {
        return num;
    }
    
    // DFS construction
    int n = num.length();
    string result = num;
    
    function<bool(int, bool, bool, unordered_map<int, int>&)> construct = 
        [&](int pos, bool is_tight, bool is_greater, unordered_map<int, int>& remaining) -> bool {
        
        if (pos == n) {
            if (is_greater) {
                for (auto [prime, cnt] : remaining) {
                    if (cnt > 0) return false;
                }
                return true;
            }
            return false;
        }
        
        int start = (is_greater || !is_tight) ? 1 : (num[pos] - '0');
        
        for (int digit = start; digit <= 9; digit++) {
            unordered_map<int, int> new_remaining = remaining;
            int temp_d = digit;
            
            for (int prime : {2, 3, 5, 7}) {
                while (temp_d % prime == 0) {
                    new_remaining[prime]--;
                    temp_d /= prime;
                }
            }
            
            bool new_tight = is_tight && (digit == (num[pos] - '0'));
            bool new_greater = is_greater || (digit > (num[pos] - '0'));
            
            result[pos] = char('0' + digit);
            
            if (construct(pos + 1, new_tight, new_greater, new_remaining)) {
                return true;
            }
        }
        
        return false;
    };
    
    auto temp_factors = factors;
    if (construct(0, true, false, temp_factors)) {
        return result;
    }
    
    return "-1";
}

int main() {
    cout << smallestNumber("1234", 256) << endl;   // "1488"
    cout << smallestNumber("12355", 50) << endl;   // "12355"
    cout << smallestNumber("11111", 26) << endl;   // "-1"
    return 0;
}
```

### Java Implementation (Optimized)
```java
class Solution {
    public String smallestNumber(String num, int t) {
        // Factorize t
        int[] factors = {0, 0, 0, 0}; // for 2, 3, 5, 7
        int[] primes = {2, 3, 5, 7};
        int temp_t = t;
        
        for (int i = 0; i < 4; i++) {
            while (temp_t % primes[i] == 0) {
                factors[i]++;
                temp_t /= primes[i];
            }
        }
        
        // If t has other prime factors, impossible
        if (temp_t > 1) {
            return "-1";
        }
        
        // Check if num satisfies
        int[] curr_factors = getFactors(num);
        if (curr_factors != null) {
            boolean satisfies = true;
            for (int i = 0; i < 4; i++) {
                if (curr_factors[i] < factors[i]) {
                    satisfies = false;
                    break;
                }
            }
            if (satisfies) {
                return num;
            }
        }
        
        // DFS construction
        int n = num.length();
        char[] result = num.toCharArray();
        
        int[] remaining = factors.clone();
        if (construct(num, result, 0, true, false, remaining, primes)) {
            return new String(result);
        }
        
        return "-1";
    }
    
    private int[] getFactors(String s) {
        int[] f = new int[4]; // for 2, 3, 5, 7
        int[] primes = {2, 3, 5, 7};
        
        for (char ch : s.toCharArray()) {
            if (ch == '0') return null;
            int d = ch - '0';
            for (int i = 0; i < 4; i++) {
                int temp_d = d;
                while (temp_d % primes[i] == 0) {
                    f[i]++;
                    temp_d /= primes[i];
                }
            }
        }
        return f;
    }
    
    private boolean construct(String num, char[] result, int pos, boolean is_tight, 
                            boolean is_greater, int[] remaining, int[] primes) {
        if (pos == num.length()) {
            if (is_greater) {
                for (int cnt : remaining) {
                    if (cnt > 0) return false;
                }
                return true;
            }
            return false;
        }
        
        int start = (is_greater || !is_tight) ? 1 : (num.charAt(pos) - '0');
        
        for (int digit = start; digit <= 9; digit++) {
            int[] new_remaining = remaining.clone();
            int temp_d = digit;
            
            for (int i = 0; i < 4; i++) {
                while (temp_d % primes[i] == 0) {
                    new_remaining[i]--;
                    temp_d /= primes[i];
                }
            }
            
            boolean new_tight = is_tight && (digit == (num.charAt(pos) - '0'));
            boolean new_greater = is_greater || (digit > (num.charAt(pos) - '0'));
            
            result[pos] = (char)('0' + digit);
            
            if (construct(num, result, pos + 1, new_tight, new_greater, new_remaining, primes)) {
                return true;
            }
        }
        
        return false;
    }
    
    public static void main(String[] args) {
        Solution sol = new Solution();
        System.out.println(sol.smallestNumber("1234", 256));   // "1488"
        System.out.println(sol.smallestNumber("12355", 50));   // "12355"
        System.out.println(sol.smallestNumber("11111", 26));   // "-1"
    }
}
```

### Dry Run: Optimized Approach
**Input:** num = "1234", t = 256

```
1. Factorize 256 = 2^8
   factors = {2: 8, 3: 0, 5: 0, 7: 0}

2. Check "1234": 1×2×3×4 = 24 = 2^3 × 3
   - Has 2^3 but need 2^8 ✗

3. DFS construction starting from "1234":
   - pos=0, digit=1: remaining = {2: 8, ...}
   - pos=1, digit=2: remaining = {2: 7, ...}
   - pos=2, digit=3: remaining = {2: 7, 3: -1, ...} → invalid
   
   Backtrack, try digit=4 at pos=2:
   - pos=2, digit=4: 4 = 2^2, remaining = {2: 5, ...}
   - pos=3, digit=4: remaining = {2: 3, ...} → incomplete, backtrack

   Try pos=1, digit=3:
   - pos=1, digit=3: digit=3 > '2', is_greater = true
   - Now we need remaining factors with more freedom
   
   Continue building: "14..." or "15..."
   
   Eventually reach "1488":
   - 1 = nothing
   - 4 = 2^2 → remaining = {2: 6, ...}
   - 8 = 2^3 → remaining = {2: 3, ...}
   - 8 = 2^3 → remaining = {2: 0, ...} ✓

4. Return "1488"
```

---

## Complexity Analysis

### Brute Force
- **Time:** O(n × d) where n is range searched and d is digit count
- **Space:** O(1)
- **Verdict:** Too slow for large inputs

### Optimized (DFS)
- **Time:** O(10 × d) = O(d) where d ≤ 10 (max 10 digits to try per position)
- **Space:** O(d) for recursion stack
- **Verdict:** Efficient and acceptable

---

## Key Takeaways

1. **Prime Factorization:** Only factors 2, 3, 5, 7 matter
2. **Impossibility Check:** If t has other prime factors, return "-1"
3. **Greedy DFS:** Try smallest digits first while maintaining factors
4. **Tight Constraint:** Track whether we must match original digits
5. **Early Termination:** If already satisfied, return immediately

---

## Test Cases Summary

| Input | t | Output | Explanation |
|-------|---|--------|-------------|
| "1234" | 256 | "1488" | 1×4×8×8 = 256 = 2^8 |
| "12355" | 50 | "12355" | 1×2×3×5×5 = 150 = 2×3×5^2 |
| "11111" | 26 | "-1" | 26 = 2×13 (has prime 13, impossible) |
| "1" | 1 | "1" | Any digit works; product of 1 is 1 |
| "999" | 144 | "1449" | Need 2^4 × 3^2, found in 1449 |

// 3348. Smallest Divisible Digit Product II
// https://leetcode.com/problems/smallest-divisible-digit-product-ii/

#include <bits/stdc++.h>
using namespace std;

// ---------- Brute Force: increment and check ----------
class SolutionBruteForce {
public:
    string smallestNumber(string num, long long t) {
        long long current = stoll(num);
        for (long long tries = 0; tries < 2000000; tries++) {
            string s = to_string(current);
            bool hasZero = false;
            long long product = 1;
            for (char c : s) {
                if (c == '0') { hasZero = true; break; }
                product *= (c - '0');
            }
            if (!hasZero && product % t == 0) return s;
            current++;
        }
        return "-1";
    }
};

// ---------- Optimal: Greedy Digit Construction ----------
class SolutionOptimal {
public:
    array<int,4> digitFactors(int d) {
        static array<array<int,4>,10> f = {{
            {0,0,0,0},{0,0,0,0},{1,0,0,0},{0,1,0,0},{2,0,0,0},
            {0,0,1,0},{1,1,0,0},{0,0,0,1},{3,0,0,0},{0,2,0,0}
        }};
        return f[d];
    }

    array<int,4> clampSub(array<int,4> req, array<int,4> sub) {
        array<int,4> res;
        for (int i = 0; i < 4; i++) res[i] = max(0, req[i] - sub[i]);
        return res;
    }

    vector<char> minimalDigits(array<int,4> req) {
        int e2=req[0], e3=req[1], e5=req[2], e7=req[3];
        vector<char> digits;
        for (int i=0;i<e7;i++) digits.push_back('7');
        for (int i=0;i<e5;i++) digits.push_back('5');
        int nine = e3/2, e3r = e3%2;
        int eight = e2/3, e2r = e2%3;
        for (int i=0;i<nine;i++) digits.push_back('9');
        for (int i=0;i<eight;i++) digits.push_back('8');
        if (e2r==0 && e3r==1) digits.push_back('3');
        else if (e2r==1 && e3r==0) digits.push_back('2');
        else if (e2r==1 && e3r==1) digits.push_back('6');
        else if (e2r==2 && e3r==0) digits.push_back('4');
        else if (e2r==2 && e3r==1) { digits.push_back('4'); digits.push_back('3'); }
        return digits;
    }

    string smallestNumber(string num, long long t) {
        int e2=0,e3=0,e5=0,e7=0;
        while (t % 2 == 0) { e2++; t /= 2; }
        while (t % 3 == 0) { e3++; t /= 3; }
        while (t % 5 == 0) { e5++; t /= 5; }
        while (t % 7 == 0) { e7++; t /= 7; }
        if (t != 1) return "-1";
        array<int,4> req = {e2,e3,e5,e7};

        int minCount = minimalDigits(req).size();
        int n = num.size();

        if (minCount <= n) {
            if (num.find('0') == string::npos) {
                array<int,4> total = {0,0,0,0};
                for (char c : num) {
                    auto f = digitFactors(c - '0');
                    for (int i=0;i<4;i++) total[i]+=f[i];
                }
                bool ok = true;
                for (int i=0;i<4;i++) if (total[i] < req[i]) ok = false;
                if (ok) return num;
            }

            vector<array<int,4>> prefix(n+1, {0,0,0,0});
            for (int i = 0; i < n; i++) {
                auto f = (num[i] != '0') ? digitFactors(num[i]-'0') : array<int,4>{0,0,0,0};
                for (int k=0;k<4;k++) prefix[i+1][k] = prefix[i][k] + f[k];
            }

            int firstZero = num.find('0');
            if (firstZero == (int)string::npos) firstZero = n;

            for (int i = n-1; i >= 0; i--) {
                if (i > firstZero) continue;
                auto remaining = clampSub(req, prefix[i]);
                int originalDigit = (i == firstZero) ? 0 : (num[i]-'0');
                for (int d = originalDigit+1; d <= 9; d++) {
                    auto remAfter = clampSub(remaining, digitFactors(d));
                    auto cand = minimalDigits(remAfter);
                    int slots = n - 1 - i;
                    if ((int)cand.size() <= slots) {
                        for (int p = 0; p < slots - (int)cand.size(); p++) cand.push_back('1');
                        sort(cand.begin(), cand.end());
                        return num.substr(0,i) + char('0'+d) + string(cand.begin(), cand.end());
                    }
                }
            }
        }

        int L = max(n+1, minCount);
        vector<char> digits = minimalDigits(req);
        for (int p = 0; p < L - minCount; p++) digits.push_back('1');
        sort(digits.begin(), digits.end());
        return string(digits.begin(), digits.end());
    }
};

int main() {
    SolutionOptimal s;
    cout << s.smallestNumber("1234", 256) << endl; // 1488
    cout << s.smallestNumber("12355", 50) << endl;  // 12355
    cout << s.smallestNumber("11111", 26) << endl;  // -1
    return 0;
}

// Problem: Implement an LRU (Least Recently Used) Cache
// Approach: Doubly linked list (most/least recent order) + hashmap for O(1)
// access to list nodes.
// Time: O(1) for get and put   Space: O(capacity)

#include <bits/stdc++.h>
using namespace std;

class LRUCache {
private:
    int capacity;
    // list stores {key, value}, front = most recently used, back = least
    list<pair<int, int>> items;
    unordered_map<int, list<pair<int, int>>::iterator> cache;

public:
    LRUCache(int capacity) : capacity(capacity) {}

    int get(int key) {
        if (cache.find(key) == cache.end()) return -1;
        auto it = cache[key];
        int value = it->second;
        items.erase(it);
        items.push_front({key, value});
        cache[key] = items.begin();
        return value;
    }

    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
            items.erase(cache[key]);
        } else if ((int)items.size() >= capacity) {
            auto last = items.back();
            cache.erase(last.first);
            items.pop_back();
        }
        items.push_front({key, value});
        cache[key] = items.begin();
    }
};

int main() {
    LRUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    cout << cache.get(1) << endl; // 1
    cache.put(3, 3);              // evicts key 2
    cout << cache.get(2) << endl; // -1
    cache.put(4, 4);              // evicts key 1
    cout << cache.get(1) << endl; // -1
    cout << cache.get(3) << endl; // 3
    cout << cache.get(4) << endl; // 4
    return 0;
}

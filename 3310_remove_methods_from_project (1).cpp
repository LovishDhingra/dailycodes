// 3310. Remove Methods From Project
// https://leetcode.com/problems/remove-methods-from-project/

#include <bits/stdc++.h>
using namespace std;

// ---------- Brute Force: Transitive Closure (Floyd-Warshall style) ----------
class SolutionBruteForce {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        vector<vector<bool>> reach(n, vector<bool>(n, false));
        for (auto& inv : invocations) {
            reach[inv[0]][inv[1]] = true;
        }
        for (int i = 0; i < n; i++) reach[i][i] = true;

        for (int mid = 0; mid < n; mid++) {
            for (int i = 0; i < n; i++) {
                if (reach[i][mid]) {
                    for (int j = 0; j < n; j++) {
                        if (reach[mid][j]) reach[i][j] = true;
                    }
                }
            }
        }

        vector<bool> suspicious(n, false);
        for (int j = 0; j < n; j++) {
            if (reach[k][j]) suspicious[j] = true;
        }

        for (auto& inv : invocations) {
            int a = inv[0], b = inv[1];
            if (suspicious[b] && !suspicious[a]) {
                vector<int> all(n);
                iota(all.begin(), all.end(), 0);
                return all;
            }
        }

        vector<int> result;
        for (int i = 0; i < n; i++) {
            if (!suspicious[i]) result.push_back(i);
        }
        return result;
    }
};

// ---------- Optimal: Single BFS/DFS + Edge Validation ----------
class SolutionOptimal {
public:
    void dfs(int node, vector<vector<int>>& graph, vector<bool>& visited) {
        visited[node] = true;
        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor, graph, visited);
            }
        }
    }

    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        vector<vector<int>> graph(n);
        for (auto& inv : invocations) {
            graph[inv[0]].push_back(inv[1]);
        }

        vector<bool> suspicious(n, false);
        dfs(k, graph, suspicious);

        for (auto& inv : invocations) {
            int a = inv[0], b = inv[1];
            if (suspicious[b] && !suspicious[a]) {
                vector<int> all(n);
                iota(all.begin(), all.end(), 0);
                return all;
            }
        }

        vector<int> result;
        for (int i = 0; i < n; i++) {
            if (!suspicious[i]) result.push_back(i);
        }
        return result;
    }
};

int main() {
    SolutionOptimal s;
    vector<vector<int>> invocations = {{1,2},{0,1},{3,2}};
    vector<int> result = s.remainingMethods(4, 1, invocations);
    for (int x : result) cout << x << " "; // 0 1 2 3
    cout << endl;
    return 0;
}

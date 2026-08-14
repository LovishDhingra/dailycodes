// Problem: Course Schedule
// Given numCourses and prerequisite pairs [a, b] (must take b before a),
// determine if it's possible to finish all courses (i.e., no cycle).
// Approach: Topological sort via Kahn's algorithm (BFS with in-degrees).
// Time: O(V + E)   Space: O(V + E)

#include <bits/stdc++.h>
using namespace std;

bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> adj(numCourses);
    vector<int> indegree(numCourses, 0);

    for (auto& pr : prerequisites) {
        int course = pr[0], prereq = pr[1];
        adj[prereq].push_back(course);
        indegree[course]++;
    }

    queue<int> q;
    for (int i = 0; i < numCourses; i++) {
        if (indegree[i] == 0) q.push(i);
    }

    int visited = 0;
    while (!q.empty()) {
        int node = q.front(); q.pop();
        visited++;
        for (int next : adj[node]) {
            if (--indegree[next] == 0) q.push(next);
        }
    }

    return visited == numCourses; // true if no cycle
}

int main() {
    int numCourses = 4;
    vector<vector<int>> prerequisites = {{1, 0}, {2, 0}, {3, 1}, {3, 2}};
    cout << "Can finish: " << (canFinish(numCourses, prerequisites) ? "true" : "false") << endl;
    return 0;
}

// 547. Number of Provinces
// https://leetcode.com/problems/number-of-provinces/

import java.util.*;

public class Solution547_NumberOfProvinces {

    // ---------- Brute Force: naive Union-Find (no path compression / rank) ----------
    static class SolutionBruteForce {
        int[] parent;

        private int find(int x) {
            while (parent[x] != x) x = parent[x];
            return x;
        }

        private void union(int x, int y) {
            int rootX = find(x), rootY = find(y);
            if (rootX != rootY) parent[rootX] = rootY;
        }

        public int findCircleNum(int[][] isConnected) {
            int n = isConnected.length;
            parent = new int[n];
            for (int i = 0; i < n; i++) parent[i] = i;

            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if (isConnected[i][j] == 1) union(i, j);

            Set<Integer> roots = new HashSet<>();
            for (int i = 0; i < n; i++) roots.add(find(i));
            return roots.size();
        }
    }

    // ---------- Optimal 1: DFS ----------
    static class SolutionDFS {
        private void dfs(int city, int[][] isConnected, boolean[] visited) {
            visited[city] = true;
            for (int neighbor = 0; neighbor < isConnected.length; neighbor++) {
                if (isConnected[city][neighbor] == 1 && !visited[neighbor]) {
                    dfs(neighbor, isConnected, visited);
                }
            }
        }

        public int findCircleNum(int[][] isConnected) {
            int n = isConnected.length;
            boolean[] visited = new boolean[n];
            int provinces = 0;

            for (int city = 0; city < n; city++) {
                if (!visited[city]) {
                    provinces++;
                    dfs(city, isConnected, visited);
                }
            }
            return provinces;
        }
    }

    // ---------- Optimal 2: Union-Find with path compression + union by rank ----------
    static class SolutionUnionFind {
        int[] parent, rank_;
        int provinces;

        private int find(int x) {
            if (parent[x] != x) parent[x] = find(parent[x]);
            return parent[x];
        }

        private void union(int x, int y) {
            int rootX = find(x), rootY = find(y);
            if (rootX == rootY) return;
            if (rank_[rootX] < rank_[rootY]) { int t = rootX; rootX = rootY; rootY = t; }
            parent[rootY] = rootX;
            if (rank_[rootX] == rank_[rootY]) rank_[rootX]++;
            provinces--;
        }

        public int findCircleNum(int[][] isConnected) {
            int n = isConnected.length;
            parent = new int[n];
            rank_ = new int[n];
            provinces = n;
            for (int i = 0; i < n; i++) parent[i] = i;

            for (int i = 0; i < n; i++)
                for (int j = i + 1; j < n; j++)
                    if (isConnected[i][j] == 1) union(i, j);

            return provinces;
        }
    }

    public static void main(String[] args) {
        SolutionDFS s = new SolutionDFS();
        int[][] isConnected = {{1,1,0},{1,1,0},{0,0,1}};
        System.out.println(s.findCircleNum(isConnected)); // 2
    }
}

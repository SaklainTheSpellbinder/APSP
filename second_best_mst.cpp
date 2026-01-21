#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v, w, id;
};

struct DSU {
    vector<int> parent;
    DSU(int n) {
        parent.resize(n + 1);
        for (int i = 1; i <= n; i++) parent[i] = i;
    }
    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }
    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
            return true;
        }
        return false;
    }
};

bool compareEdges(Edge a, Edge b) {
    return a.w < b.w;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        edges[i].id = i;
    }

    sort(edges.begin(), edges.end(), compareEdges);

    // Step 1: Find the initial MST
    DSU dsu1(n);
    long long mst_weight = 0;
    vector<int> mst_edges;
    for (int i = 0; i < m; i++) {
        if (dsu1.unite(edges[i].u, edges[i].v)) {
            mst_weight += edges[i].w;
            mst_edges.push_back(i); // Store indices of edges in MST
        }
    }

    // Step 2: Find Second Best MST by skipping one MST edge at a time
    long long second_mst_weight = 2e18; // Use a very large value

    for (int skip_idx : mst_edges) {
        DSU dsu2(n);
        long long current_weight = 0;
        int edges_count = 0;

        for (int i = 0; i < m; i++) {
            if (i == skip_idx) continue; // The "Brute Force" skip

            if (dsu2.unite(edges[i].u, edges[i].v)) {
                current_weight += edges[i].w;
                edges_count++;
            }
        }

        // Only update if we successfully formed a spanning tree (V-1 edges)
        if (edges_count == n - 1) {
            second_mst_weight = min(second_mst_weight, current_weight);
        }
    }

    cout << "MST: " << mst_weight << endl;
    cout << "Second MST: " << second_mst_weight << endl;

    return 0;
}
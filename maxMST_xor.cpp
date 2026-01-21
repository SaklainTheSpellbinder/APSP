#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent a game (edge)
struct Edge {
    int u, v;
    long long weight;
};

// Disjoint Set Union to track connected teams
struct DSU {
    vector<int> parent;
    DSU(int n) {
        parent.resize(n);
        for (int i = 0; i < n; ++i) parent[i] = i;
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

int main() {
    int N;
    if (!(cin >> N)) return 0;

    vector<long long> ids(N);
    for (int i = 0; i < N; ++i) {
        cin >> ids[i];
    }

    // Generate all possible matches and their scores
    vector<Edge> edges;
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            edges.push_back({i, j, ids[i] ^ ids[j]});
        }
    }

    // Sort edges by weight descending to find the Maximum Spanning Tree
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight > b.weight;
    });

    DSU dsu(N);
    long long total_points = 0;
    int edges_count = 0;

    for (const auto& edge : edges) {
        if (dsu.unite(edge.u, edge.v)) {
            total_points += edge.weight;
            edges_count++;
            // A spanning tree for N nodes has N-1 edges
            if (edges_count == N - 1) break;
        }
    }

    cout << total_points << endl;

    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to store edge information
struct Edge {
    int u, v, w;
};

// DSU structure for cycle detection and component merging
struct DSU {
    vector<int> parent;
    int components;

    DSU(int n) {
        parent.resize(n + 1);
        for (int i = 1; i <= n; i++) parent[i] = i;
        components = n;
    }

    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }

    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
            components--;
        }
    }
};

bool compareEdges(const Edge& a, const Edge& b) {
    return a.w < b.w;
}

int main() {
    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    // Sort edges by latency to enable the sliding window
    sort(edges.begin(), edges.end(), compareEdges);

    int min_range = 2e9; // Initialize with a very large value
    bool possible = false;

    // Sliding window: try each edge as the smallest latency in the network
    for (int i = 0; i < m; i++) {
        DSU dsu(n);
        
        for (int j = i; j < m; j++) {
            dsu.unite(edges[j].u, edges[j].v);

            // Once the network is fully connected, check the range
            if (dsu.components == 1) {
                min_range = min(min_range, edges[j].w - edges[i].w);
                possible = true;
                break; // Moving i will only require a different j
            }
        }
    }

    if (possible) cout << min_range << endl;
    else cout << -1 << endl; // Or any error value if graph cannot be connected

    return 0;
}
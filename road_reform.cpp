#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

// Disjoint Set Union (DSU) for Kruskal's Algorithm
struct DSU {
    vector<int> parent;
    DSU(int n) {
        parent.resize(n + 1);
        iota(parent.begin(), parent.end(), 0);
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

struct Edge {
    int u, v;
    long long s, w;
};

void solve() {
    int n, m;
    long long k;
    if (!(cin >> n >> m >> k)) return;

    vector<Edge> edges(m);
    long long min_abs_diff = 2e18; // Large value for comparison

    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].s;
        // The cost contribution of an edge to the "sum of reductions"
        edges[i].w = max(0LL, edges[i].s - k);
        // Track the overall closest edge to k
        min_abs_diff = min(min_abs_diff, abs(edges[i].s - k));
    }

    // Sort edges by their cost contribution (edges <= k are treated as 0)
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.w < b.w;
    });

    DSU dsu(n);
    long long mst_weight = 0;
    for (int i = 0; i < m; ++i) {
        if (dsu.unite(edges[i].u, edges[i].v)) {
            mst_weight += edges[i].w;
        }
    }

    // If mst_weight > 0, every ST must use an edge > k. MST weight is the answer.
    // If mst_weight == 0, a tree with all edges <= k exists. Use the closest edge to k.
    if (mst_weight > 0) {
        cout << mst_weight << "\n";
    } else {
        cout << min_abs_diff << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    if (!(cin >> t)) return 0;
    while (t--) solve();
    return 0;
}
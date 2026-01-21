#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

struct Edge {
    int from, to;
    ll w;
    bool operator<(const Edge &other) const {
        return w < other.w;
    }
};

class DSU {
    vector<int> parent;
public:
    DSU(int n) {
        parent.resize(n + 1);
        for (int i = 1; i <= n; i++) parent[i] = i;
    }
    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }
    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            parent[rootX] = rootY;
            return true;
        }
        return false;
    }
};

// Standard Kruskal's (Assumes edges are already sorted)
ll KRUSKAL(const vector<Edge> &sorted_edges, int n) {
    ll total = 0;
    DSU dsu(n);
    int count = 0;
    for (const auto &e : sorted_edges) {
        if (dsu.unite(e.from, e.to)) {
            total += e.w;
            count++;
        }
    }
    return (count == n - 1) ? total : -1; // Return -1 if not connected
}

// Forced Edge Kruskal's (Assumes edges are already sorted)
ll kruskal_forced(const vector<Edge> &sorted_edges, int n, Edge forced) {
    ll total = forced.w;
    DSU dsu(n);
    dsu.unite(forced.from, forced.to);
    
    int count = 1;
    for (const auto &e : sorted_edges) {
        if (dsu.unite(e.from, e.to)) {
            total += e.w;
            count++;
        }
    }
    return (count == n - 1) ? total : -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<Edge> input_order(m);
    for (int i = 0; i < m; i++) {
        cin >> input_order[i].from >> input_order[i].to >> input_order[i].w;
    }

    vector<Edge> sorted_edges = input_order;
    sort(sorted_edges.begin(), sorted_edges.end());

    ll mst_weight = KRUSKAL(sorted_edges, n);

    for (int i = 0; i < m; i++) {
        ll weight_with_forced = kruskal_forced(sorted_edges, n, input_order[i]);
        if (weight_with_forced == mst_weight) cout << "YES" << endl;
        else cout << "NO" << endl;
    }

    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v, w;
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

struct DSU {
    vector<int> parent;
    int components;
    DSU(int n) {
        parent.resize(n);
        for (int i = 0; i < n; i++) parent[i] = i;
        components = n;
    }
    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }
    bool unite(int i, int j) {
        int root_i = find(i), root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
            components--;
            return true;
        }
        return false;
    }
};

void solve(int t_case) {
    int n;
    cin >> n;
    long long total_wire = 0;
    vector<Edge> edges;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int w;
            cin >> w;
            if (w > 0) {
                total_wire += w;
                // Add an edge between room i and j
                // Note: We include self-loops in total_wire but 
                // they aren't useful for MST (unite(i, i) is always false)
                edges.push_back({i, j, w});
            }
        }
    }

    sort(edges.begin(), edges.end());

    DSU dsu(n);
    long long mst_weight = 0;
    int edges_used = 0;

    for (auto &e : edges) {
        if (dsu.unite(e.u, e.v)) {
            mst_weight += e.w;
            edges_used++;
        }
    }

    cout << "Case " << t_case << ": ";
    if (edges_used == n - 1 || n == 1) {
        cout << total_wire - mst_weight << endl;
    } else {
        cout << -1 << endl;
    }
}

int main() {
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }
    return 0;
}

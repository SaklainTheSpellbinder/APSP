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
        parent.resize(n + 1);
        for (int i = 1; i <= n; i++) parent[i] = i;
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
    int n, m, a;
    cin >> n >> m >> a;
    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    sort(edges.begin(), edges.end());

    DSU dsu(n);
    long long road_cost = 0;

    for (int i = 0; i < m; i++) {
        // Only use roads that are cheaper than building a new airport
        if (edges[i].w < a) {
            if (dsu.unite(edges[i].u, edges[i].v)) {
                road_cost += edges[i].w;
            }
        }
    }

    long long total_cost = road_cost + (1LL * dsu.components * a);
    cout << "Case #" << t_case << ": " << total_cost << " " << dsu.components << endl;
}

int main() {
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }
    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v, w;
};

// Standard DSU
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
        int root_i = find(i), root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
            return true;
        }
        return false;
    }
};

void solve(int t_case) {
    int N, W;
    if (!(cin >> N >> W)) return;
    
    vector<Edge> current_mst_edges;
    cout << "Case " << t_case << ":" << endl;

    for (int i = 0; i < W; i++) {
        Edge new_edge;
        cin >> new_edge.u >> new_edge.v >> new_edge.w;
        current_mst_edges.push_back(new_edge);

        // Sort only the current candidate edges (at most N)
        sort(current_mst_edges.begin(), current_mst_edges.end(), [](Edge a, Edge b) {
            return a.w < b.w;
        });

        DSU dsu(N);
        vector<Edge> next_mst_edges;
        long long total_weight = 0;

        for (auto &e : current_mst_edges) {
            if (dsu.unite(e.u, e.v)) {
                total_weight += e.w;
                next_mst_edges.push_back(e);
            }
        }

        // Update our running candidate list to only include edges from the new MST
        current_mst_edges = next_mst_edges;

        if (current_mst_edges.size() == N - 1) {
            cout << total_weight << endl;
        } else {
            cout << -1 << endl;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }
    return 0;
}

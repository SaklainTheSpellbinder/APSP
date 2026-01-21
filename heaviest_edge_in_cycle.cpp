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
    DSU(int n) {
        parent.resize(n);
        for (int i = 0; i < n; i++) parent[i] = i;
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
    int n, m;
    while (cin >> n >> m && (n != 0 || m != 0)) {
        vector<Edge> edges(m);
        for (int i = 0; i < m; i++) {
            cin >> edges[i].u >> edges[i].v >> edges[i].w;
        }

        sort(edges.begin(), edges.end());

        DSU dsu(n);
        vector<int> heaviest_edges;

        for (int i = 0; i < m; i++) {
            // If u and v are already connected, this edge is the 
            // heaviest edge in the cycle it completes.
            if (dsu.find(edges[i].u) == dsu.find(edges[i].v)) {
                heaviest_edges.push_back(edges[i].w);
            } else {
                dsu.unite(edges[i].u, edges[i].v);
            }
        }

        if (heaviest_edges.empty()) {
            cout << "forest" << endl;
        } else {
            sort(heaviest_edges.begin(), heaviest_edges.end());
            for (int i = 0; i < heaviest_edges.size(); i++) {
                cout << heaviest_edges[i] << (i == heaviest_edges.size() - 1 ? "" : " ");
            }
            cout << endl;
        }
    }
    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Planet {
    int x, y, z, id;
};

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
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<Planet> planets(n);
    for (int i = 0; i < n; i++) {
        cin >> planets[i].x >> planets[i].y >> planets[i].z;
        planets[i].id = i;
    }

    vector<Edge> candidate_edges;

    // Sort by X and add adjacent edges
    sort(planets.begin(), planets.end(), [](Planet a, Planet b) {
        return a.x < b.x;
    });
    for (int i = 0; i < n - 1; i++) {
        candidate_edges.push_back({planets[i].id, planets[i + 1].id, abs(planets[i].x - planets[i + 1].x)});
    }

    // Sort by Y and add adjacent edges
    sort(planets.begin(), planets.end(), [](Planet a, Planet b) {
        return a.y < b.y;
    });
    for (int i = 0; i < n - 1; i++) {
        candidate_edges.push_back({planets[i].id, planets[i + 1].id, abs(planets[i].y - planets[i + 1].y)});
    }

    // Sort by Z and add adjacent edges
    sort(planets.begin(), planets.end(), [](Planet a, Planet b) {
        return a.z < b.z;
    });
    for (int i = 0; i < n - 1; i++) {
        candidate_edges.push_back({planets[i].id, planets[i + 1].id, abs(planets[i].z - planets[i + 1].z)});
    }

    // Standard Kruskal's
    sort(candidate_edges.begin(), candidate_edges.end());

    DSU dsu(n);
    long long min_total_cost = 0;
    int edges_count = 0;

    for (const auto& edge : candidate_edges) {
        if (dsu.unite(edge.u, edge.v)) {
            min_total_cost += edge.w;
            edges_count++;
            if (edges_count == n - 1) break;
        }
    }

    cout << min_total_cost << endl;

    return 0;
}
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define nl "\n"
#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(0);

const ll INF = 1e15;

int main() {
    FAST_IO;
    int n, m;
    cin >> n >> m; // 

    vector<vector<ll>> dist(n, vector<ll>(n, INF));
    for (int i = 0; i < n; i++) dist[i][i] = 0;

    // Original graph input [cite: 9]
    vector<pair<pair<int, int>, ll>> edges;
    for (int i = 0; i < m; i++) {
        int u, v; ll w;
        cin >> u >> v >> w;
        dist[u][v] = min(dist[u][v], w);
        edges.push_back({{u, v}, w});
    }

    // Standard Floyd-Warshall to get base distances
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] < INF && dist[k][j] < INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    int forbidden_u, forbidden_v;
    cin >> forbidden_u >> forbidden_v; // The edge to be ignored

    ll min_path_without_edge = INF;
    int start_node, end_node;
    cin >> start_node >> end_node;

    // Logic: Iterate over all OTHER edges to find a detour
    for (auto &edge : edges) {
        int u = edge.first.first;
        int v = edge.first.second;
        ll w = edge.second;

        // Skip the forbidden edge
        if (u == forbidden_u && v == forbidden_v) continue;

        // Check path: Start -> u -> v -> End
        if (dist[start_node][u] < INF && dist[v][end_node] < INF) {
            min_path_without_edge = min(min_path_without_edge, 
                                        dist[start_node][u] + w + dist[v][end_node]);
        }
    }

    if (min_path_without_edge >= INF) cout << -1 << nl; // [cite: 14]
    else cout << min_path_without_edge << nl;

    return 0;
}
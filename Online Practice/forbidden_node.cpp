#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(0);

const ll INF = 1e15;

int main() {
    FAST_IO;
    int n, m;
    cin >> n >> m; // n cities, m roads 

    vector<vector<ll>> dist(n, vector<ll>(n, INF));
    for (int i = 0; i < n; i++) dist[i][i] = 0;

    for (int i = 0; i < m; i++) {
        int u, v; ll w;
        cin >> u >> v >> w; // direct road cost [cite: 38]
        dist[u][v] = min(dist[u][v], w); 
    }

    int forbidden_node;
    cin >> forbidden_node; // The city that is blocked

    // Floyd-Warshall skipping the forbidden node
    for (int k = 0; k < n; k++) {
        // SKIP if k is the forbidden node
        if (k == forbidden_node) continue;

        for (int i = 0; i < n; i++) {
            // ALSO SKIP if start or end is the forbidden node
            if (i == forbidden_node) continue;

            for (int j = 0; j < n; j++) {
                if (j == forbidden_node) continue;

                if (dist[i][k] < INF && dist[k][j] < INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    int q; cin >> q; // q queries [cite: 40]
    while (q--) {
        int a, b; cin >> a >> b;
        if (a == forbidden_node || b == forbidden_node || dist[a][b] >= INF) {
            cout << -1 << "\n"; // No route possible [cite: 43]
        } else {
            cout << dist[a][b] << "\n";
        }
    }
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define nl "\n"
#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(0);

const ll INF = 1e18;

// Function to print the path from the parent matrix
void printPath(int i, int j, vector<vector<int>>& parent) {
    if (i == j) {
        cout << i;
    } else if (parent[i][j] == -1) {
        cout << "No path";
    } else {
        printPath(i, parent[i][j], parent);
        cout << " -> " << j;
    }
}

int main() {
    FAST_IO;
    int n, m;
    cin >> n >> m; // n cities, m roads [cite: 8, 37]

    vector<vector<ll>> dist(n, vector<ll>(n, INF));
    vector<vector<int>> parent(n, vector<int>(n, -1));

    for (int i = 0; i < n; i++) dist[i][i] = 0;

    for (int i = 0; i < m; i++) {
        int u, v; ll w;
        cin >> u >> v >> w; // direct road with cost [cite: 3, 33]
        if (w < dist[u][v]) {
            dist[u][v] = w;
            parent[u][v] = u; // Initial parent is the starting node
        }
    }

    // Minimax Floyd-Warshall with Path Tracking
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                ll bottleneck_via_k = max(dist[i][k], dist[k][j]);
                
                // This IS the relaxation step for Minimax
                if (bottleneck_via_k < dist[i][j]) {
                    dist[i][j] = bottleneck_via_k;
                    parent[i][j] = parent[k][j]; // Update the path link
                }
            }
        }
    }

    int q; cin >> q; // Number of queries [cite: 11, 40]
    while (q--) {
        int a, b; cin >> a >> b;
        if (dist[a][b] == INF) {
            cout << -1 << nl; // No route exists [cite: 14, 43]
        } else {
            cout << "Bottleneck Cost: " << dist[a][b] << " | Path: ";
            printPath(a, b, parent);
            cout << nl;
        }
    }

    return 0;
}
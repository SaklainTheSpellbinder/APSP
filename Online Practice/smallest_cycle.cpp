#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;
const ll INF = 1e15;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<ll>> dist(n + 1, vector<ll>(n + 1, INF));
    vector<vector<ll>> adj(n + 1, vector<ll>(n + 1, INF)); // Store original weights

    for (int i = 1; i <= n; i++) dist[i][i] = 0;

    for (int i = 0; i < m; i++) {
        int u, v; ll w;
        cin >> u >> v >> w;
        dist[u][v] = min(dist[u][v], w);
        adj[u][v] = min(adj[u][v], w); // Keep original weights for cycle check
    }

    ll shortestCycle = INF;

    for (int k = 1; k <= n; k++) {
        // 1. Check for cycles using node k as the 'top' of the cycle
        for (int i = 1; i < k; i++) {
            for (int j = 1; j < k; j++) {
                if (i != j && dist[i][j] != INF && adj[j][k] != INF && adj[k][i] != INF) {
                    shortestCycle = min(shortestCycle, dist[i][j] + adj[j][k] + adj[k][i]);
                }
            }
        }

        // 2. Standard Floyd-Warshall update
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    if (shortestCycle >= INF) cout << "No Cycle" << endl;
    else cout << "Shortest Cycle (Girth): " << shortestCycle << endl;

    return 0;
}
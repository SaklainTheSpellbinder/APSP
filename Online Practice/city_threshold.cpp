#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define nl "\n"
#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(0);

const ll INF = 1e15;

int main() {
    FAST_IO;
    int n, m;
    // Input n (cities) and m (roads) [cite: 17]
    if (!(cin >> n >> m)) return 0;

    // Initialize distance matrix [cite: 90]
    vector<vector<ll>> dist(n + 1, vector<ll>(n + 1, INF));
    for (int i = 1; i <= n; i++) dist[i][i] = 0;

    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        // Roads are bidirectional [cite: 12]
        // Maintain the minimum weight for multiple edges [cite: 17]
        if (w < dist[u][v]) {
            dist[u][v] = dist[v][u] = w;
        }
    }

    // Input the threshold cost [cite: 18]
    ll threshold;
    cin >> threshold;

    // Standard Floyd-Warshall to determine the distance matrix [cite: 93]
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][k] < INF && dist[k][j] < INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    // Task: find city with smallest number of reachable cities within threshold [cite: 14]
    vector<int> reachable_count(n + 1, 0);
    int min_reachable = n + 1;

    for (int i = 1; i <= n; i++) {
        int count = 0;
        for (int j = 1; j <= n; j++) {
            // Count city j if reachable within threshold 
            if (i != j && dist[i][j] <= threshold) {
                count++;
            }
        }
        reachable_count[i] = count;
        if (count < min_reachable) {
            min_reachable = count;
        }
    }

    // Output all cities with the minimum count [cite: 21]
    bool first = true;
    for (int i = 1; i <= n; i++) {
        if (reachable_count[i] == min_reachable) {
            if (!first) cout << " ";
            cout << i;
            first = false;
        }
    }
    cout << nl;

    return 0;
}
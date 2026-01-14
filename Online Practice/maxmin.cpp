#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define nl "\n"
#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(0);

// For Maximin, INF is used for the starting/diagonal capacity
const ll INF = 1e18; 

int main() {
    FAST_IO;
    int n, m;
    if(!(cin >> n >> m)) return 0; // cities and roads [cite: 37]

    // Initialize: Default capacity between any two cities is 0
    vector<vector<ll>> dist(n + 1, vector<ll>(n + 1, 0));
    for (int i = 0; i <= n; i++) dist[i][i] = INF;

    for (int i = 0; i < m; i++) {
        int u, v; ll w;
        cin >> u >> v >> w; // road from a to b with capacity c 
        // If multiple roads exist, we take the one with the highest capacity
        dist[u][v] = max(dist[u][v], w); 
    }

    int Y, Z; cin >> Y >> Z; // Mandatory distribution centers [cite: 39]

    // Maximin Floyd-Warshall Triple Loop
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                // Potential capacity via city k is the minimum of the two legs
                ll capacity_via_k = min(dist[i][k], dist[k][j]);
                
                // Relaxation: Update if we find a path with a better bottleneck
                if (capacity_via_k > dist[i][j]) {
                    dist[i][j] = capacity_via_k;
                }
            }
        }
    }

    int q; cin >> q; // Number of queries [cite: 40]
    while (q--) {
        int a, b; cin >> a >> b; // Query cities [cite: 41]
        
        // Final Path must include Y or Z [cite: 35]
        ll cap_via_Y = min(dist[a][Y], dist[Y][b]);
        ll cap_via_Z = min(dist[a][Z], dist[Z][b]);

        ll result = max(cap_via_Y, cap_via_Z);

        if (result == 0) cout << -1 << nl; // No route exists [cite: 43]
        else cout << result << nl;
    }

    return 0;
}
#include <bits/stdc++.h>
using namespace std;

#define nl "\n"
#define ll long long
#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(0);

const ll INF = 1e15;

void solve(int caseNum) {
    int n, m, p;
    cin >> n >> m >> p;

    // Use long long for distances to prevent overflow during weight calculation
    vector<vector<ll>> dist(n, vector<ll>(n, INF));
    for (int i = 0; i < n; i++) dist[i][i] = 0;

    for (int i = 0; i < m; i++) {
        int u, v, income, cost;
        cin >> u >> v >> cost >> income;
        
        // Weight transformation: (Cost * P) - Income
        ll weight = (ll)cost * p - income;
        
        // Handle multiple edges between same cities
        if (weight < dist[u][v]) {
            dist[u][v] = weight;
        }
    }

    // Standard Floyd-Warshall
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] < INF && dist[k][j] < INF) {
                    if (dist[i][j] > dist[i][k] + dist[k][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }

    // Check for Negative Cycle
    // If any node can reach itself with a cost < 0, a negative cycle exists
    bool possible = false;
    for (int i = 0; i < n; i++) {
        if (dist[i][i] < 0) {
            possible = true;
            break;
        }
    }

    cout << "Case " << caseNum << ": " << (possible ? "YES" : "NO") << nl;
}

int main() {
    FAST_IO;
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }
    return 0;
}
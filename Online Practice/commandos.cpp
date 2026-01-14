#include <bits/stdc++.h>
using namespace std;

#define nl "\n"
#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(0);

const int INF = 1e8;

void solve(int caseNum) {
    int n, m;
    cin >> n >> m;

    // Initialize distance matrix
    vector<vector<int>> dist(n, vector<int>(n, INF));
    for (int i = 0; i < n; i++) dist[i][i] = 0;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        // Bidirectional roads
        dist[u][v] = dist[v][u] = 1; 
    }

    // Floyd-Warshall
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    int s, d;
    cin >> s >> d;

    int max_time = 0;
    // For every possible city 'i' that a commando could visit
    for (int i = 0; i < n; i++) {
        // The total time for that specific commando is dist(s,i) + dist(i,d)
        if (dist[s][i] != INF && dist[i][d] != INF) {
            max_time = max(max_time, dist[s][i] + dist[i][d]);
        }
    }

    cout << "Case " << caseNum << ": " << max_time << nl;
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
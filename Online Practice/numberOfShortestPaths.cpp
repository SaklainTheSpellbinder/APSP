#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;
const ll INF = 1e18;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<ll>> dist(n + 1, vector<ll>(n + 1, INF));
    vector<vector<ll>> count(n + 1, vector<ll>(n + 1, 0));

    for (int i = 1; i <= n; i++) {
        dist[i][i] = 0;
        count[i][i] = 1;
    }

    for (int i = 0; i < m; i++) {
        int u, v; ll w;
        cin >> u >> v >> w;
        if (w < dist[u][v]) {
            dist[u][v] = w;
            count[u][v] = 1; // Initial shortest path count
        } else if (w == dist[u][v]) {
            count[u][v]++; // Another edge of the same weight
        }
    }

    // Floyd-Warshall with Counting
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    ll new_dist = dist[i][k] + dist[k][j];
                    ll new_ways = count[i][k] * count[k][j];

                    if (new_dist < dist[i][j]) {
                        // Found a strictly shorter path
                        dist[i][j] = new_dist;
                        count[i][j] = new_ways;
                    } else if (new_dist == dist[i][j]) {
                        // Found another path of the same minimum length
                        count[i][j] += new_ways;
                    }
                }
            }
        }
    }

    int q; cin >> q;
    while (q--) {
        int a, b; cin >> a >> b;
        if (dist[a][b] == INF) cout << "No path" << endl;
        else cout << "Min Distance: " << dist[a][b] << " | Ways: " << count[a][b] << endl;
    }

    return 0;
}
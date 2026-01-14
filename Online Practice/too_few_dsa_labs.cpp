#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define nl "\n"
#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(0);

const ll INF = 1e15;

int main() {
    FAST_IO;
    int n, m, k_students;
    if (!(cin >> n >> m >> k_students)) return 0;

    vector<int> capacity(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> capacity[i];
    }

    // Initialize distance matrix
    vector<vector<ll>> dist(n + 1, vector<ll>(n + 1, INF));
    
    // Rule: Students can't pass through a lab that is under maintenance 
    for (int i = 1; i <= n; i++) {
        if (capacity[i] != -1) {
            dist[i][i] = 0;
        }
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        // Edge only exists if both labs are operational 
        if (capacity[u] != -1 && capacity[v] != -1) {
            dist[u][v] = dist[v][u] = min(dist[u][v], w);
        }
    }

    // Standard Floyd-Warshall to find all-pairs shortest paths 
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][k] < INF && dist[k][j] < INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    int q;
    cin >> q;
    while (q--) {
        int start_lab;
        cin >> start_lab;
        
        // We need a temporary capacity vector for each query to simulate students entering one by one 
        vector<int> current_cap = capacity;
        
        for (int s = 0; s < k_students; s++) {
            ll best_cost = INF;
            int target_lab = -1;

            // Find the best lab: minimum walking cost and has remaining space 
            for (int j = 1; j <= n; j++) {
                if (current_cap[j] > 0 && dist[start_lab][j] < best_cost) {
                    best_cost = dist[start_lab][j];
                    target_lab = j;
                }
            }

            if (target_lab != -1) {
                cout << best_cost << (s == k_students - 1 ? "" : " ");
                current_cap[target_lab]--; // Reduce capacity as student chooses the lab 
            } else {
                cout << -1 << (s == k_students - 1 ? "" : " ");
            }
        }
        cout << nl;
    }

    return 0;
}
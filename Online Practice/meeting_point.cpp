#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define nl "\n"
#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(0);

const ll INF = 1e15; 

int main() {
    FAST_IO;
    int n, m;
    if (!(cin >> n >> m)) return 0;

    // 1. Initialize Distance Matrix based on PDF road costs
    // n can be up to 500 [cite: 8, 37]
    vector<vector<ll>> dist(n + 1, vector<ll>(n + 1, INF));
    for (int i = 0; i <= n; i++) dist[i][i] = 0;

    for (int i = 0; i < m; i++) {
        int u, v;
        ll cost;
        cin >> u >> v >> cost; // Road cost (fuel/tolls) 
        dist[u][v] = min(dist[u][v], cost); 
    }

    // 2. Standard Floyd-Warshall to find all-pairs shortest costs 
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] < INF && dist[k][j] < INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    // 3. Input Logistics Priorities (Volume of goods per city)
    // This represents the "Hourly Rate" logic in the logistics context.
    vector<int> volume(n);
    for (int i = 0; i < n; i++) {
        cin >> volume[i]; 
    }

    // 4. Find the Optimal Distribution City (K)
    ll min_total_logistic_cost = INF;
    int optimal_city = -1;

    // Check every city 'k' as the potential distribution center
    for (int k = 0; k < n; k++) {
        ll current_cost = 0;
        bool all_reachable = true;

        for (int i = 0; i < n; i++) {
            if (dist[i][k] == INF) {
                all_reachable = false;
                break;
            }
            // Cost = Distance from city i to Center k * Volume at city i
            current_cost += (dist[i][k] * (ll)volume[i]);
        }

        if (all_reachable && current_cost < min_total_logistic_cost) {
            min_total_logistic_cost = current_cost;
            optimal_city = k;
        }
    }

    // 5. Final Output 
    if (optimal_city == -1) {
        cout << -1 << nl;
    } else {
        cout << "Optimal Logistics Hub: " << optimal_city << nl;
        cout << "Minimum Total Weighted Cost: " << min_total_logistic_cost << nl;
    }

    return 0;
}
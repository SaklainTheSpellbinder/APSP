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

    // dist stores cost, edges stores number of roads on that path
    vector<vector<ll>> dist(n, vector<ll>(n, INF));
    vector<vector<int>> edges(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) dist[i][i] = 0;

    for (int i = 0; i < m; i++) {
        int u, v; ll c;
        cin >> u >> v >> c;
        if (c < dist[u][v]) {
            dist[u][v] = c;
            edges[u][v] = 1; // Direct road is 1 edge
        }
    }

    int V; cin >> V; // Quality Control Center city [cite: 10]

    // 1. Standard Floyd-Warshall to fill all-pairs distance and edge counts
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] < INF && dist[k][j] < INF) {
                    if (dist[i][j] > dist[i][k] + dist[k][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        edges[i][j] = edges[i][k] + edges[k][j];
                    }
                }
            }
        }
    }

    // 2. Input City Volumes (Weights/Hourly Rates)
    vector<int> volume(n);
    for (int i = 0; i < n; i++) cin >> volume[i];

    // 3. Find the Hub K that minimizes weighted cost including the V discount
    ll min_total_cost = INF;
    int best_hub = -1;

    for (int k = 0; k < n; k++) {
        ll current_hub_cost = 0;
        bool reachable = true;

        for (int i = 0; i < n; i++) {
            // Path without discount
            ll cost_to_k = dist[i][k];

            // Path with discount if we pass through V 
            if (dist[i][V] < INF && dist[V][k] < INF) {
                ll discounted_cost = (dist[i][V] + dist[V][k]) - (edges[i][V] + edges[V][k]);
                cost_to_k = min(cost_to_k, discounted_cost);
            }

            if (cost_to_k >= INF) {
                reachable = false;
                break;
            }
            current_hub_cost += (cost_to_k * (ll)volume[i]);
        }

        if (reachable && current_hub_cost < min_total_cost) {
            min_total_cost = current_hub_cost;
            best_hub = k;
        }
    }

    if (best_hub == -1) cout << -1 << nl;
    else {
        cout << "Optimal Hub: " << best_hub << nl;
        cout << "Total Weighted Cost: " << min_total_cost << nl;
    }

    return 0;
}
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define nl "\n"
#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(0);

const ll INF = 1e18;

int main() {
    FAST_IO;
    int n, m;
    if (!(cin >> n >> m)) return 0;

    // dp1: Standard costs, dp2: Discounted costs (cost - 1)
    vector<vector<ll>> dp1(n, vector<ll>(n, INF));
    vector<vector<ll>> dp2(n, vector<ll>(n, INF));

    for (int i = 0; i < n; i++) {
        dp1[i][i] = 0;
        dp2[i][i] = 0;
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        // The problem uses 0-based indexing for cities 
        if (w < dp1[u][v]) {
            dp1[u][v] = w;
            dp2[u][v] = max(0LL, w - 1); // Edge weight reduced by 1 
        }
    }

    int v_center;
    cin >> v_center; // The discount city V [cite: 247]

    // Standard Floyd-Warshall for both matrices
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dp1[i][k] < INF && dp1[k][j] < INF)
                    dp1[i][j] = min(dp1[i][j], dp1[i][k] + dp1[k][j]);
                if (dp2[i][k] < INF && dp2[k][j] < INF)
                    dp2[i][j] = min(dp2[i][j], dp2[i][k] + dp2[k][j]);
            }
        }
    }

    int q;
    cin >> q;
    while (q--) {
        int a, b;
        cin >> a >> b;

        // Choice 1: Standard shortest path (ignoring V)
        ll original_path = dp1[a][b];

        // Choice 2: Path through V with discounts applied [cite: 243]
        ll discounted_path = INF;
        if (dp2[a][v_center] < INF && dp2[v_center][b] < INF) {
            discounted_path = dp2[a][v_center] + dp2[v_center][b];
        }

        ll ans = min(original_path, discounted_path);

        if (ans >= INF) cout << -1 << nl;
        else cout << ans << nl;
    }

    return 0;
}
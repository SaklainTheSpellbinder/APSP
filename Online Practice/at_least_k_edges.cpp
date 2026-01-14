#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define nl "\n"
#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(0);

const ll INF = 2e18; 

// Min-Plus Matrix Multiplication
vector<vector<ll>> multiply(const vector<vector<ll>>& A, const vector<vector<ll>>& B, int n) {
    vector<vector<ll>> C(n + 1, vector<ll>(n + 1, INF));
    for (int k_node = 1; k_node <= n; k_node++) {
        for (int i = 1; i <= n; i++) {
            if (A[i][k_node] == INF) continue; 
            for (int j = 1; j <= n; j++) {
                if (B[k_node][j] < INF) {
                    C[i][j] = min(C[i][j], A[i][k_node] + B[k_node][j]);
                }
            }
        }
    }
    return C;
}

// Binary Exponentiation for Exactly K edges
vector<vector<ll>> power(vector<vector<ll>> A, ll k, int n) {
    vector<vector<ll>> res(n + 1, vector<ll>(n + 1, INF));
    for (int i = 1; i <= n; i++) res[i][i] = 0; 
    
    while (k > 0) {
        if (k % 2 == 1) res = multiply(res, A, n);
        A = multiply(A, A, n);
        k /= 2;
    }
    return res;
}

int main() {
    FAST_IO;
    int n, m;
    ll k_min;
    cin >> n >> m >> k_min;

    // adj stores exactly 1 edge
    // standard_apsp will store any number of edges
    vector<vector<ll>> adj(n + 1, vector<ll>(n + 1, INF));
    vector<vector<ll>> standard_apsp(n + 1, vector<ll>(n + 1, INF));

    for (int i = 1; i <= n; i++) standard_apsp[i][i] = 0;

    for (int i = 0; i < m; i++) {
        int u, v; ll w;
        cin >> u >> v >> w;
        adj[u][v] = min(adj[u][v], w); 
        standard_apsp[u][v] = min(standard_apsp[u][v], w);
    }

    // 1. Calculate Standard APSP using standard Floyd-Warshall
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (standard_apsp[i][k] < INF && standard_apsp[k][j] < INF)
                    standard_apsp[i][j] = min(standard_apsp[i][j], standard_apsp[i][k] + standard_apsp[k][j]);
            }
        }
    }

    // 2. Calculate Exactly K edges matrix
    vector<vector<ll>> exactly_k = power(adj, k_min, n);

    // 3. Combine them: Exactly K + (0 or more)
    ll final_ans = INF;
    // For a path from node 1 to node n
    for (int p = 1; p <= n; p++) {
        if (exactly_k[1][p] < INF && standard_apsp[p][n] < INF) {
            final_ans = min(final_ans, exactly_k[1][p] + standard_apsp[p][n]);
        }
    }

    if (final_ans >= INF) cout << -1 << nl;
    else cout << final_ans << nl;

    return 0;
}
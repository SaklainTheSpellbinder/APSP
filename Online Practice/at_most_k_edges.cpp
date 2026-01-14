#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define nl "\n"
#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(0);

const ll INF = 2e18; 

// Min-Plus Matrix Multiplication
vector<vector<ll>> multiply(vector<vector<ll>>& A, vector<vector<ll>>& B, int n) {
    vector<vector<ll>> C(n + 1, vector<ll>(n + 1, INF));
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            if (A[i][k] == INF) continue; 
            for (int j = 1; j <= n; j++) {
                if (B[k][j] < INF) {
                    C[i][j] = min(C[i][j], A[i][k] + B[k][j]);
                }
            }
        }
    }
    return C;
}

// Binary Exponentiation
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
    ll k_limit;
    cin >> n >> m >> k_limit;

    vector<vector<ll>> adj(n + 1, vector<ll>(n + 1, INF));

    // KEY MODIFICATION for "At Most K": 
    // Add a 0-weight self-loop to every city so we can 'stay' there.
    for (int i = 1; i <= n; i++) {
        adj[i][i] = 0; 
    }

    for (int i = 0; i < m; i++) {
        int u, v; ll w;
        cin >> u >> v >> w;
        adj[u][v] = min(adj[u][v], w); 
    }

    vector<vector<ll>> result = power(adj, k_limit, n);

    if (result[1][n] >= INF) cout << -1 << nl;
    else cout << result[1][n] << nl;

    return 0;
}
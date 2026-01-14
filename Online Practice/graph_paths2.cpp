#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define nl "\n"
#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(0);

const ll INF = 2e18; // Use a value larger than 1e18 for safety

// Min-Plus Matrix Multiplication
vector<vector<ll>> multiply(vector<vector<ll>>& A, vector<vector<ll>>& B, int n) {
    vector<vector<ll>> C(n + 1, vector<ll>(n + 1, INF));
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            if (A[i][k] == INF) continue; // Optimization
            for (int j = 1; j <= n; j++) {
                if (B[k][j] < INF) {
                    C[i][j] = min(C[i][j], A[i][k] + B[k][j]);
                }
            }
        }
    }
    return C;
}

// Binary Exponentiation for Matrices
vector<vector<ll>> power(vector<vector<ll>> A, ll k, int n) {
    vector<vector<ll>> res(n + 1, vector<ll>(n + 1, INF));
    // Base Case for paths of length 0: Identity is 0 on diagonal, INF elsewhere
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
    ll k_edges;
    cin >> n >> m >> k_edges;

    // Initial DP matrix (Paths of exactly 1 edge)
    vector<vector<ll>> adj(n + 1, vector<ll>(n + 1, INF));

    for (int i = 0; i < m; i++) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        // Since we need exactly k edges, we keep the minimum single edge weight
        adj[a][b] = min(adj[a][b], c); 
    }

    // Compute Matrix^k
    vector<vector<ll>> result = power(adj, k_edges, n);

    if (result[1][n] >= INF) {
        cout << -1 << nl;
    } else {
        cout << result[1][n] << nl;
    }

    return 0;
}
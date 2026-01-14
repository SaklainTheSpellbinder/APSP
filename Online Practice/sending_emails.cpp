#include <bits/stdc++.h>
using namespace std;

#define nl "\n"
#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(0);

void solve(int caseNum) {
    int n, m, s, k;
    cin >> n >> m >> s >> k;

    // Initialize probability matrix with 0.0 (no path)
    // and 1.0 for the diagonal (probability of reaching itself is 100%)
    vector<vector<double>> prob(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; i++) prob[i][i] = 1.0;

    for (int i = 0; i < m; i++) {
        int u, v;
        double p;
        cin >> u >> v >> p;
        p /= 100.0; // Convert percentage to 0-1 range
        
        // Use the maximum probability for multiple edges
        if (p > prob[u][v]) {
            prob[u][v] = prob[v][u] = p;
        }
    }

    // Floyd-Warshall for Maximum Probability Path (Max-Product)
    for (int k_node = 0; k_node < n; k_node++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                // Update: Maximize the product of probabilities
                if (prob[i][k_node] * prob[k_node][j] > prob[i][j]) {
                    prob[i][j] = prob[i][k_node] * prob[k_node][j];
                }
            }
        }
    }

    // Expected number of transmissions calculation:
    // Expected transmissions = 1 / Probability
    // Total time = (Expected transmissions) * (Time per attempt * 2) * S
    // The *2 and S are constants provided in the problem statement.
    double max_prob = prob[0][n - 1];
    double result = (2.0 * s * k) / max_prob;

    cout << "Case " << caseNum << ": " << fixed << setprecision(4) << result << nl;
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
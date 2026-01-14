#include <bits/stdc++.h>
using namespace std;

#define nl "\n"
#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(0);

int main() {
    FAST_IO;
    int n; cin >> n;
    // dist matrix for -log values, next_node for path reconstruction
    vector<vector<double>> dp(n + 1, vector<double>(n + 1, 1e15));
    vector<vector<int>> next_node(n + 1, vector<int>(n + 1, -1));

    for (int i = 1; i <= n; i++) dp[i][i] = 0.0;

    unordered_map<string, int> name_to_id;
    vector<string> id_to_name(n + 1);
    for (int i = 1; i <= n; i++) {
        string s; cin >> s;
        name_to_id[s] = i;
        id_to_name[i] = s;
    }

    int m; cin >> m;
    for (int i = 0; i < m; i++) {
        string a, b; double c;
        cin >> a >> c >> b;
        double weight = -log(c);
        if (weight < dp[name_to_id[a]][name_to_id[b]]) {
            dp[name_to_id[a]][name_to_id[b]] = weight;
            next_node[name_to_id[a]][name_to_id[b]] = name_to_id[b];
        }
    }

    // Floyd-Warshall with successor updates
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dp[i][k] < 1e14 && dp[k][j] < 1e14) {
                    if (dp[i][j] > dp[i][k] + dp[k][j]) {
                        dp[i][j] = dp[i][k] + dp[k][j];
                        next_node[i][j] = next_node[i][k];
                    }
                }
            }
        }
    }

    // Identify and print the cycle
    for (int i = 1; i <= n; i++) {
        if (dp[i][i] < -1e-9) { // Negative cycle found 
            cout << "Yes" << nl;
            int curr = i;
            vector<string> cycle;
            do {
                cycle.push_back(id_to_name[curr]);
                curr = next_node[curr][i];
            } while (curr != i);
            cycle.push_back(id_to_name[i]);

            for (int k = 0; k < cycle.size(); k++) {
                cout << cycle[k] << (k == cycle.size() - 1 ? "" : " -> ");
            }
            cout << nl;
            return 0;
        }
    }
    cout << "No" << nl;
    return 0;
}
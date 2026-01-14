#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    // Adjacency matrix for the graph
    vector<vector<ll>> dist(n + 1, vector<ll>(n + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> dist[i][j];
        }
    }

    // Order of deletion
    vector<int> deletion_order(n);
    for (int i = 0; i < n; i++) cin >> deletion_order[i];

    // Reverse the order to "add" nodes
    reverse(deletion_order.begin(), deletion_order.end());

    vector<ll> answers;
    vector<bool> activated(n + 1, false);

    // Process nodes in reverse deletion order (Adding nodes)
    for (int k_idx = 0; k_idx < n; k_idx++) {
        int k = deletion_order[k_idx];
        activated[k] = true;

        // Run the k-loop for the newly added node
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }

        // Sum shortest paths between all currently "activated" nodes
        ll current_sum = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (activated[i] && activated[j]) {
                    current_sum += dist[i][j];
                }
            }
        }
        answers.push_back(current_sum);
    }

    // Reverse the answers back to match deletion order
    reverse(answers.begin(), answers.end());

    for (int i = 0; i < n; i++) {
        cout << answers[i] << (i == n - 1 ? "" : " ");
    }
    cout << endl;

    return 0;
}
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int get_dist(const string& a, const string& b, int m) {
    int max_diff = 0;
    for (int i = 0; i < m; ++i) {
        max_diff = max(max_diff, abs(a[i] - b[i]));
    }
    return max_diff;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<string> grid(n);
    for (int i = 0; i < n; ++i) cin >> grid[i];

    vector<int> min_dist(n, 1e9);
    vector<bool> visited(n, false);
    min_dist[0] = 0;
    int max_bottleneck = 0;

    for (int i = 0; i < n; ++i) {
        int u = -1;
        // Find unvisited node with smallest distance
        for (int v = 0; v < n; ++v) {
            if (!visited[v] && (u == -1 || min_dist[v] < min_dist[u])) {
                u = v;
            }
        }

        visited[u] = true;
        max_bottleneck = max(max_bottleneck, min_dist[u]);

        // Update neighbors
        for (int v = 0; v < n; ++v) {
            if (!visited[v]) {
                int d = get_dist(grid[u], grid[v], m);
                if (d < min_dist[v]) {
                    min_dist[v] = d;
                }
            }
        }
    }

    cout << max_bottleneck << endl;
    return 0;
}
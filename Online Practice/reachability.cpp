#include <bits/stdc++.h>
using namespace std;

#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(0);

const int MAXN = 50001;
bitset<MAXN> reach[MAXN];
vector<int> adj[MAXN];
int indegree[MAXN];

int main() {
    FAST_IO;
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        indegree[v]++;
    }

    // Reachable Nodes in a DAG using Bitsets
    // We process nodes in reverse topological order (bottom-up)
    vector<int> topo;
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) q.push(i);
        reach[i].set(i); // A node can always reach itself
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topo.push_back(u);
        for (int v : adj[u]) {
            if (--indegree[v] == 0) q.push(v);
        }
    }

    // Process in reverse topological order
    for (int i = n - 1; i >= 0; i--) {
        int u = topo[i];
        for (int v : adj[u]) {
            reach[u] |= reach[v]; // Bitset OR: Node u can reach anything node v can reach
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << reach[i].count() << (i == n ? "" : " ");
    }
    cout << "\n";

    return 0;
}
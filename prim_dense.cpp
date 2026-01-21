int primDense(int n, vector<vector<int>>& adjMatrix) {
    vector<int> min_weight(n, INF);
    vector<bool> visited(n, false);
    min_weight[0] = 0;
    int total_mst_weight = 0;

    for (int i = 0; i < n; i++) {
        int u = -1;
        // Step 1: Find the unvisited vertex with the minimum weight (Array Scan)
        for (int v = 0; v < n; v++) {
            if (!visited[v] && (u == -1 || min_weight[v] < min_weight[u])) {
                u = v;
            }
        }

        if (min_weight[u] == INF) return -1; // Graph is disconnected

        visited[u] = true;
        total_mst_weight += min_weight[u];

        // Step 2: Update weights of neighbors
        for (int v = 0; v < n; v++) {
            if (adjMatrix[u][v] != 0 && !visited[v]) {
                if (adjMatrix[u][v] < min_weight[v]) {
                    min_weight[v] = adjMatrix[u][v];
                }
            }
        }
    }
    return total_mst_weight;
}
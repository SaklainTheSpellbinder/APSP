if (dist[i][j] > dist[i][k] + dist[k][j]) {
    dist[i][j] = dist[i][k] + dist[k][j];
    next[i][j] = next[i][k]; // The path to j starts with the path to k
}

vector<int> constructPath(int u, int v) {
    if (next[u][v] == -1) return {}; // No path exists
    vector<int> path = {u};
    while (u != v) {
        u = next[u][v];
        path.push_back(u);
    }
    return path;
}

int countNodes(int u, int v) {
    if (dist[u][v] == INF) return 0; // No path exists [cite: 147]
    int count = 1; // Start with the source node
    while (u != v) {
        u = next_node[u][v];
        count++;
    }
    return count;
}

// In your main function:
int nodes = countNodes(start, end);
int edges = nodes - 1;
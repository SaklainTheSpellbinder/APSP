int cycle_node = -1;
for (int i = 0; i < n; i++) {
    if (dist[i][i] < 0) {
        cycle_node = i;
        break;
    }
}

for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][k] < INF && dist[k][j] < INF) {
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }
}


if (cycle_node != -1) {
    cout << "Negative cycle found: ";
    int curr = cycle_node;
    vector<int> path;
    
    // Trace the path from cycle_node back to itself
    do {
        path.push_back(curr);
        curr = next[curr][cycle_node];
    } while (curr != cycle_node);
    
    path.push_back(cycle_node); // Complete the loop
    for (int i = 0; i < path.size(); i++) {
        cout << path[i] << (i == path.size() - 1 ? "" : " -> ");
    }
    cout << endl;
}
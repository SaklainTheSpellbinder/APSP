#include <bits/stdc++.h>
using namespace std;

#define nl "\n"
#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(0);

int dx[] = {1, 1, 2, 2, -1, -1, -2, -2};
int dy[] = {2, -2, 1, -1, 2, -2, 1, -1};

int dists[10][10][10][10]; // dists[src_r][src_c][dst_r][dst_c]
int R, C;

void bfs(int r, int c) {
    for(int i=0; i<R; i++) for(int j=0; j<C; j++) dists[r][c][i][j] = -1;
    queue<pair<int,int>> q;
    q.push({r, c});
    dists[r][c][r][c] = 0;

    while(!q.empty()){
        pair<int,int> curr = q.front(); q.pop();
        for(int i=0; i<8; i++){
            int nx = curr.first + dx[i], ny = curr.second + dy[i];
            if(nx >= 0 && nx < R && ny >= 0 && ny < C && dists[r][c][nx][ny] == -1){
                dists[r][c][nx][ny] = dists[r][c][curr.first][curr.second] + 1;
                q.push({nx, ny});
            }
        }
    }
}

void solve(int caseNum) {
    cin >> R >> C;
    vector<string> board(R);
    vector<pair<pair<int,int>, int>> riders;
    for(int i=0; i<R; i++) {
        cin >> board[i];
        for(int j=0; j<C; j++) {
            if(board[i][j] != '.') {
                riders.push_back({{i, j}, board[i][j] - '0'});
            }
        }
    }

    // Precalculate all-pairs knight distances on the grid
    for(int i=0; i<R; i++) for(int j=0; j<C; j++) bfs(i, j);

    int min_total_steps = 1e9;
    bool possible = false;

    for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
            int current_cell_steps = 0;
            bool can_all_reach = true;

            for(auto &rider : riders){
                int d = dists[rider.first.first][rider.first.second][i][j];
                if(d == -1) { can_all_reach = false; break; }
                // Calculate steps: ceil(dist / K)
                current_cell_steps += (d + rider.second - 1) / rider.second;
            }

            if(can_all_reach){
                possible = true;
                min_total_steps = min(min_total_steps, current_cell_steps);
            }
        }
    }

    cout << "Case " << caseNum << ": " << (possible ? min_total_steps : -1) << nl;
}

int main() {
    FAST_IO;
    int t; cin >> t;
    for(int i=1; i <= t; i++) solve(i);
    return 0;
}
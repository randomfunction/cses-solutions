#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
 
        int n, m;
    cin >> n >> m;
 
    vector<vector<char>> grid(n, vector<char>(m));
    pair<int, int> start, end;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> grid[i][j];
            if (grid[i][j] == 'A') start = {i, j};
            if (grid[i][j] == 'B') end = {i, j};
        }
    }
 
    vector<vector<int>> dist(n, vector<int>(m, -1));
    vector<vector<pair<int, int>>> parent(n, vector<pair<int, int>>(m, {-1, -1}));
    queue<pair<int, int>> q;
    q.push(start);
    dist[start.first][start.second] = 0;
    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};
    char moves[] = {'D', 'U', 'R', 'L'};
 
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
 
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
 
            if (nx >= 0 && ny >= 0 && nx < n && ny < m && grid[nx][ny] != '#' && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[x][y] + 1;
                parent[nx][ny] = {x, y};
                q.push({nx, ny});
 
                if (nx == end.first && ny == end.second) break;
            }
        }
    }
    if (dist[end.first][end.second] == -1) {
        cout << "NO" << endl;
        return 0;
    }
    cout << "YES" << endl;
    cout << dist[end.first][end.second] << endl;
 
    string path;
    pair<int, int> cur = end;
    while (cur != start) {
        auto [px, py] = parent[cur.first][cur.second];
        for (int i = 0; i < 4; ++i) {
            if (px + dx[i] == cur.first && py + dy[i] == cur.second) {
                path += moves[i];
                break;
            }
        }
        cur = parent[cur.first][cur.second];
    }
 
    reverse(path.begin(), path.end());
    cout << path << endl;
    return 0;
}
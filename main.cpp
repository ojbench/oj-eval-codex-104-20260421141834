#include <bits/stdc++.h>
using namespace std;

// Grid shortest path via required shop(s):
// Compute BFS distance from start (2) and from home (3) to every cell.
// Answer = min over all shop cells (4) of dist_start[shop] + dist_home[shop].
// Cells with value 1 are blocked. Movement is 4-directional.

static const int INF = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m; // n: columns, m: rows
    if (!(cin >> n >> m)) return 0;
    vector<int> grid; grid.reserve((size_t)n * m);
    pair<int,int> start{-1,-1}, home{-1,-1};
    vector<pair<int,int>> shops;

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            int x; cin >> x;
            grid.push_back(x);
            if (x == 2) start = {i, j};
            else if (x == 3) home = {i, j};
            else if (x == 4) shops.emplace_back(i, j);
        }
    }

    auto idx = [n](int r, int c){ return r * n + c; };

    auto bfs_from = [&](pair<int,int> src){
        vector<int> dist((size_t)n * m, INF);
        if (src.first < 0) return dist; // will remain INF
        deque<pair<int,int>> dq;
        dist[idx(src.first, src.second)] = 0;
        dq.push_back(src);
        static const int dr[4] = {-1, 1, 0, 0};
        static const int dc[4] = {0, 0, -1, 1};
        while (!dq.empty()) {
            auto [r, c] = dq.front(); dq.pop_front();
            int base = dist[idx(r,c)];
            for (int k = 0; k < 4; ++k) {
                int nr = r + dr[k];
                int nc = c + dc[k];
                if (nr < 0 || nr >= m || nc < 0 || nc >= n) continue;
                int cell = grid[idx(nr, nc)];
                if (cell == 1) continue; // blocked
                int &d = dist[idx(nr, nc)];
                if (d > base + 1) {
                    d = base + 1;
                    dq.emplace_back(nr, nc);
                }
            }
        }
        return dist;
    };

    auto ds = bfs_from(start);
    auto dh = bfs_from(home);

    long long ans = (long long)INF;
    for (auto [r, c] : shops) {
        int a = ds[idx(r,c)];
        int b = dh[idx(r,c)];
        if (a >= INF || b >= INF) continue;
        ans = min(ans, (long long)a + b);
    }

    if (ans >= INF) {
        // If unreachable, print -1 (problem statement doesn't specify; this is conventional)
        cout << -1 << '\n';
    } else {
        cout << ans << '\n';
    }

    return 0;
}

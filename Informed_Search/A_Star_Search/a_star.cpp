#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
vector<pair<int, int>> a[N]; 
int H[N], n, m;

vector<int> a_star(int s, int t) {
    vector<long long> G(n + 1, LLONG_MAX);
    vector<int> pre(n + 1, -1);
    vector<bool> vis(n + 1, 0);
    priority_queue<pair<long long, int>> q;

    G[s] = 0;
    q.push({-(G[s] + H[s]), s});

    while (!q.empty()) {
        auto [c, u] = q.top();
        q.pop();
        if (u == t) break;
        if (vis[u]) continue;
        vis[u] = true;

        for (auto [v, cost] : a[u]) {
            if (G[v] > G[u] + cost) {
                G[v] = G[u] + cost;
                pre[v] = u;
                q.push({-(G[v] + H[v]), v});
            }
        }
    }

    if (G[t] == LLONG_MAX) return {};
    vector<int> path;
    for (int u = t; u != -1; u = pre[u]) path.push_back(u);
    reverse(path.begin(), path.end());
    return path;
}

int32_t main() {
    cout << "Enter number of nodes:\n";
    cin >> n;
    cout << "Enter number of edges:\n";
    cin >> m;

    cout << "Enter edges (format: A B cost):\n";
    for (int i = 0; i < m; i++) {
        char x, y; int c;
        cin >> x >> y >> c;
        int u = x - 'A', v = y - 'A';
        a[u].push_back({v, c});
    }

    cout << "Enter heuristic values (A 5 ... then #):\n";
    while (1) {
        char x; cin >> x;
        if (x == '#') break;
        int h; cin >> h;
        H[x - 'A'] = h;
    }

    char sc, tc;
    cout << "Enter start node:\n";
    cin >> sc;
    cout << "Enter end node:\n";
    cin >> tc;
    int s = sc - 'A', t = tc - 'A';

    vector<int> res = a_star(s, t);
    if (res.empty())
        cout << "No path found from " << sc << " to " << tc << '\n';
    else {
        cout << "Path: ";
        for (int u : res) cout << char(u + 'A') << " ";
        cout << "\n";
    }

    return 0;
}

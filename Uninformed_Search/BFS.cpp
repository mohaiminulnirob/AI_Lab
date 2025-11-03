#include <bits/stdc++.h>
using namespace std;

const int N = 1e3 + 5;
vector<int> a[N];
int edges, orig[N], level[N];
bool vis[N];
map<string, int> id;
map<int, string> rid;
vector<int> traversal;
vector<int> levelSeq[N];
int idCounter = 0;

void bfs(int start, int target) {
    queue<int> q;
    q.push(start);
    vis[start] = true;
    orig[start] = -1;
    level[start] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        traversal.push_back(u);

        if (u == target)
            return;

        for (auto v : a[u]) {
            if (!vis[v]) {
                vis[v] = true;
                orig[v] = u;
                level[v] = level[u] + 1;
                q.push(v);
            }
        }
    }
}

int32_t main() {
    cout << "Enter number of edges:\n";
    cin >> edges;
    string init, target;
    cout << "Enter initial and target node:\n";
    cin >> init >> target;
    cout << "Enter edges (u v):\n";

    for (int i = 0; i < edges; i++) {
        string x, y;
        cin >> x >> y;

        // Map new string nodes to integers
        if (!id.count(x)) {
            id[x] = idCounter;
            rid[idCounter] = x;
            idCounter++;
        }
        if (!id.count(y)) {
            id[y] = idCounter;
            rid[idCounter] = y;
            idCounter++;
        }

        int u = id[x];
        int v = id[y];
        a[u].push_back(v);
    }

    int start = id[init];
    int dest = id[target];

    bfs(start, dest);

    cout << "Traversing Sequence: ";
    int maxlevel = 0;
    for (int u : traversal) {
        cout << rid[u] << " ";
        levelSeq[level[u]].push_back(u);
        maxlevel = max(maxlevel, level[u]);
    }
    cout << '\n';

    for (int i = 0; i <= maxlevel; i++) {
        cout << "level " << i << ": ";
        for (auto u : levelSeq[i]) {
            cout << rid[u] << " ";
        }
        cout << '\n';
    }
    cout << '\n';

    if (!vis[dest]) {
        cout << "No path from " << init << " to " << target << '\n';
        return 0;
    }

    vector<int> path;
    for (int v = dest; v != -1; v = orig[v])
        path.push_back(v);
    reverse(path.begin(), path.end());

    cout << "Path: ";
    for (int u : path)
        cout << rid[u] << "(" << level[u] << ") ";
    cout << '\n';
}

#include <bits/stdc++.h>
using namespace std;

const int N = 1e3 + 5;
vector<int> a[N];
int edges, orig[N], maxDepth;
bool vis[N];
map<string, int> id;
map<int, string> rid;
int idCounter = 0;
vector<int> traversal;
bool found = false;

// Depth-Limited Search (used by IDS)
bool dls(int u, int target, int depth, int limit) {
    vis[u] = true;
    traversal.push_back(u);

    if (u == target) {
        found = true;
        return true;
    }

    if (depth >= limit) return false;

    for (auto v : a[u]) {
        if (!vis[v]) {
            orig[v] = u;
            if (dls(v, target, depth + 1, limit)) return true;
        }
    }

    return false;
}

int32_t main() {
    cout << "Enter number of edges:\n";
    cin >> edges;
    string init, target;
    cout << "Enter initial and target node:\n";
    cin >> init >> target;
    cout << "Enter maximum depth:\n";
    cin >> maxDepth;
    cout << "Enter edges (u v):\n";

    for (int i = 0; i < edges; i++) {
        string x, y;
        cin >> x >> y;

        // Map new string nodes to integers
        if (!id.count(x)) { id[x] = idCounter; rid[idCounter] = x; idCounter++; }
        if (!id.count(y)) { id[y] = idCounter; rid[idCounter] = y; idCounter++; }

        int u = id[x];
        int v = id[y];
        a[u].push_back(v);
        // If graph is undirected, uncomment the next line:
        // a[v].push_back(u);
    }

    int start = id[init];
    int dest = id[target];

    for (int limit = 1; limit <= maxDepth; limit++) {
        fill(vis, vis + N, false);
        traversal.clear();
        orig[start] = -1;
        found = false;

        if (dls(start, dest, 0, limit)) {
            cout << "Traversing Sequence (Depth Limit " << limit << "): ";
            for (int u : traversal)
                cout << rid[u] << " ";
            cout << '\n';

            vector<int> path;
            for (int v = dest; v != -1; v = orig[v])
                path.push_back(v);
            reverse(path.begin(), path.end());

            cout << "Path: ";
            for (int u : path)
                cout << rid[u] << " ";
            cout << '\n';
            return 0;
        } else {
            cout << "Failure (Depth Limit " << limit << ")\n";
        }
    }

    cout << "No path from " << init << " to " << target << " found within depth " << maxDepth << "\n";
    return 0;
}

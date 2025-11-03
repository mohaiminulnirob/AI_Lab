#include <bits/stdc++.h>
using namespace std;

const int N = 1e3 + 5;
vector<int> a[N];
int edges, limit, orig[N];
bool vis[N], found = false;
map<string, int> id;
map<int, string> rid;
vector<int> traversal;
int idCounter = 0;

void dls(int u, int target, int depth) {
    if (depth > limit || found) return;

    vis[u] = true;
    traversal.push_back(u);

    if (u == target) {
        found = true;
        return;
    }

    for (auto v : a[u]) {
        if (!vis[v]) {
            orig[v] = u;
            dls(v, target, depth + 1);
        }
    }
}

int32_t main() {
    cout << "Enter number of edges:\n";
    cin >> edges;
    string init, target;
    cout << "Enter initial and target node:\n";
    cin >> init >> target;
    cout << "Enter depth limit:\n";
    cin >> limit;
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
        // If graph is undirected, uncomment the next line
        // a[v].push_back(u);
    }

    int start = id[init];
    int dest = id[target];
    orig[start] = -1;

    dls(start, dest, 0);

    cout << "Traversing Sequence: ";
    for (int u : traversal)
        cout << rid[u] << " ";
    cout << '\n';

    if (!found) {
        cout << "Failure! No path from " << init << " to " << target 
             << " within depth limit " << limit << '\n';
        return 0;
    }

    vector<int> path;
    for (int v = dest; v != -1; v = orig[v])
        path.push_back(v);
    reverse(path.begin(), path.end());

    cout << "Path: ";
    for (int u : path)
        cout << rid[u] << " ";
    cout << '\n';

    return 0;
}

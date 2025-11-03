#include <bits/stdc++.h>
using namespace std;

const int N = 1000;
vector<pair<int, int>> adj[N]; 
int H[N];                      
int n, m, ans;

vector<int> a_star(int s, int t) {
    vector<long long> G(n, LLONG_MAX);
    vector<int> pre(n, -1);
    vector<bool> vis(n, false);

    priority_queue<pair<long long, int>> pq; 
    G[s] = 0;
    pq.push({-(G[s] + H[s]), s});

    while (!pq.empty()) {
        auto [f, u] = pq.top();
        pq.pop();

        if (vis[u]) continue;
        vis[u] = true;
        if (u == t){
            ans=G[u];
            break;

        } 

        for (auto [v, w] : adj[u]) {
            if (G[v] > G[u] + w) {
                G[v] = G[u] + w;
                pre[v] = u;
                pq.push({-(G[v] + H[v]), v});
            }
        }
    }

    if (G[t] == LLONG_MAX) return {};

    vector<int> path;
    for (int u = t; u != -1; u = pre[u])
        path.push_back(u);
    reverse(path.begin(), path.end());
    return path;
}

int32_t main() {
    cout << "Enter number of nodes:\n";
    cin >> n;

    cout << "Enter number of edges:\n";
    cin >> m;

    map<string, int> id;
    map<int, string> rid;
    int idCounter = 0;

    cout << "Enter edges (format: A B cost):\n";
    for (int i = 0; i < m; i++) {
        string s1, s2;
        int cost;
        cin >> s1 >> s2 >> cost;

        if (!id.count(s1)) { id[s1] = idCounter++; rid[id[s1]] = s1; }
        if (!id.count(s2)) { id[s2] = idCounter++; rid[id[s2]] = s2; }


        int u = id[s1], v = id[s2];
        adj[u].push_back({v, cost});
        adj[v].push_back({u, cost}); 
    }

    cout << "Enter heuristic values (format: A 5 ... then #):\n";
    while (true) {
        string s;
        cin >> s;
        if (s == "#") break;
        int h;
        cin >> h;
        if (!id.count(s)) {
            id[s] = idCounter++;
            rid[id[s]] = s;
        }
        H[id[s]] = h;
    }

    string sc, tc;
    cout << "Enter start node:\n";
    cin >> sc;
    cout << "Enter end node:\n";
    cin >> tc;

    int s = id[sc];
    int t = id[tc];

    vector<int> res = a_star(s, t);
    if (res.empty())
        cout << "No path found from " << sc << " to " << tc << "\n";
    else {
        cout << "Path: ";
        for (int u : res)
            cout << rid[u] << " ";
        cout << "\n";
    }

    return 0;
}

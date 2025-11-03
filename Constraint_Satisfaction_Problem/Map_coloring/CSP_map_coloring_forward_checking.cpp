#include<bits/stdc++.h>
using namespace std;

const int N=100;
int assign[N];
int var, cons, domain;
vector<int> adj[N];
vector<set<int>> domains; // domain[i] = remaining possible colors for variable i

bool is_valid(int region, int color) {
    for (auto u : adj[region]) {
        if (assign[u] == color)
            return false;
    }
    return true;
}

// Forward checking version of solve
bool solve(int u) {
    if (u == var) return true;

    // Try each color still available for this variable
    for (int color : domains[u]) {
        if (is_valid(u, color)) {
            assign[u] = color;

            // Save current domain state for restoration later
            vector<set<int>> old_domains = domains;

            // Forward checking: remove this color from neighbors' domains
            for (auto v : adj[u]) {
                if (assign[v] == -1)
                    domains[v].erase(color);
            }

            // Check if any unassigned variable has no remaining color → fail early
            bool valid = true;
            for (int i = 0; i < var; i++) {
                if (assign[i] == -1 && domains[i].empty()) {
                    valid = false;
                    break;
                }
            }

            if (valid && solve(u + 1))
                return true;

            // Restore previous domain state on backtrack
            domains = old_domains;
            assign[u] = -1;
        }
    }
    return false;
}

int32_t main() {
    int t = 1;
    // cin >> t;
    while (t--) {
        cout << "Enter number of regions: \n";
        cin >> var;

        map<string, int> varMap;
        map<int, string> rVarMap;

        cout << "Enter regions: \n";
        for (int i = 0; i < var; i++) {
            string s;
            cin >> s;
            varMap[s] = i;
            rVarMap[i] = s;
        }

        cout << "Enter number of constraints: \n";
        cin >> cons;
        for (int i = 0; i < cons; i++) {
            string x, y;
            cin >> x >> y;
            int a = varMap[x];
            int b = varMap[y];
            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        cout << "Enter domain number: \n";
        cin >> domain;
        map<int, string> domainMap;
        cout << "Enter domains: \n";
        for (int i = 0; i < domain; i++) {
            string s;
            cin >> s;
            domainMap[i] = s;
        }

        fill(assign, assign + var, -1);

        // Initialize all variable domains with all possible colors
        domains.assign(var, {});
        for (int i = 0; i < var; i++) {
            for (int j = 0; j < domain; j++)
                domains[i].insert(j);
        }

        if (solve(0)) {
            cout << "\nColor Assignment:\n";
            for (int i = 0; i < var; i++) {
                cout << rVarMap[i] << " -> " << domainMap[assign[i]] << '\n';
            }
        } else {
            cout << "No solution exist\n";
        }

        for (int i = 0; i < var; i++) adj[i].clear();
    }
}

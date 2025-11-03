#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back

int n;

// ✅ Heuristic: number of attacking queen pairs
int heuristic(const vector<int> &state) {
    int h = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (state[i] == state[j]) h++; // same row
            if (abs(state[i] - state[j]) == abs(i - j)) h++; // diagonal
        }
    }
    return h;
}

// ✅ Generate successors (move one queen to another row in same column)
vector<vector<int>> getSuccessors(const vector<int> &cur) {
    vector<vector<int>> suc;
    for (int col = 0; col < n; col++) {
        for (int row = 0; row < n; row++) {
            if (row != cur[col]) {
                vector<int> nxt = cur;
                nxt[col] = row;
                suc.pb(nxt);
            }
        }
    }
    return suc;
}

// ✅ A* search for N-Queens
vector<int> a_star_nqueen(vector<int> start) {
    struct Node {
        vector<int> state;
        int g, h;
        int f() const { return g + h; }
        bool operator>(const Node &other) const {
            return f() > other.f();
        }
    };

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    set<vector<int>> visited;

    pq.push({start, 0, heuristic(start)});
    visited.insert(start);

    while (!pq.empty()) {
        Node cur = pq.top();
        pq.pop();

        if (cur.h == 0) return cur.state; // ✅ Found goal (no attacks)

        auto successors = getSuccessors(cur.state);
        for (auto &s : successors) {
            if (!visited.count(s)) {
                visited.insert(s);
                int h = heuristic(s);
                pq.push({s, cur.g + 1, h});
            }
        }
    }
    return {}; // No solution found (shouldn't happen for N-Queens)
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cout << "Enter number of queens:\n";
    cin >> n;

    cout << "Enter initial state (n numbers = row positions of queens in each column):\n";
    vector<int> start(n);
    for (int i = 0; i < n; i++) cin >> start[i];

    vector<int> res = a_star_nqueen(start);

    if (res.empty()) {
        cout << "No solution found.\n";
    } else {
        cout << "\nSolution (row positions for each column):\n";
        for (int x : res) cout << x << " ";
        cout << "\n\nBoard:\n";
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                cout << (res[c] == r ? "Q " : ". ");
            }
            cout << "\n";
        }
    }

    return 0;
}

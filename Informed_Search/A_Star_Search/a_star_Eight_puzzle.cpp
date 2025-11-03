#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back

// ✅ Goal state
const string goal = "123456780";

// ✅ Heuristic: number of misplaced tiles
int heuristic(const string &state) {
    int h = 0;
    for (int i = 0; i < 9; i++) {
        if (state[i] != '0' && state[i] != goal[i])
            h++;
    }
    return h;
}

// ✅ Generate neighbors by moving the blank (0)
vector<string> getSuccessors(const string &cur) {
    vector<string> nxt;
    int pos = cur.find('0');
    int x = pos / 3, y = pos % 3;
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    for (int k = 0; k < 4; k++) {
        int nx = x + dx[k], ny = y + dy[k];
        if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3) {
            string temp = cur;
            swap(temp[pos], temp[nx * 3 + ny]);
            nxt.push_back(temp);
        }
    }
    return nxt;
}

// ✅ A* Search for 8-Puzzle
vector<string> a_star_puzzle(const string &start) {
    struct Node {
        string state;
        int g, h;
        int f() const { return g + h; }
        bool operator>(const Node &other) const {
            return f() > other.f();
        }
    };

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    unordered_map<string, int> gScore;
    unordered_map<string, string> parent;

    pq.push({start, 0, heuristic(start)});
    gScore[start] = 0;

    while (!pq.empty()) {
        Node cur = pq.top();
        pq.pop();

        if (cur.state == goal) {
            // reconstruct path
            vector<string> path;
            string s = cur.state;
            while (s != "") {
                path.push_back(s);
                s = parent[s];
            }
            reverse(path.begin(), path.end());
            return path;
        }

        for (auto &nxt : getSuccessors(cur.state)) {
            int tentative_g = cur.g + 1;
            if (!gScore.count(nxt) || tentative_g < gScore[nxt]) {
                gScore[nxt] = tentative_g;
                parent[nxt] = cur.state;
                pq.push({nxt, tentative_g, heuristic(nxt)});
            }
        }
    }

    return {}; // no solution
}

// ✅ Utility: print puzzle state
void printState(const string &s) {
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0) cout << "\n";
        cout << (s[i] == '0' ? "_ " : string(1, s[i]) + " ");
    }
    cout << "\n";
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cout << "Enter the initial 8-puzzle state (use 0 for blank):\n";
    string start = "";
    for (int i = 0; i < 9; i++) {
        char c;
        cin >> c;
        start += c;
    }

    vector<string> path = a_star_puzzle(start);

    if (path.empty()) {
        cout << "No solution found!\n";
    } else {
        cout << "\nSolution found in " << path.size() - 1 << " moves.\n";
        for (int step = 0; step < path.size(); step++) {
            cout << "\nStep " << step << ":";
            printState(path[step]);
        }
    }

    return 0;
}

#include<bits/stdc++.h>
using namespace std;

const int N = 100;
int n;
int board[N][N];
vector<set<int>> domains; // possible rows for each column

// Check if a queen can be placed at (row, col) given the current board
bool is_safe(int row, int col) {
    // Check this row on left side
    for (int j = 0; j < col; j++)
        if (board[row][j])
            return false;

    // Check upper left diagonal
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    // Check lower left diagonal
    for (int i = row + 1, j = col - 1; i < n && j >= 0; i++, j--)
        if (board[i][j])
            return false;

    return true;
}


// Column-wise solve with forward checking
bool solve(int col) {
    if (col == n) return true;

    // Make a copy of current domain state for backtracking
    vector<set<int>> old_domains = domains;

    for (int row : domains[col]) {
        if (is_safe(row, col)) {
            board[row][col] = 1;

            // Forward checking: remove attacked rows from future columns
            for (int next_col = col + 1; next_col < n; next_col++) {
                // Remove same row
                domains[next_col].erase(row);

                // Remove diagonals
                int d = next_col - col;
                if (row - d >= 0) domains[next_col].erase(row - d);
                if (row + d < n) domains[next_col].erase(row + d);
            }

            // If any future column has no rows left → prune
            bool valid = true;
            for (int next_col = col + 1; next_col < n; next_col++) {
                if (domains[next_col].empty()) {
                    valid = false;
                    break;
                }
            }

            if (valid && solve(col + 1)) return true;

            // Backtrack
            board[row][col] = 0;
            domains = old_domains;
        }
    }
    return false;
}

int32_t main() {
    cout << "Enter number of queens:\n";
    cin >> n;

    memset(board, 0, sizeof(board));

    // Initialize domains: every column can initially take any row
    domains.assign(n, set<int>());
    for (int col = 0; col < n; col++)
        for (int row = 0; row < n; row++)
            domains[col].insert(row);

    if (solve(0)) {
        cout << "\nSolution (1 = Queen, 0 = Empty):\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                cout << board[i][j] << " ";
            cout << '\n';
        }
    } else {
        cout << "No solution exists.\n";
    }
}

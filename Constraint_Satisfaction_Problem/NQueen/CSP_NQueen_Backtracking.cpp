#include<bits/stdc++.h>
using namespace std;

const int N = 100;
int n;
int board[N][N];

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

bool solve(int col) {
    if (col == n)
        return true;

    for (int row = 0; row < n; row++) {
        if (is_safe(row, col)) {
            board[row][col] = 1;

            if (solve(col + 1))
                return true;

            // Backtrack
            board[row][col] = 0;
        }
    }
    return false;
}

int32_t main() {
    cout << "Enter number of queens:\n";
    cin >> n;

    memset(board, 0, sizeof(board));

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

    return 0;
}

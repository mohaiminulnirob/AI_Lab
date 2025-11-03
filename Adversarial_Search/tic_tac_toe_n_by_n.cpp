#include <bits/stdc++.h>
using namespace std;

const char PLAYER = 'X', AI = 'O', EMPTY = ' ';

// ============================
// Utility functions
// ============================

void printBoard(const vector<char>& board, int N) {
    cout << "\n";
    for (int i = 0; i < N * N; i++) {
        cout << (board[i] == EMPTY ? ' ' : board[i]);
        if (i % N != N - 1)
            cout << " | ";
        else if (i != N * N - 1)
            cout << "\n" << string(N * 4 - 3, '-') << "\n";
    }
    cout << "\n\n";
}

bool isMovesLeft(const vector<char>& board) {
    return any_of(board.begin(), board.end(), [](char c) { return c == EMPTY; });
}

// Generate all possible winning line combinations for N×N
vector<vector<int>> generateWins(int N) {
    vector<vector<int>> wins;

    // Rows
    for (int i = 0; i < N; i++) {
        vector<int> row;
        for (int j = 0; j < N; j++)
            row.push_back(i * N + j);
        wins.push_back(row);
    }

    // Columns
    for (int j = 0; j < N; j++) {
        vector<int> col;
        for (int i = 0; i < N; i++)
            col.push_back(i * N + j);
        wins.push_back(col);
    }

    // Main diagonal
    vector<int> diag1;
    for (int i = 0; i < N; i++)
        diag1.push_back(i * N + i);
    wins.push_back(diag1);

    // Anti-diagonal
    vector<int> diag2;
    for (int i = 0; i < N; i++)
        diag2.push_back(i * N + (N - 1 - i));
    wins.push_back(diag2);

    return wins;
}

int evaluate(const vector<char>& board, const vector<vector<int>>& wins) {
    for (auto& line : wins) {
        char first = board[line[0]];
        if (first == EMPTY) continue;
        bool same = true;
        for (int idx : line)
            if (board[idx] != first) { same = false; break; }
        if (same) return (first == AI) ? +10 : -10;
    }
    return 0;
}

// ============================
// Minimax with Alpha-Beta pruning
// ============================

int minimax(vector<char>& board, int depth, bool isMax, int alpha, int beta,
            int N, const vector<vector<int>>& wins)
{
    int score = evaluate(board, wins);
    if (score == 10) return score - depth;
    if (score == -10) return score + depth;
    if (!isMovesLeft(board)) return 0;

    if (isMax) {
        int best = -1e9;
        for (int i = 0; i < N * N; i++) {
            if (board[i] == EMPTY) {
                board[i] = AI;
                best = max(best, minimax(board, depth + 1, false, alpha, beta, N, wins));
                board[i] = EMPTY;
                alpha = max(alpha, best);
                if (beta <= alpha) break;
            }
        }
        return best;
    } else {
        int best = 1e9;
        for (int i = 0; i < N * N; i++) {
            if (board[i] == EMPTY) {
                board[i] = PLAYER;
                best = min(best, minimax(board, depth + 1, true, alpha, beta, N, wins));
                board[i] = EMPTY;
                beta = min(beta, best);
                if (beta <= alpha) break;
            }
        }
        return best;
    }
}

int findBestMove(vector<char>& board, int N, const vector<vector<int>>& wins) {
    int bestVal = -1e9;
    int bestMove = -1;
    for (int i = 0; i < N * N; i++) {
        if (board[i] == EMPTY) {
            board[i] = AI;
            int moveVal = minimax(board, 0, false, -1e9, 1e9, N, wins);
            board[i] = EMPTY;
            if (moveVal > bestVal) {
                bestMove = i;
                bestVal = moveVal;
            }
        }
    }
    return bestMove;
}

// ============================
// Main Game Loop
// ============================

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    int N; 
    cout << "Enter board size (e.g. 3 or 4): ";
    cin >> N;

    vector<char> board(N * N, EMPTY);
    auto wins = generateWins(N);

    cout << "Tic Tac Toe (" << N << "x" << N << ") - You = X, AI = O\n";
    printBoard(board, N);

    while (true) {
        string input;
        cout << "Enter your move (1-" << N * N << "): ";
        cin >> input;

        if (input.size() > 2 || !isdigit(input[0])) {
            cout << "Invalid move! Enter a number 1-" << N * N << ".\n";
            continue;
        }

        int move = stoi(input) - 1;
        if (move < 0 || move >= N * N) {
            cout << "Out of range! Try again.\n";
            continue;
        }
        if (board[move] != EMPTY) {
            cout << "That spot is already taken! Try again.\n";
            continue;
        }

        board[move] = PLAYER;
        printBoard(board, N);

        if (evaluate(board, wins) == -10) {
            cout << "You win!\n";
            break;
        }
        if (!isMovesLeft(board)) {
            cout << "It's a draw!\n";
            break;
        }

        cout << "AI is thinking...\n";
        int aiMove = findBestMove(board, N, wins);
        board[aiMove] = AI;
        printBoard(board, N);

        if (evaluate(board, wins) == 10) {
            cout << "AI wins!\n";
            break;
        }
        if (!isMovesLeft(board)) {
            cout << "It's a draw!\n";
            break;
        }
    }
    return 0;
}
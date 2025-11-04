#include <bits/stdc++.h>
using namespace std;

const char PLAYER = 'X', AI = 'O', EMPTY = ' ';
const int SIZE = 4;     // 4x4 grid
const int CELLS = SIZE * SIZE;

void printBoard(const vector<char>& board) {
    cout << "\n";
    for (int i = 0; i < CELLS; i++) {
        cout << (board[i] == EMPTY ? '_' : board[i]);
        if (i % SIZE != SIZE - 1)
            cout << " | ";
        else if (i != CELLS - 1)
            cout << "\n---------------------\n";
    }
    cout << "\n\n";
}

bool isMovesLeft(const vector<char>& board) {
    for (char c : board)
        if (c == EMPTY)
            return true;
    return false;
}

int evaluate(const vector<char>& board) {
    vector<vector<int>> wins = {
        // Rows
        {0,1,2,3},{4,5,6,7},{8,9,10,11},{12,13,14,15},
        // Columns
        {0,4,8,12},{1,5,9,13},{2,6,10,14},{3,7,11},
        // Diagonals
        {0,5,10,15},{3,6,9,12}
    };

    for (auto& w : wins) {
        if (board[w[0]] != EMPTY &&
            board[w[0]] == board[w[1]] &&
            board[w[1]] == board[w[2]] &&
            board[w[2]] == board[w[3]]) {
            if (board[w[0]] == AI) return +10;
            if (board[w[0]] == PLAYER) return -10;
        }
    }
    return 0;
}

int minimax(vector<char>& board, int depth, bool isMax, int alpha, int beta) {
    int score = evaluate(board);
    if (score == 10) return score - depth;
    if (score == -10) return score + depth;
    if (!isMovesLeft(board)) return 0;

    if (isMax) {
        int best = -1000;
        for (int i = 0; i < CELLS; i++) {
            if (board[i] == EMPTY) {
                board[i] = AI;
                best = max(best, minimax(board, depth + 1, false, alpha, beta));
                board[i] = EMPTY;
                alpha = max(alpha, best);
                if (beta <= alpha) break;
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < CELLS; i++) {
            if (board[i] == EMPTY) {
                board[i] = PLAYER;
                best = min(best, minimax(board, depth + 1, true, alpha, beta));
                board[i] = EMPTY;
                beta = min(beta, best);
                if (beta <= alpha) break;
            }
        }
        return best;
    }
}

int findBestMove(vector<char>& board) {
    int bestVal = -1000;
    int bestMove = -1;

    for (int i = 0; i < CELLS; i++) {
        if (board[i] == EMPTY) {
            board[i] = AI;
            int moveVal = minimax(board, 0, false, -1000, 1000);
            board[i] = EMPTY;
            if (moveVal > bestVal) {
                bestMove = i;
                bestVal = moveVal;
            }
        }
    }
    return bestMove;
}

int main() {
    vector<char> board(CELLS, EMPTY);
    cout << "4x4 Tic Tac Toe (You = X, AI = O)\n";
    printBoard(board);

    while (true) {
        string input;
        cout << "Enter your move (1-16): ";
        cin >> input;
        if (input.size() != 1 && input.size() != 2) {
            cout << "Invalid move! Enter a number 1-16.\n";
            continue;
        }
        int move = stoi(input) - 1;
        if (move < 0 || move >= CELLS || board[move] != EMPTY) {
            cout << "Invalid spot! Try again.\n";
            continue;
        }

        board[move] = PLAYER;
        printBoard(board);

        if (evaluate(board) == -10) {
            cout << "You win!\n";
            break;
        }
        if (!isMovesLeft(board)) {
            cout << "It's a draw!\n";
            break;
        }

        int aiMove = findBestMove(board);
        board[aiMove] = AI;
        cout << "AI plays position " << aiMove + 1 << "\n";
        printBoard(board);

        if (evaluate(board) == 10) {
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

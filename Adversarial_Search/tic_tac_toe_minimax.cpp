#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back

char boardState[3][3];

bool isMovesLeft(){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(boardState[i][j]=='_') return true;
        }
    }
    return false;
}

int evaluate(){
    // rows
    for(int i=0;i<3;i++){
        if(boardState[i][0]==boardState[i][1] &&
           boardState[i][1]==boardState[i][2]){
            if(boardState[i][0]=='X') return +10;
            else if(boardState[i][0]=='O') return -10;
        }
    }
    // cols
    for(int j=0;j<3;j++){
        if(boardState[0][j]==boardState[1][j] &&
           boardState[1][j]==boardState[2][j]){
            if(boardState[0][j]=='X') return +10;
            else if(boardState[0][j]=='O') return -10;
        }
    }
    // diagonals
    if(boardState[0][0]==boardState[1][1] && boardState[1][1]==boardState[2][2]){
        if(boardState[0][0]=='X') return +10;
        else if(boardState[0][0]=='O') return -10;
    }
    if(boardState[0][2]==boardState[1][1] && boardState[1][1]==boardState[2][0]){
        if(boardState[0][2]=='X') return +10;
        else if(boardState[0][2]=='O') return -10;
    }
    return 0;
}

int minimax(bool isMax){
    int score = evaluate();
    if(score==10 || score==-10) return score;
    if(!isMovesLeft()) return 0;

    if(isMax){
        int best = -1000;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(boardState[i][j]=='_'){
                    boardState[i][j]='X';
                    best = max(best, minimax(false));
                    boardState[i][j]='_';
                }
            }
        }
        return best;
    }
    else{
        int best=1000;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(boardState[i][j]=='_'){
                    boardState[i][j]='O';
                    best = min(best, minimax(true));
                    boardState[i][j]='_';
                }
            }
        }
        return best;
    }
}

pair<int,int> findBestMove(){
    int bestVal = -1000;
    pair<int,int> bestMove={-1,-1};

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(boardState[i][j]=='_'){
                boardState[i][j]='X';
                int moveVal = minimax(false);
                boardState[i][j]='_';
                if(moveVal > bestVal){
                    bestMove={i,j};
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

int32_t main(){
    ios_base::sync_with_stdio(0);cin.tie(0);

    int t=1;
    cin>>t;
    while(t--){
        // input
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                cin>>boardState[i][j]; // '_' empty
            }
        }
        pair<int,int> ans = findBestMove();
        cout<<ans.first<<" "<<ans.second<<"\n";
    }
    return 0;
}

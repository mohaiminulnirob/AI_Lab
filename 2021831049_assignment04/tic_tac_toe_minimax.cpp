#include<bits/stdc++.h>
using namespace std;
const char PLAYER='X',AI='O',EMPTY=' ';

void printBoard(const vector<char>&board){
    cout<<"\n";
    for(int i=0;i<9;i++){
        cout<<board[i];
        if(i%3!=2)
           cout<<" | ";
        else if(i!=8)
           cout<<"\n---------\n";
    }
    cout<<"\n\n";
}

bool isMovesLeft(const vector<char>&board){
    for(char cell:board){
        if(cell==EMPTY)
            return true;
    }
    return false;
}

int evaluate(const vector<char>&board){
    int wins[8][3]={{0,1,2},{3,4,5},{6,7,8},{0,3,6},
                    {1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    for(auto&w:wins){
        if(board[w[0]]==board[w[1]] && board[w[1]]==board[w[2]]){
            if(board[w[0]]==AI) return +10;
            if(board[w[0]]==PLAYER) return -10;
        }
    }
    return 0;
}

int minimax(vector<char>&board,int depth,bool isMax,int alpha,int beta){
    int score=evaluate(board);
    if(score==10) return score-depth;   
    if(score==-10) return score+depth;  
    if(!isMovesLeft(board)) return 0;

    if(isMax){
        int best=-1e9;
        for(int i=0;i<9;i++){
            if(board[i]==EMPTY){
                board[i]=AI;
                best=max(best,minimax(board,depth+1,false,alpha,beta));
                board[i]=EMPTY;
                alpha=max(alpha,best);
                if(beta<=alpha) break;
            }
        }
        return best;
    } else {
        int best=1e9;
        for(int i=0;i<9;i++){
            if(board[i]==EMPTY){
                board[i]=PLAYER;
                best=min(best,minimax(board,depth+1,true,alpha,beta));
                board[i]=EMPTY;
                beta=min(beta,best);
                if(beta<=alpha) break;
            }
        }
        return best;
    }
}

int findBestMove(vector<char>&board){
    int bestVal=-1e9;
    int bestMove=-1;
    for(int i=0;i<9;i++){
        if(board[i]==EMPTY){
            board[i]=AI;
            int moveVal=minimax(board,0,false,-1e9,1e9);
            board[i]=EMPTY;
            if(moveVal>bestVal){
                bestMove=i;
                bestVal=moveVal;
            }
        }
    }
    return bestMove;
}

int32_t main(){
    vector<char>board(9,EMPTY);
    cout<<"Tic Tac Toe (You = X, AI = O)\n";
    printBoard(board);
    
    while(true){
        string input;
        cout<<"Enter your move (1-9): ";
        cin>>input;
        if(input.size()!=1||input[0]<'1'||input[0]>'9'){
            cout<<"Invalid move! Please enter a number from 1 to 9.\n";
            continue;
        }
        int move=input[0]-'1';
        if(board[move]!=EMPTY){
            cout<<"That spot is already taken! Try again.\n";
            continue;
        }
        board[move]=PLAYER;
        if(evaluate(board)==-10){
            printBoard(board);
            cout<<"You win!\n";
            break;
        }
        if(!isMovesLeft(board)){
            printBoard(board);
            cout<<"It's a draw!\n";
            break;
        }
        int aiMove=findBestMove(board);
        board[aiMove]=AI;
        printBoard(board);
        if(evaluate(board)==10){
            cout<<"AI wins!\n";
            break;
        }
        if(!isMovesLeft(board)){
            cout<<"It's a draw!\n";
            break;
        }
    }
    return 0;
}

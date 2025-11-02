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

int checkWin(const vector<char>&board,char player){
    int wins[8][3]={{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    for(auto&w:wins)
        if(board[w[0]]==player && board[w[1]]==player && board[w[2]]==player)
            return 1;
    return 0;
}

int findBestMove(vector<char>&board){
    int wins[8][3]={{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    for(auto&w:wins){
        int countAI=0,countEmpty=0,emptyPos=-1;
        for(int i:w){
            if(board[i]==AI)
                countAI++;
            if(board[i]==EMPTY){
                countEmpty++;
                emptyPos=i;
            }
        }
        if(countAI==2 && countEmpty==1)
            return emptyPos;
    }
    for(auto&w:wins){
        int countPlayer=0,countEmpty=0,emptyPos=-1;
        for(int i:w){
            if(board[i]==PLAYER)
                countPlayer++;
            if(board[i]==EMPTY){
                countEmpty++;
                emptyPos=i;
            }
        }
        if(countPlayer==2 && countEmpty==1)
            return emptyPos;
    }
    if(board[4]==EMPTY)
        return 4;
    int corners[4]={0,2,6,8};
    for(int c:corners)
        if(board[c]==EMPTY)
            return c;
    for(int i=0;i<9;i++)
        if(board[i]==EMPTY)
            return i;
    return -1;
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
        if(checkWin(board,PLAYER)){
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
        if(checkWin(board,AI)){
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

#include <bits/stdc++.h>
using namespace std;
vector<int>ld(30,0),rd(30,0),cl(30,0);
vector<vector<vector<int>>>allSolution;
void print(vector<vector<int>>board){
    for(int i=0;i<board.size();i++){
        for(int j=0;j<board.size();j++){
            if(board[i][j]==1)
                cout<<"Q"<<" ";
            else cout<<"."<<" ";
        }
        cout<<'\n';
    }
}
bool NQueenUtil(vector<vector<int>>board,int c){
    int n=board.size();
    if(c>=board.size()){
        allSolution.push_back(board);
        return true;
    }
    for(int i=0;i<board.size();i++){ 
        if(!cl[i] && !ld[i-c+n-1] && !rd[i+c]){
            board[i][c]=1;
           ld[i-c+n-1]=rd[i+c]=cl[i]=1;
            if(NQueenUtil(board,c+1)){
               ;
            }
            ld[i-c+n-1]=rd[i+c]=cl[i]=0;
             board[i][c]=0;
        }

    }
    return true;
}
bool NQ(int n){
    vector<vector<int>>board(n,vector<int>(n,0));
    bool f=NQueenUtil(board,0);
    if(allSolution.size()>0){
        for(auto u:allSolution){
            print(u);
            cout<<'\n';
        }
    }
}
int main(){
    int t=1;
    //cin>>t;
    while(t--){
        int n;
        cin>>n;
        NQ(n);
    }
}
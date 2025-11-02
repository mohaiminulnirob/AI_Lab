#include<bits/stdc++.h>
using namespace std;

const int N=100;
vector<int>domain={0,1,2};
vector<int>adj[N];
int assign[N],vars,cons;

bool valid(int u,int col){
    for(int v:adj[u]){
        if(assign[v]==col) return false;
    }
    return true;
}

bool solve(int u){
    if(u==vars) return true;
    for(int col:domain){
        if(valid(u,col)){
            assign[u]=col;
            if(solve(u+1)) return true;
            assign[u]=-1;
        }
    }
    return false;
}

int32_t main(){
    cout<<"Enter number of variables (regions):\n";
    cin>>vars;
    cout<<"Enter number of constraints (edges between variables):\n";
    cin>>cons;
    cout<<"Enter constraints (A B if A and B are adjacent):\n";
    for(int i=0;i<cons;i++){
        char x,y;
        cin>>x>>y;
        int u=x-'A',v=y-'A';
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    fill(assign,assign+vars,-1);

    if(solve(0)){
        cout<<"Solution found:\n";
        for(int i=0;i<vars;i++){
            char color;
            if(assign[i]==0) color='R';
            else if(assign[i]==1) color='G';
            else color='B';
            cout<<char(i+'A')<<" -> "<<color<<'\n';
        }
    }
    else{
        cout<<"No solution exists.\n";
    }
    return 0;
}

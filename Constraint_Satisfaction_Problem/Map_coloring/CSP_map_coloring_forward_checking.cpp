#include<bits/stdc++.h>
using namespace std;

const int N=100;
vector<int>adj[N];
int vars,cons;

bool FC(int u, vector<int>&assign, vector<vector<int>>&domains){
    if(u==vars) return true;

    for(int col:domains[u]){
        // check if valid
        bool ok=true;
        for(int v:adj[u]){
            if(assign[v]==col){ ok=false; break; }
        }
        if(!ok) continue;

        // assign u
        assign[u]=col;

        // make a copy of domains for forward propagation
        vector<vector<int>> newDomains = domains;

        // forward check: prune color col from neighbors domain
        bool fail=false;
        for(int v:adj[u]){
            if(assign[v]==-1){
                vector<int> nd;
                for(int c : newDomains[v]){
                    if(c!=col) nd.push_back(c);
                }
                if(nd.size()==0){ fail=true; break; }
                newDomains[v]=nd;
            }
        }

        if(!fail){
            if(FC(u+1,assign,newDomains)) return true;
        }

        assign[u]=-1;
    }
    return false;
}

int32_t main(){
    cout<<"Enter number of variables:\n";
    cin>>vars;
    cout<<"Enter number of constraints:\n";
    cin>>cons;

    cout<<"Enter constraints (A B means color of A != B):\n";
    for(int i=0;i<cons;i++){
        char x,y;
        cin>>x>>y;
        int u=x-'A', v=y-'A';
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // domain initialization
    vector<vector<int>> domains(vars, vector<int>{0,1,2});
    vector<int> assign(vars,-1);

    if(FC(0,assign,domains)){
        cout<<"Solution:\n";
        for(int i=0;i<vars;i++){
            char color = (assign[i]==0?'R':assign[i]==1?'G':'B');
            cout<<char('A'+i)<<" -> "<<color<<"\n";
        }
    }else cout<<"No solution!\n";

    return 0;
}

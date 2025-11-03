#include<bits/stdc++.h>
using namespace std;

const int N=100;
int assign[N];
int var,cons,domain;
vector<int>adj[N];

bool is_valid(int region,int color){
    for(auto u:adj[region]){
        if(assign[u]==color)
          return false;
    }
    return true;
}

bool solve(int u){
    if(u==var) return true;
    for(int i=0;i<domain;i++){
        if(is_valid(u,i)){
          assign[u]=i;
        if(solve(u+1))
          return true;
        assign[u]=-1;
        }
    }
    return false;
}
int32_t main(){
    int t=1;
    //cin>>t;
    while(t--){
        cout<<"Enter number of regions: \n";
        cin>>var;
        map<string,int>varMap;
        map<int,string>rVarMap;
        cout<<"Enter regions: \n";
        for(int i=0;i<var;i++){
            string s;
            cin>>s;
            varMap[s]=i;
            rVarMap[i]=s;
        }
        cout<<"Enter number of constraints: \n";
        cin>>cons;
        for(int i=0;i<cons;i++){
            string x,y;
            cin>>x>>y;
            int a=varMap[x];
            int b=varMap[y];
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        cout<<"Enter domain number: \n";
        cin>>domain;
        map<int,string>domainMap;
        cout<<"Enter domains: \n";
        for(int i=0;i<domain;i++){
            string s;
            cin>>s;
            domainMap[i]=s;
        }
        fill(assign,assign+var,-1);
        if(solve(0)){
            for(int i=0;i<var;i++){
                cout<<rVarMap[i]<<" "<<domainMap[assign[i]]<<'\n';
            }
        }
        else{
            cout<<"No solution exist"<<'\n';
        }

    }

}
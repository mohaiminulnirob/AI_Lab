#include<bits/stdc++.h>
using namespace std;

const int N=1e3+5;
vector<int>a[N];
int edges,orig[N];
bool vis[N],found=false;
char init,target;
vector<int>traversal;

void dfs(int u)
{
    if(found) return;
    
    vis[u]=true;
    traversal.push_back(u);

    if((u+'A')==target) {
        found=true;
        return;
    }

    for(auto v:a[u])
    {
        if(!vis[v])
        {
            orig[v]=u;
            dfs(v);
        }
    }
}

int32_t main(){
    cout<<"Enter number of edges: "<<'\n';
    cin>>edges;
    cout<<"Enter initial and target node: "<<'\n';
    cin>>init>>target;
    cout<<"Enter edges: "<<'\n';
    for(int i=0;i<edges;i++)
    {
        char x,y;
        cin>>x>>y;
        int u=x-'A';
        int v=y-'A';
        a[u].push_back(v);
    }

    int start=init-'A';
    orig[start]=-1;

    dfs(start);

    cout<<"Traversing Sequence: ";
    for(int u:traversal)
        cout<<char(u+'A')<<" ";
    cout<<'\n';

    int dest=target-'A';
    if(!vis[dest])
    {
        cout<<"No path from "<<init<<" to "<<target<<'\n';
        return 0;
    }

    vector<int>path;
    for(int v=dest;v!=-1;v=orig[v])
        path.push_back(v);
    reverse(path.begin(),path.end());

    cout<<"Path: ";
    for(int u:path)
        cout<<char(u+'A')<<" ";
    cout<<'\n';
}

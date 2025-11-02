#include<bits/stdc++.h>
using namespace std;

const int N=1e3+5;
vector<int>a[N];
int edges,orig[N],level[N];
bool vis[N];
char init,target;
vector<int>traversal;
vector<int>levelSeq[N];

void bfs(int start)
{
    queue<int>q;
    q.push(start);
    vis[start]=true;
    orig[start]=-1;
    level[start]=0;

    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        traversal.push_back(u);

        if((u+'A')==target)
            return;

        for(auto v:a[u])
        {
            if(!vis[v])
            {
                vis[v]=true;
                orig[v]=u;
                level[v]=level[u]+1;
                q.push(v);
            }
        }
    }
}

int32_t main(){
    cout<<"Enter number of edegs: "<<'\n';
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
    bfs(start);
    cout<<"Traversing Sequence: ";
    int maxlevel=0;
    for(int u:traversal){
        cout<<char(u+'A')<<" ";
        levelSeq[level[u]].push_back(u);
        maxlevel=max(maxlevel,level[u]);
    }
    cout<<'\n';
    for(int i=0;i<=maxlevel;i++){
        cout<<"level "<<i<<": ";
        for(auto u:levelSeq[i]){
            cout<<char(u+'A')<<" ";
        }
        cout<<'\n';
    }
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
        cout<<char(u+'A')<<"("<<level[u]<<")"<<" ";
    cout<<'\n';
}

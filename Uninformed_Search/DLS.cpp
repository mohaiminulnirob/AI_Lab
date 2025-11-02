#include<bits/stdc++.h>
using namespace std;

const int N=1e3+5;
vector<int>a[N];
int edges,limit,orig[N];
char init,target;
bool vis[N],found=false;
vector<int>traversal;

void dls(int u,int depth)
{
    if(depth>limit||found) return;

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
            dls(v,depth+1);
        }
    }
}

int32_t main(){
    cout<<"Enter number of edegs: "<<'\n';
    cin>>edges;
    cout<<"Enter initial and target node: "<<'\n';
    cin>>init>>target;
    cout<<"Enter depth limit: "<<'\n';
    cin>>limit;
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

    dls(start,0);
    cout<<"Traversing Sequence: ";
    for(int u:traversal)
        cout<<char(u+'A')<<" ";
    cout<<'\n';
    if(!found)
    {
        cout<<"Failure! No path from "<<init<<" to "<<target<<" within depth limit "<<limit<<'\n';
        return 0;
    }
    
    vector<int>path;
    int des=target-'A';
    while(des!=-1)
    {
        path.push_back(des);
        des=orig[des];
    }
    reverse(path.begin(),path.end());

    cout<<"Path: ";
    for(int u:path)
        cout<<char(u+'A')<<" ";
    cout<<'\n';
}

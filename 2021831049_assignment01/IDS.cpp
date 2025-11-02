#include<bits/stdc++.h>
using namespace std;

const int N=1e3+5;
vector<int>a[N];
int edges,orig[N],maxDepth;
char init,target;
bool vis[N],found=false;
vector<int>traversal;

bool dls(int u,int depth,int limit)
{
    vis[u]=true;
    traversal.push_back(u);

    if((u+'A')==target) {
        found=true;
        return true;
    }

    if(depth>=limit) return false;

    for(auto v:a[u])
    {
        if(!vis[v])
        {
            orig[v]=u;
            if(dls(v,depth+1,limit)) return true;
        }
    }

    return false;
}

int32_t main(){
    cout<<"Enter number of edegs: "<<'\n';
    cin>>edges;
    cout<<"Enter initial and target node: "<<'\n';
    cin>>init>>target;
    cout<<"Enter maximum depth: "<<'\n';
    cin>>maxDepth;
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

    for(int limit=1;limit<=maxDepth;limit++)
    {
        fill(vis,vis+N,false);
        traversal.clear();
        orig[start]=-1;
        found=false;

        if(dls(start,0,limit))
        {
            cout<<"Traversing Sequence (Depth Limit "<<limit<<"): ";
            for(int u:traversal)
                cout<<char(u+'A')<<" ";
            cout<<'\n';

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
            return 0;
        }
        else cout<<"Failure (Depth Limit "<<limit<<")"<<'\n';
    }

    cout<<"No path from "<<init<<" to "<<target<<" found within depth "<<maxDepth<<'\n';
    return 0;
}

#include<bits/stdc++.h>
using namespace std;
#define ll long long

vector<vector<int>> goal = {
    {1,2,3},
    {4,5,6},
    {7,8,0}
};

int heuristic(vector<vector<int>> &a){
    int h = 0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(a[i][j] !=0 && a[i][j] != goal[i][j]) h++;
        }
    }
    return h;
}

vector<vector<vector<int>>> getSuccessors(vector<vector<int>> cur){
    vector<vector<vector<int>>> v;
    int x,y;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(cur[i][j]==0) x=i,y=j;

    int dx[4]={-1,1,0,0};
    int dy[4]={0,0,-1,1};

    for(int k=0;k<4;k++){
        int nx=x+dx[k], ny=y+dy[k];
        if(nx>=0 && nx<3 && ny>=0 && ny<3){
            auto nxt = cur;
            swap(nxt[x][y],nxt[nx][ny]);
            v.push_back(nxt);
        }
    }
    return v;
}

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin>>t;
    while(t--){
        vector<vector<int>> cur(3,vector<int>(3));
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                cin>>cur[i][j];

        double T = 100.0;
        double cooling = 0.99;

        while(T > 0.001){
            auto succ = getSuccessors(cur);

            // pick random successor
            auto next = succ[rand()%succ.size()];

            int ch = heuristic(cur);
            int nh = heuristic(next);
 
            if(nh < ch){
                cur = next; // always accept if better
            }else{
                double prob = exp(-(nh-ch)/T);
                double r = (double)rand()/RAND_MAX;
                if(r < prob) cur = next;                                                                                                              
            }
            T *= cooling;

            // BEST STOP early if solved
            if(heuristic(cur) == 0) break;
        }

        cout<<"Final heuristic = "<<heuristic(cur)<<"\n";
        for(auto &r: cur){
            for(auto &x: r) cout<<x<<" ";
            cout<<"\n";
        }
    }
    return 0;
}

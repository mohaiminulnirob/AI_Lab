#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> goal = {{1,2,3},{4,5,6},{7,8,0}};

int heuristic(vector<vector<int>> &a){
    int h=0;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(a[i][j]!=0 && a[i][j]!=goal[i][j]) h++;
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
            auto nxt=cur;
            swap(nxt[x][y],nxt[nx][ny]);
            v.push_back(nxt);
        }
    }
    return v;
}

vector<vector<int>> hillClimb(vector<vector<int>> cur){
    while(true){
        int currH = heuristic(cur);
        auto succ = getSuccessors(cur);

        vector<vector<int>> best = cur;
        int bestH = currH;

        for(auto &s : succ){
            int h = heuristic(s);
            if(h < bestH){
                bestH = h;
                best = s;
            }
        }
        if(bestH >= currH) break;
        cur = best;
    }
    return cur;
}

vector<vector<int>> randomPuzzle(){
    vector<int> vals = {1,2,3,4,5,6,7,8,0};
    random_shuffle(vals.begin(), vals.end());
    vector<vector<int>> board(3,vector<int>(3));
    int k=0;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            board[i][j]=vals[k++];
    return board;
}

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin>>t;
    while(t--){
        int restart; cin>>restart;

        vector<vector<int>> bestBoard;
        int bestH = 9999;

        for(int i=0;i<restart;i++){
            auto start = randomPuzzle();
            auto result = hillClimb(start);
            int h = heuristic(result);

            if(h < bestH){
                bestH = h;
                bestBoard = result;
            }
            if(bestH == 0) break;
        }

        cout<<"Best heuristic reached: "<<bestH<<"\n";
        for(auto &row: bestBoard){
            for(auto &x: row) cout<<x<<" ";
            cout<<"\n";
        }
        cout<<"\n";
    }
    return 0;
}

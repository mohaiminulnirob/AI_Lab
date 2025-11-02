#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back

// Target Goal
vector<vector<int>> goal = {
    {1,2,3},
    {4,5,6},
    {7,8,0}
};

// calculate heuristic = number of misplaced tiles
int heuristic(vector<vector<int>> &a){
    int h = 0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(a[i][j]!=0 && a[i][j]!=goal[i][j]) h++;
        }
    }
    return h;
}

// get all possible next states
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
            swap(nxt[x][y], nxt[nx][ny]);
            v.push_back(nxt);
        }
    }

    return v;
}

int32_t main(){
  ios_base::sync_with_stdio(0);cin.tie(0);
  
  int t=1;
  cin>>t;
  while(t--)
  {
      vector<vector<int>> cur(3, vector<int>(3));
      for(int i=0;i<3;i++)
          for(int j=0;j<3;j++)
              cin>>cur[i][j];
      
      while(true){

          int currentH = heuristic(cur);
          if(currentH==0){
            break;
          }
          auto succ = getSuccessors(cur);

          vector<vector<int>> best = cur;
          int bestH = currentH;

          for(auto &s: succ){
              int h = heuristic(s);
              if(h < bestH){
                  bestH = h;
                  best = s;
              }
          }

          if(bestH >= currentH){
            cout<<"Local optimum"<<'\n';
            break; // no better move -> local optimum

          } 
          cur = best;
      }

      cout<<"Final reached state with heuristic = "<<heuristic(cur)<<"\n";
      for(auto &row: cur){
          for(auto &x: row) cout<<x<<" ";
          cout<<"\n";
      }
  }

  return 0;
}

#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back

int n;

// Heuristic → number of attacking queen pairs
int heuristic(vector<int> &state){
    int h = 0;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(state[i] == state[j]) h++; // same row
            if(abs(state[i]-state[j]) == abs(i-j)) h++; // diagonal attack
        }
    }
    return h;
}

// generate neighbors
vector<vector<int>> getSuccessors(vector<int> &cur){
    vector<vector<int>> suc;
    for(int col=0;col<n;col++){
        for(int row=0;row<n;row++){
            if(row != cur[col]){
                vector<int> nxt = cur;
                nxt[col] = row;
                suc.pb(nxt);
            }
        }
    }
    return suc;
}

int32_t main()
{
  ios_base::sync_with_stdio(0); cin.tie(0);

  int t=1;
  cin>>t;
  while(t--)
  {
      cin>>n;

      vector<int> cur(n);
      for(int i=0;i<n;i++) cin>>cur[i]; // initial state

      while(true){
          int currH = heuristic(cur);
          auto neighbors = getSuccessors(cur);

          vector<int> best = cur;
          int bestH = currH;

          for(auto &s: neighbors){
              int h = heuristic(s);
              if(h < bestH){
                  bestH = h;
                  best = s;
              }
          }

          if(bestH >= currH) break; // stuck (local opt)
          cur = best;
      }

      cout<<"Final heuristic: "<<heuristic(cur)<<"\n";
      cout<<"State / queen rows : ";
      for(int x:cur) cout<<x<<" ";
      cout<<"\n";
  }

  return 0;
}

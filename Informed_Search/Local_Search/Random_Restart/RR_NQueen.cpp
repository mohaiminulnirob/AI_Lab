#include<bits/stdc++.h>
using namespace std;
int n;

int heuristic(vector<int> &s){
    int h=0;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(s[i] == s[j]) h++;
            if(abs(s[i]-s[j]) == abs(i-j)) h++;
        }
    }
    return h;
}

vector<int> randomState(){
    vector<int> s(n);
    for(int i=0;i<n;i++) s[i] = rand()%n;
    return s;
}

vector<int> getBestNeighbor(vector<int> cur){
    int currH = heuristic(cur);
    vector<int> best = cur;
    int bestH = currH;

    for(int col=0;col<n;col++){
        for(int row=0;row<n;row++){
            if(row != cur[col]){
                vector<int> nxt = cur;
                nxt[col] = row;
                int h = heuristic(nxt);
                if(h < bestH){
                    bestH = h;
                    best = nxt;
                }
            }
        }
    }
    return best;
}

vector<int> hillClimb(vector<int> start){
    vector<int> cur = start;
    while(true){
        vector<int> nxt = getBestNeighbor(cur);
        if(heuristic(nxt) >= heuristic(cur)) break;
        cur = nxt;
    }
    return cur;
}

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin>>t;
    while(t--){
        cin>>n;
        int restart; cin>>restart;

        vector<int> bestState;
        int bestH = 1e9;

        while(restart--){
            vector<int> st = randomState();
            vector<int> res = hillClimb(st);
            int h = heuristic(res);

            if(h < bestH){
                bestH = h;
                bestState = res;
            }
            if(bestH == 0) break;
        }

        cout<<"Best heuristic = "<<bestH<<"\n";
        for(int x:bestState) cout<<x<<" ";
        cout<<"\n";
    }
    return 0;
}

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

vector<int> randomSuccessor(vector<int> &cur){
    vector<int> nxt = cur;
    int col = rand()%n;
    int row = rand()%n;
    nxt[col] = row;
    return nxt;
}

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin>>t;
    while(t--){
        cin>>n;
        vector<int> cur(n);
        for(int i=0;i<n;i++) cin>>cur[i]; // initial

        double T = 100.0;
        double cooling = 0.99;

        while(T > 0.0001){
            vector<int> nxt = randomSuccessor(cur);

            int hc = heuristic(cur);
            int hn = heuristic(nxt);

            if(hn < hc){
                cur = nxt;
            }else{
                double prob = exp(-(hn-hc)/T);
                double r = (double)rand()/RAND_MAX;
                if(r < prob) cur = nxt;
            }

            T *= cooling;
            if(heuristic(cur) == 0) break;
        }

        cout<<"Final heuristic = "<<heuristic(cur)<<"\nState: ";
        for(int x:cur) cout<<x<<" ";
        cout<<"\n";
    }
    return 0;
}

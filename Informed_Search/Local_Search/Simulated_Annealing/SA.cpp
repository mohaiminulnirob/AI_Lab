#include<bits/stdc++.h>
using namespace std;

double f(double x){
    return -(x-3)*(x-3) + 10;
}

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin>>t;
    while(t--){
        double x; cin>>x; // starting point
        
        double T = 100.0;     // initial temperature
        double cooling = 0.99; // cooling rate
        
        while(T > 0.0001){
            double left = x - 1;
            double right = x + 1;
            double nxt = (rand()%2) ? left : right;

            double currValue = f(x);
            double nextValue = f(nxt);

            if(nextValue > currValue){
                x = nxt; // better always accept
            } else {
                double delta = currValue - nextValue;
                double prob = exp(-delta/T);
                double r = (double)rand()/RAND_MAX;

                if(r < prob) x = nxt; // accept worse move with probability
            }

            T *= cooling;
        }

        cout<<"Simulated Annealing result: x="<<x<<" value="<<f(x)<<"\n";
    }

    return 0;
}

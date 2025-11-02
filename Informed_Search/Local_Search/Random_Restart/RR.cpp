#include<bits/stdc++.h>
using namespace std;
#define ll long long

double f(double x){
    return -(x-3)*(x-3) + 10;
}

// basic hill climbing run
double hillClimb(double x){
    while(true){
        double left = x-1;
        double right = x+1;

        double best = x;
        if(f(left) > f(best)) best = left;
        if(f(right) > f(best)) best = right;

        if(best == x) break;
        x = best;
    }
    return x;
}

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin>>t;
    while(t--){
        int restart; cin>>restart; // number of restarts
        double finalBestX = 0;
        double finalBestVal = -1e18;

        while(restart--){
            double startX = rand()%21 - 10; // random start between -10 to +10
            double resultX = hillClimb(startX);
            double val = f(resultX);

            if(val > finalBestVal){
                finalBestVal = val;
                finalBestX = resultX;
            }
        }

        cout<<"Best found x="<<finalBestX<<" value="<<finalBestVal<<"\n";
    }

    return 0;
}

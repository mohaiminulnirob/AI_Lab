#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back

double f(double x){
    return -(x-3)*(x-3) + 10; // sample function
}

int32_t main()
{
  ios_base::sync_with_stdio(0);cin.tie(0);

  int t=1;
  cin>>t;
  while(t--)
  {
      double x; 
      cin>>x; // starting state
      while (true)
      {
          double left = x-1;
          double right = x+1;

          double best = x;
          if(f(left) > f(best)) best = left;
          if(f(right) > f(best)) best = right;

          if(best == x){
              // no better state => stop (local maxima)
              break;
          }
          x = best;
      }
      cout<<"Local Maximum at x = "<<x<<" with value = "<<f(x)<<"\n";
  }

  return 0;
}

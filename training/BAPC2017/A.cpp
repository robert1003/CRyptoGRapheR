#include<bits/stdc++.h>
#define ll long long
#define M_PI 3.1415926535897932384

using namespace std;

int main(){
  ios::sync_with_stdio(0); cin.tie(0);
  int n,m; double r;
  cin>>m>>n>>r;
  int x1,y1,x2,y2; cin>>x1>>y1>>x2>>y2;
  double ans=1e12;
  for(int i=min(y1,y2);i>=0;i--)
    ans=min(ans,(y1-i+y2-i)*r/n+abs(x1-x2)*M_PI/m*r/n*i);
  cout<<fixed<<setprecision(12)<<ans<<"\n";
  return 0;
}


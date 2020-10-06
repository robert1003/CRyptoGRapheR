#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int k, _a[14], sum;

void init() {
  cin >> k; sum=0;
  for(int i = 0 ; i < 7 ; ++i) {
    cin >> _a[i]; _a[i+7]=_a[i];
    sum += _a[i];
  }
}
int calc(int *a){
  int t=(k+sum-1)/sum*7-7,r=k%sum;
  if(r==0) r+=sum;
  for(int i=0;i<7&&r;i++){
    t++; r-=a[i];
  }
  return t;
}
void solve() {
  int ans = 1e9;
  for(int i=0;i<7;i++) ans=min(ans,calc(_a+i));
  cout<<ans<<"\n";
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int t; cin>>t;
  while(t--){
    init();
    solve();
  }
}


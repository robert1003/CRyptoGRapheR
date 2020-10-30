#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

ll a[100005];

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int t; cin>>t;
  for(int tt=1;tt<=t;tt++){
    int n; cin>>n;
    for(int i=0;i<n;i++) cin>>a[i];
    sort(a,a+n);
    ll ct=0; int ans=0;
    for(int i=0;i<n;i++){
      if(ct<=a[i]) ct+=a[i],ans++;
    }
    cout<<"Case #"<<tt<<": "<<ans<<"\n";
  }
  return 0;
}


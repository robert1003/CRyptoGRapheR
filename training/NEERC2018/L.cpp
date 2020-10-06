#include<bits/stdc++.h>
#define ll long long

using namespace std;

ll a[100005],b[100005],c[100005];
int ind[100005];

int main(){
  cin.tie(0); ios::sync_with_stdio(0);
  int n,k; cin>>n>>k;
  for(int i=0;i<n;i++) cin>>a[i];
  for(int i=0;i<n;i++) cin>>b[i];
  int r=0;
  for(int i=0;i<n;i++) c[a[i]]++;
  for(int i=1;i<=k;i++) r+=(c[i]==0);
  iota(ind,ind+n,0);
  sort(ind,ind+n,[&](int i,int j){return b[i]<b[j];});
  ll ans=0;
  for(int _i=0;_i<n&&r;_i++){
    int i=ind[_i];
    if(c[a[i]]>1){
      --c[a[i]];
      ans+=b[i];
      r--;
    }
  }
  cout<<ans<<"\n";
  return 0;
}


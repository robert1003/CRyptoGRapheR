#include<bits/stdc++.h>
#define ll long long

using namespace std;

int main(){
  ios::sync_with_stdio(0); cin.tie(0);
  int t; cin>>t;
  while(t--){
    int n,m; cin>>n>>m;
    int r=0,c=0;
    for(int i=0;i<n;i++){
      int x; cin>>x; r|=1<<x;
    }
    for(int i=0;i<m;i++){
      int x; cin>>x; c|=1<<x;
    }
    int ans=0;
    for(int i=0;i<16;i++){
      int cr=0,cc=0;
      for(int j=0;j<4;j++){
        if(i&(1<<j)){
          cr|=(1<<(j>>1));
          cc|=(1<<(j&1));
        }
      }
      if(cr==r&&cc==c) ans++;
    }
    cout<<ans<<"\n";
  }
  return 0;
}

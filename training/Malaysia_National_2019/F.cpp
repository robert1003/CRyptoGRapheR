#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
const ll mod=1000000007;

bool adj[2005][2005];
ll dp[2005][300];

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n,e,k; cin>>n>>e>>k;
  while(k--){
    int x,y; cin>>x>>y;
    adj[x-1][y-1]=1;
  }
  dp[0][0]=1;
  for(int i=0;i<n;i++){
    for(int j=0;j<256;j++){
      if(!dp[i][j]) continue;
      int st=(j<<1);
      for(int k=-e;k<=e;k++){
        if(i+k<0||i+k>=n) continue;
        if(adj[i][i+k]) continue;
        if(st&(1<<(4-k))) continue;
        int nst=(st|(1<<(4-k)))&0xff;
        dp[i+1][nst]=(dp[i+1][nst]+dp[i][j])%mod;
      }
    }
  }
  cout<<accumulate(dp[n],dp[n]+256,0LL)<<"\n";
  return 0;
}


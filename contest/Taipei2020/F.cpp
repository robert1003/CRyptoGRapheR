#include<bits/stdc++.h>
#define ll long long

using namespace std;

vector<int> G[200005];
int dp[200005][2];
int c[100005][2];
int n;

void dfs(int x,int p){
  for(int i:G[x]){
    if(i>=n&&i!=p){
      dfs(i,x);
      dp[x][0]+=min(dp[i][0],dp[i][1]);
      dp[x][1]+=dp[i][0];
    }
  }
  dp[x][0]++;
}

int main(){
  ios::sync_with_stdio(0); cin.tie(0);
  int m; cin>>n>>m;
  for(int i=0;i<n+m;i++){
    int a,b; cin>>a>>b;
    G[a].push_back(b);
    G[b].push_back(a);
  }
  for(int i=0;i<n;i++) dfs(i,i);
  for(int i=0;i<n;i++){
    c[i][0]=dp[i][1];
    c[i][1]=dp[i][0];
  }
  int ans=1e9;
  dp[0][0]=1e9; dp[0][1]=c[0][1];
  for(int i=1;i<n;i++){
    dp[i][0]=dp[i-1][1]+c[i][0];
    dp[i][1]=min(dp[i-1][0],dp[i-1][1])+c[i][1];
  }
  ans=min(dp[n-1][0],dp[n-1][1]);
  dp[0][0]=c[0][0]; dp[0][1]=1e9;
  for(int i=1;i<n;i++){
    dp[i][0]=dp[i-1][1]+c[i][0];
    dp[i][1]=min(dp[i-1][0],dp[i-1][1])+c[i][1];
  }
  ans=min(ans,dp[n-1][1]);
  cout<<ans<<"\n";
  return 0;
}

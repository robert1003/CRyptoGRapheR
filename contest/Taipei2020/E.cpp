#include<bits/stdc++.h>
#define ll long long

using namespace std;

string s; int n,k;
bool f[505][505];
int dp[505][505];

void solve(int l,int r){
  if(dp[l][r]!=-1) return;
  if(l>r){
    f[l][r]=1;
    dp[l][r]=0;
    return;
  }
  if(l==r){
    f[l][r]=(k==1);
    dp[l][r]=1;
    return;
  }
  dp[l][r]=-2;
  for(int i=l;i<r;i++){
    solve(l,i); solve(i+1,r);
    if(f[l][i]&&f[i+1][r]){
      f[l][r]=1; break;
    }
  }
  if(f[l][r]) dp[l][r]=0;
  if(s[l]==s[r]){
    for(int i=l+1;i<r;i++){
      if(s[i]==s[l]){
        solve(l,i); solve(i,r);
        if(dp[l][i]!=-2&&dp[i][r]!=-2) 
          dp[l][r]=max(dp[l][r],dp[l][i]+dp[i][r]-1);
      }
    }
    solve(l+1,r-1);
    if(f[l+1][r-1]) dp[l][r]=max(dp[l][r],2);
    if(dp[l][r]==0||(dp[l][r]>=k)) f[l][r]=1;
  }
}

int main(){
  ios::sync_with_stdio(0); cin.tie(0);
  cin>>s>>k; n=s.size();
  for(int i=0;i<n;i++) for(int j=0;j<n;j++) dp[i][j]=-1;
  solve(0,n-1);
  cout<<(f[0][n-1]?"Yes\n":"No\n");
  return 0;
}

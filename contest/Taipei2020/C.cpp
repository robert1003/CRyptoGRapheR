#include<bits/stdc++.h>
#define ll long long

using namespace std;

int dp[2][10005],*pre=dp[0],*cur=dp[1];

int main(){
  ios::sync_with_stdio(0); cin.tie(0);
  int t; cin>>t;
  while(t--){
    int n,k; cin>>n>>k;
    int p=0;
    cur[0]=k;
    for(int i=1;i<n;i++){
      swap(cur,pre);
      if(~pre[p]&1) p++;
      for(int j=0;j<=i;j++){
        cur[j]=0;
        if(j!=i) cur[j]+=(pre[j]+1)/2;
        if(j) cur[j]+=pre[j-1]/2;
      }
    }
    cout<<p<<"\n";
  }
  return 0;
}

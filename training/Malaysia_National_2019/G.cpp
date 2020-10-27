#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

const ll M = (int)1e9 + 7;

vector<int> G[20005][105];
int nv[20005],ind[20005],bac[20005],m;
bool v[20005];
ll w[20005][105],ans[20005],dp[105];
vector<int> GG[20005];

void dfs(vector<int> cG[],int x){
  v[x]=1;
  for(int i:cG[x]){
    if(!v[i]) dfs(cG,i);
  }
  ind[m++]=x;
}

void run(int id){
  for(int i=0;i<nv[id];i++){
    if(w[id][i]<0){
      assert(ans[-w[id][i]-1]!=-1);
      w[id][i]=ans[-w[id][i]-1]+1;
    }
  }
  fill(v,v+nv[id],0);
  m=0;
  for(int i=0;i<nv[id];i++){
    if(!v[i]) dfs(G[id],i);
  }
  fill(dp,dp+nv[id],-1);
  ans[id]=0;
  for(int _i=0;_i<nv[id];_i++){
    int i=ind[_i];
    dp[i]=0;
    for(int j:G[id][i]){
      assert(dp[j]!=-1);
      dp[i]=max(dp[i],dp[j]);
    }
    dp[i]=(dp[i] + w[id][i]) % M;
    ans[id]=max(ans[id],dp[i]);
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n,q; cin>>n>>q;
  for(int i=0;i<n;i++){
    cin>>nv[i];
    for(int j=0;j<nv[i];j++){
      int k; cin>>k;
      while(k--){
        int x; cin>>x;
        G[i][j].push_back(x-1);
      }
      int t; ll p; cin>>t>>p;
      if(t==0) w[i][j]=p;
      else w[i][j]=-p,GG[p-1].push_back(i);
    }
  }
  for(int i=0;i<n;i++){
    if(!v[i]) dfs(GG,i);
  }
  fill(ans,ans+n,-1);
  copy(ind,ind+n,bac);
  for(int i=n-1;i>=0;i--) run(bac[i]);
  while(q--){
    int x; cin>>x;
    cout<<ans[x-1]%M<<"\n";
  }
  return 0;
}


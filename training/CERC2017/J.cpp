#pragma GCC optimize ("O3,unroll-loops,no-stack-protector")
//#pragma GCC target ("sse,sse2,sse3,ssse3,popcnt,abm,mmx,avx,tune=native")
#include<bits/stdc++.h>
#define ll long long
 
using namespace std;
 
vector<int> E[1000006];
int sz[1000006],p[1000006],id[1000005],t;
int flag;
int compSz;
 
void dfs(int i, int f) {
  p[i]=f;
  for(auto x : E[i]) {
    if(x != f)
      dfs(x, i);
  }
  id[t++]=i;
}
 
int main(){
  cin.tie(0); ios::sync_with_stdio(0);
  int n;
  cin >> n;
  for(int i = 1; i < n; ++i) {
    int a, b;
    cin >> a >> b;
    E[a].push_back(b);
    E[b].push_back(a);
  }
  dfs(1,1);
  for(int i = 1; i < n; ++i) {
    if(n %(i+1)) continue;
    compSz = n/(i + 1);
    flag = 1;
    fill(sz,sz+n+1,1);
    for(int j=0;j<n&&flag;j++){
      int x=id[j];
      if(sz[x]>compSz) flag=0;
      else if(sz[x]==compSz) sz[x]=0;
      sz[p[x]]+=sz[x];
    }
    if(flag)
      cout << i << ' ';
  }
  cout<<"\n";
  return 0;
}

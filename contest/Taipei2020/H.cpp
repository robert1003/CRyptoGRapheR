#include<bits/stdc++.h>
#define ll long long

using namespace std;

int p[10005],sz[10005];
int find(int x){return x==p[x]?x:p[x]=find(p[x]);}
tuple<ll,int,int> edge[500005],chose[10005];
int main(){
  ios::sync_with_stdio(0); cin.tie(0);
  int n,m; cin>>n>>m;
  for(int i=0;i<m;i++){
    int u,v; ll w; cin>>u>>v>>w;
    edge[i]=make_tuple(w,u-1,v-1);
  }
  sort(edge,edge+m);
  ll mn=1e17;
  iota(p,p+n,0);
  for(int i=m-1;i>=0;i--){
    int u,v; ll w; tie(w,u,v)=edge[i];
    if((u=find(u))!=(v=find(v))){
      p[v]=u;
      mn=w;
    }
  }
  iota(p,p+n,0);
  int k=0;
  for(int i=0;i<m;i++){
    int u,v; ll w; tie(w,u,v)=edge[i];
    if(w<mn) continue;
    if((u=find(u))!=(v=find(v))){
      p[v]=u;
      chose[k++]=edge[i];
    }
  }
  ll ans=0;
  iota(p,p+n,0); fill(sz,sz+n,1);
  for(int i=k-1;i>=0;i--){
    int u,v; ll w; tie(w,u,v)=chose[i];
    u=find(u); v=find(v);
    ans+=w*sz[u]*sz[v];
    p[u]=v; sz[v]+=sz[u];
  }
  cout<<ans<<"\n";
  return 0;
}

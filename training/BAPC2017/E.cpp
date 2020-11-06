#include<bits/stdc++.h>
#define ll long long

using namespace std;

struct Dinic{
  static const int MXN=10000;
  struct Edge{int v,f,re;};
  int n,s,t,level[MXN];
  vector<Edge> E[MXN];
  void init(int _n,int _s,int _t){
    n=_n;s=_s;t=_t;
    for(int i=0;i<n;i++) E[i].clear();
  }
  void add_edge(int u,int v,int f){
    E[u].push_back({v,f,(int)E[v].size()});
    E[v].push_back({u,0,(int)E[u].size()-1});
  }
  bool BFS(){
    for(int i=0;i<n;i++) level[i]=-1;
    queue<int> que;
    que.push(s);
    level[s]=0;
    while(!que.empty()){
      int u=que.front(); que.pop();
      for(auto &it:E[u]){
        if(it.f>0&&level[it.v]==-1){
          level[it.v]=level[u]+1;
          que.push(it.v);
        }
      }
    }
    return level[t]!=-1;
  }
  int DFS(int u,int nf){
    if(u==t) return nf;
    int res=0;
    for(auto &it:E[u]){
      if(it.f>0&&level[it.v]==level[u]+1){
        int tf=DFS(it.v,min(nf,it.f));
        res+=tf; nf-=tf; it.f-=tf;
        E[it.v][it.re].f+=tf;
        if(nf==0) return res;
      }
    }
    if(!res) level[u]=-1;
    return res;
  }
  int flow(int res=0){
      while(BFS())
        res+=DFS(s,2147483647);
      return res;
  }
}flow;

ll dis(const pair<int,int> &a,const pair<int,int> &b){
  ll dx=a.first-b.first,dy=a.second-b.second;
  return dx*dx+dy*dy;
}

int main(){
  ios::sync_with_stdio(0); cin.tie(0);
  int n,na,nb; cin>>n>>na>>nb;
  vector<pair<int,int>> a(na),b(nb);
  for(int i=0;i<na;i++)
    cin>>a[i].first>>a[i].second;
  for(int i=0;i<nb;i++)
    cin>>b[i].first>>b[i].second;
  ll l=0,r=5e8,m;
  while(l<r){
    m=(l+r+1)>>1;
    flow.init(na+nb+2,na+nb,na+nb+1);
    for(int i=0;i<na;i++){
      for(int j=0;j<nb;j++){
        if(dis(a[i],b[j])<m)
          flow.add_edge(i,j+na,1);
      }
    }
    for(int i=0;i<na;i++) flow.add_edge(flow.s,i,1);
    for(int i=0;i<nb;i++) flow.add_edge(i+na,flow.t,1);
    int tmp=na+nb-flow.flow();
    if(tmp<n) r=m-1;
    else l=m;
  }
  cout<<fixed<<setprecision(12)<<sqrt(l)<<"\n";
  return 0;
}


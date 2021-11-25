struct Dinic{
  static const int MXN=10000;
  struct Edge{ int v,c,r; };
  int n,s,t,level[MXN]; vector<Edge> G[MXN];
  void init(int _n,int _s,int _t){
    n=_n; s=_s; t=_t;
    for (int i=0; i<n; i++) G[i].clear();
  }
  void addEdge(int u,int v,int c){
    G[u].push_back({v,c,(int)G[v].size()});
    G[v].push_back({u,0,(int)G[u].size()-1});
  }
  bool BFS(){
    for (int i=0;i<n;i++) level[i]=-1;
    queue<int> que; que.push(s); level[s]=0;
    while(!que.empty()){
      int u=que.front(); que.pop();
      for (auto &it:G[u]){
        if(it.c>0&&level[it.v]==-1){
          level[it.v]=level[u]+1; que.push(it.v);
    } } }
    return level[t]!=-1;
  }
  int DFS(int u,int nf){
    if(u==t) return nf;
    int res=0;
    for (auto &it:G[u]){
      if(it.c>0&&level[it.v]==level[u]+1){
        int tf=DFS(it.v,min(nf,it.c));
        res+=tf; nf-=tf; it.c-=tf;
        G[it.v][it.r].c+=tf;
        if(nf==0) return res;
      }
    }
    if(!res) level[u]=-1;
    return res;
  }
  int flow(int res=0){
    while(BFS()) res+=DFS(s,2147483647);
    return res;
  } // reset: do nothing
}flow;

struct Chordal{
  static const int MXN=100010;
  vector<int> E[MXN],V[MXN];
  int n,f[MXN],rk[MXN],order[MXN],stk[MXN],nsz[MXN];
  bool vis[MXN],isMaximalClique[MXN];
  void init(int _n){
    n=_n;
    for(int i=0;i<=n;++i){
      E[i].clear(),V[i].clear();
      f[i]=rk[i]=order[i]=vis[i]=0;
    }
  }
  void addEdge(int x,int y){
    E[x].push_back(y),E[y].push_back(x);
  }
  void mcs(){
    for(int i=1;i<=n;++i) V[0].push_back(i);
    for(int i=n,M=0;i>=1;--i){
      for(;;){
        while(V[M].size()&&vis[V[M].back()])
          V[M].pop_back();
        if(V[M].size()) break; else M--;
      }
      auto x=V[M].back();order[i]=x;rk[x]=i;vis[x]=1;
      for(auto y:E[x]) if(!vis[y])
        f[y]++,V[f[y]].push_back(y),M=max(M,f[y]);
    }
  }
  bool isChordal(){
    for(int i=0;i<=n;++i) vis[i]=stk[i]=0;
    for(int i=n;i>=1;--i){
      int top=0,cnt=0,m=n+1;
      for(auto x:E[order[i]]) if(rk[x] > i)
        stk[top++]=x,vis[x]=1,m=min(m,rk[x]);
      if(m==n+1) continue;
      for(auto x:E[order[m]]) if(vis[x]) ++cnt;
      for(int j=0;j<top;++j) vis[stk[j]]=0;
      if(cnt+1!=top) return 0;
    }
    return 1;
  }
  void getMaximalClique(){
    for(int i=n;i>=1;--i){
      int M=n+1,w=order[i],v=0;
      nsz[w]=0;isMaximalClique[w]=1;
      for(auto x:E[w]) if(rk[x]>i){
        nsz[w]++; if(rk[x]<M) M=rk[x],v=x;
      }
      if(v) isMaximalClique[v]&=nsz[v]+1>nsz[w];
    }
  }
  int getMaximumClique(){
    int res=0;
    for(int i=1;i<=n;++i) res=max(res,f[i]+1);
    return res;
  }
  int getMaximumIndependentSet(){
    for(int i=0;i<=n;++i) vis[i]=0;
    int res=0;
    for(int i=1;i<=n;++i) if(!vis[order[i]]){
      res++,vis[order[i]]=1;
      for(auto x:E[order[i]]) vis[x]=1;
    }
    return res;
  }
};

struct BccVertex {
  int n,nBcc,step,dfn[MXN],low[MXN];
  vector<int> E[MXN],bccv[MXN];
  // vector<pair<int,int>> bcce[MXN];
  int top,stk[MXN];
  // pair<int,int> estk[MXM]; // max edge number
  // int id[MXN],pos[MXN];
  void init(int _n) {
    n = _n; nBcc = step = 0;
    for (int i=0; i<n; i++) E[i].clear();
  }
  void addEdge(int u, int v)
  { E[u].push_back(v); E[v].push_back(u); }
  void DFS(int u, int f) {
    dfn[u] = low[u] = step++;
    stk[top++] = u;
    for (auto v:E[u]) {
      if (v == f) continue;
      if (dfn[v] == -1) {
        // estk[etop++]={u,v};
        DFS(v,u);
        low[u] = min(low[u], low[v]);
        if (low[v] >= dfn[u]) {
          int z;
          bccv[nBcc].clear(); // bcce[nBcc].clear();
          // pair<int,int> ez;
          // do {
          //   ez=estk[--etop];
          //   bcce[nBcc].push_back(ez);
          // }while(ez.first!=u);
          do {
            z = stk[--top];
            // id[z]=nBcc; pos[z]=bccv[nBcc].size();
            bccv[nBcc].push_back(z);
          } while (z != v);
          bccv[nBcc++].push_back(u);
        }
      }else
        low[u] = min(low[u],dfn[v]);
        //if(dfn[v]<dfn[u]) estk[etop++]={u,v};
    }
  }
  vector<vector<int>> solve() {
    vector<vector<int>> res;
    for (int i=0; i<n; i++)
      dfn[i] = low[i] = -1;
    for (int i=0; i<n; i++)
      if (dfn[i] == -1) {
        top = 0; etop = 0;
        DFS(i,i);
      }
    for(int i=0;i<nBcc;i++) res.push_back(bccv[i]);
    return res;
  }
  /* bccv[.first][{.first,.second}]={u,v}
  pair<int,pair<int,int>> getpos(int u,int v){
    if(dfn[u]>dfn[v]) swap(u,v);
    int cid=id[v];
    if(id[u]==cid) return {cid,{pos[v],pos[u]}};
    else return {cid,pos[v],{bccv[cid].size()-1}};
  } */
}graph;

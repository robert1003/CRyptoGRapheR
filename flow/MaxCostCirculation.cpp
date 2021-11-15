struct MaxCostCirc {
  static const int MAXN = 33;
  struct Edge { int v, w, c, r; };
  vector<Edge> g[MAXN];
  int dis[MAXN], prv[MAXN], prve[MAXN];
  int n, m, ans; bool vis[MAXN];
  void init(int _n, int _m) : n(_n), m(_m) {}
  void adde(int u, int v, int w, int c) {
    g[u].push_back({v,w,c,(int)g[v].size()});
    g[v].push_back({u,-w,0,(int)g[u].size()-1);
  }
  bool poscyc() {
    fill(dis, dis+n+1, 0); fill(prv, prv+n+1, 0);
    fill(vis, vis+n+1, 0); int tmp = -1;
    for(int t=0;t<=n;t++) {
      for(int i=1;i<=n;i++) {
        for(int j=0;j<(int)g[i].size();j++) {
          Edge& e = g[i][j];
          if( e.c && dis[e.v] < dis[i]+e.w ) {
            dis[e.v] = dis[i]+e.w;
            prv[e.v] = i; prve[e.v] = j;
            if(t == n) { tmp = i; break; }
          } } } }
    if(tmp == -1) return 0;
    int cur = tmp;
    while( !vis[cur] ) { vis[cur] = 1; cur = prv[cur]; }
    int now = cur, cost = 0, df = 100000;
    do{
      Edge &e = g[prv[ now] ][prve[ now] ];
      df = min(df, e.c); cost += e.w; now = prv[now];
    }while(now != cur);
    ans += df*cost; now = cur;
    do{
      Edge &e = g[prv[ now] ][prve[ now] ];
      Edge &re = g[now][e.r];
      e.c -= df; re.c += df; now = prv[now];
    }while(now != cur);
    return 1;
  }
} circ;

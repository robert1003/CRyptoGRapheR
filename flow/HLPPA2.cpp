template <int MAXN, class T = int>
struct HLPP {
  const T INF = numeric_limits<T>::max();
  struct Edge {
    int to, rev;
    T f;
  };
  int s = MAXN-1, t = MAXN-2;
  vector<Edge> adj[MAXN];
  deque<int> lst[MAXN];
  vector<int> gap[MAXN];
  int ptr[MAXN];
  T excess[MAXN];
  int h[MAXN], cnt[MAXN], work, hst/*highest*/;
  void init(int _s, int _t) {
      for(auto &x : adj) x.clear();
      s = _s, t = _t;
  }
  void addEdge(int from, int to, T f, bool isDirected = true) {
    adj[from].push_back({to, (int)adj[to].size(), f});
    adj[to].push_back({from, (int)adj[from].size()-1, isDirected ? 0 : f});
  }
  void updHeight(int v, int nh) {
    work++;
    if(h[v] != MAXN) cnt[h[v]]--;
    h[v] = nh;
    if(nh == MAXN) return;
    cnt[nh]++, hst = nh; gap[nh].push_back(v);
    if(excess[v]>0) lst[nh].push_back(v), ptr[nh]++;
  }
  void globalRelabel() {
    work = 0;
    fill(begin(h), end(h), MAXN);
    fill(begin(cnt), end(cnt), 0);
    for(int i=0; i<=hst; i++)
        lst[i].clear(), gap[i].clear(), ptr[i] = 0;
    queue<int> q({t}); h[t] = 0;
    while(!q.empty()) {
      int v = q.front(); q.pop();
      for(auto &e : adj[v])
        if(h[e.to] == MAXN && adj[e.to][e.rev].f > 0)
          q.push(e.to), updHeight(e.to, h[v] + 1);
      hst = h[v];
    }
  }
  void push(int v, Edge &e) {
    if(excess[e.to] == 0)
      lst[h[e.to]].push_back(e.to), ptr[h[e.to]]++;
    T df = min(excess[v], e.f);
    e.f -= df, adj[e.to][e.rev].f += df;
    excess[v] -= df, excess[e.to] += df;
  }
  void discharge(int v) {
    int nh = MAXN;
    for(auto &e : adj[v]) {
      if(e.f > 0) {
        if(h[v] == h[e.to] + 1) {
          push(v, e);
          if(excess[v] <= 0) return;
        }
        else nh = min(nh, h[e.to] + 1);
      }
    }
    if(cnt[h[v]] > 1) updHeight(v, nh);
    else {
      for(int i = h[v]; i < MAXN; i++) {
        for(auto j : gap[i]) updHeight(j, MAXN);
        gap[i].clear(), ptr[i] = 0;
      }
    }
  }
  T solve(int heur_n = MAXN) {
    fill(begin(excess), end(excess), 0);
    excess[s] = INF, excess[t] = -INF;
    globalRelabel();
    for(auto &e : adj[s]) push(s, e);
    for(; hst >= 0; hst--) {
      while(!lst[hst].empty()) {
        int v=lst[hst].back(); lst[hst].pop_back();
        discharge(v);
        if(work > 4 * heur_n) globalRelabel();
      }
    }
    return excess[t] + INF;
  }
};

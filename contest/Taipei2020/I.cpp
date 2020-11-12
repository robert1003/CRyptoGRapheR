#include<bits/stdc++.h>
#define ll long long

using namespace std;
#define MXN 1005

struct BccVertex {
  int n, nScc, step, dfn[MXN], low[MXN];
  vector<int> E[MXN], sccv[MXN];
  int top , stk[MXN];
  bool flag[MXN];
  void init(int _n) {
    n = _n, nScc = step = 0;
    for (int i = 0; i < n; ++i) E[i].clear();
    for(int i = 0; i < n; ++i) flag[i] = 0;
  }
  void addEdge(int u, int v) {
    E[u].push_back(v), E[v].push_back(u);
  }
  void DFS(int u, int f ){
    dfn[u ] = low[u] = step++;
    stk[top++] = u;
    int cnt = 0;
    for(auto v :E[u]) {
      if(v == f) continue;
      if (dfn[v] == -1) {
        ++cnt;
        DFS(v, u);
        low[u] = min(low[u], low[v]);
        if(low[v] >= dfn[u]) {
          if(u != f)
            flag[u] = 1;
          int z;
          sccv[nScc].clear();
          do {
            z = stk[--top];
            sccv[nScc].push_back(z);
          } while(z !=v );
          sccv[nScc++].push_back(u);
        }
      }else
        low[u] = min(low[u], dfn[v]);
    }
    if(u == f and cnt != 1)
      flag[u] = 1;
  }
  vector<vector<int>> solve() {
    vector<vector<int>> res;
    for(int i =0; i < n; ++i) {
      dfn[i] = low[i] = -1;
    }
    for(int i = 0 ; i < n ; ++i) {
      if(dfn[i] == -1) {
        top = 0;
        DFS(i, i);
      }
    }
    for(int i = 0; i < nScc; ++i)
      res.push_back(sccv[i]);
    return res;
  }
}graph;

int main(){
  ios::sync_with_stdio(0); cin.tie(0);
  int L;
  cin >> L;
  while(L--) {
    int n, m;
    cin >> n >> m;
    graph.init(n);
    for(int i = 0; i < m; ++i) {
      int a, b;
      cin >> a >> b;
      --a , -- b;
      graph.addEdge(a, b);
    }
    auto sccs = graph.solve();
    // for(auto&& scc : sccs) {
    //   for(auto x : scc)
    //     cout << x << ' ';
    //   cout << endl;
    // }

    int a = count(graph.flag, graph.flag + n, 1), b = 0;
    for(auto &&scc : sccs)
      if(scc.size() == 2) ++b;
    int p = sccs.size(), q = 0;

    int mm = 0, pos = -1;
    for(int i = 0; i < sccs.size(); ++i) {
      if(sccs[i].size() >= mm) {
        mm = sccs[i].size();
        pos = i;
      }
    }
    set<int> S;
    for(auto v : sccs[pos])
      S.insert(v);
    for(auto v : sccs[pos])
      for(auto u : graph.E[v])
        if(S.count(u))
          ++q;
    q /= 2;

    auto gg = gcd(p, q);
    p /= gg, q /= gg;

    cout << a << ' ' << b << ' ' << p << ' ' << q << '\n';
  }
  return 0;
}

#include <bits/stdc++.h>
#pragma comment(linker, "/STACK:2000000")
#define F first
#define S second
using namespace std;
using ll = long long;

const int N = (int)1e5 + 5;
const int M = 18;

int n, F, cnt = 0, dep[N], fa[N][M], idx[N], gidx[N];
vector<int> G[N];
map<int, int> group[N];

void dfs(int u, int d, int f) {
  dep[u] = d; fa[u][0] = f;
  for(int i = 1 ; i < M ; ++i) fa[u][i] = fa[fa[u][i - 1]][i - 1];
  for(auto v : G[u]) if(v != f) {
    dfs(v, d + 1, u);
  }
}
int lca(int u, int v) {
  if(dep[u] > dep[v]) swap(u, v);
  for(int k = M - 1 ; k >= 0 ; --k) {
    if(dep[fa[v][k]] >= dep[u]) v = fa[v][k];
  }
  if(u == v) return u;
  for(int k = M - 1 ; k >= 0 ; --k) {
    if(fa[u][k] != fa[v][k]) {
      u = fa[u][k];
      v = fa[v][k];
    }
  }
  return fa[u][0];
}
int dis(int u, int v) {
  return dep[u] + dep[v] - 2 * dep[lca(u, v)];
}

void init() {
  cin >> n >> F;
  for(int i = 0 ; i < n - 1 ; ++i) {
    int a, b; cin >> a >> b; a--, b--;
    G[a].push_back(b);
    G[b].push_back(a);
  }
  dfs(0, 0, 0);
}
void solve() {
  vector<tuple<int, int, int> > sets;
  for(int i = 0 ; i < F ; ++i) {
    int a, b; cin >> a >> b; a--, b--;
    sets.push_back({a, b, dis(a, b)});
  }
  sort(sets.begin(), sets.end(), [&](auto a, auto b){ return get<2>(a) > get<2>(b); });
  for(auto [u, v, dis] : sets) {
    //cerr << u + 1 << ' ' << v + 1 << ' ' << dis << '\n';
    if(idx[u] != idx[v]) return void(cout << "No\n");
    if(idx[u]) {
      int l = min(gidx[u], gidx[v]), r = max(gidx[u], gidx[v]);
      //cerr << "gidx l r: " << l << ' ' << r << '\n';
      auto it1 = prev(group[idx[u]].upper_bound(l));
      //cerr << "it1: " << it1->F << ' ' << it1->S << '\n';
      if(it1->S < r) return void(cout << "No\n");
      pair<int, int> p = *it1; group[idx[u]].erase(it1);
      assert(p.F <= l && r <= p.S);
      vector<pair<int, int> > vec;
      vec.push_back({l, r});
      if(p.F < l) vec.push_back({p.F, l - 1});
      if(r < p.S) vec.push_back({r + 1, p.S});
      for(auto i : vec) group[idx[u]].insert(i);
    }
    else {
      cnt += 1;
      if(dep[u] > dep[v]) swap(u, v);
      int idxl = 1, idxr = dis + 1;
      while(dep[u] != dep[v]) {
        if(idx[v] != 0) return void(cout << "No\n");
        idx[v] = cnt;
        gidx[v] = idxr--;
        v = fa[v][0];
      }
      while(u != v) {
        if(idx[v] != 0) return void(cout << "No\n");
        if(idx[u] != 0) return void(cout << "No\n");
        idx[u] = idx[v] = cnt;
        gidx[u] = idxl++;
        gidx[v] = idxr--;
        v = fa[v][0];
        u = fa[u][0];
      }
      assert(idxl == idxr && u == v);
      if(idx[u] != 0) return void(cout << "No\n");
      idx[u] = cnt;
      gidx[u] = idxl;
      group[cnt].insert({1, dis + 1});
    }
  }
  cout << "Yes\n";
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}

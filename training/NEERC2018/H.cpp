#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = (int)1e5 + 5;

int n, m, cnt, type[N * 2], used[N * 2], scc_id[N * 2], scc_type[N * 2], deg[N * 2];
vector<int> G[N * 2], rG[N * 2], sccG[N * 2], scc[N * 2];
vector<int> order;

void dfs(int u, int f) {
  used[u] = 1;
  for(auto v : G[u]) if(v != f) {
    if(!used[v]) dfs(v, u);
  }
  order.push_back(u);
}
void dfs2(int u, int f) {
  used[u] = 1;
  scc_id[u] = cnt;
  scc[cnt].push_back(u);
  for(auto v : rG[u]) if(v != f) {
    if(!used[v]) dfs2(v, u);
  }
}
int dfs3(int u) {
  used[u] = 1;
  for(auto v : sccG[u]) {
    if(used[v]) used[u] |= (scc_type[v] | used[v]);
    else used[u] |= scc_type[v] | dfs3(v);
  }
  return used[u];
}
inline int idx(int x) { return x > 0 ? x : -x + n; }

void init() {
  cin >> n >> m;
  string s; cin >> s;
  for(int i = 1 ; i <= n * 2 ; ++i) {
    G[i].clear();
    rG[i].clear();
  }
  for(int i = 1 ; i <= n ; ++i) type[i] = type[i + n] = (s[i - 1] == 'A' ? 2 : 1);
  for(int i = 0 ; i < m ; ++i) {
    int a, b; cin >> a >> b;
    G[idx(-a)].push_back(idx(b));
    G[idx(-b)].push_back(idx(a));
    rG[idx(a)].push_back(idx(-b));
    rG[idx(b)].push_back(idx(-a));

  }
}
bool solve() {
  fill(used, used + 1 + n * 2, 0);
  order.clear();
  for(int i = 1 ; i <= n * 2 ; ++i) if(!used[i]) dfs(i, 0);
  fill(used, used + 1 + n * 2, 0);
  reverse(order.begin(), order.end());
  cnt = 0;
  for(auto i : order) if(!used[i]) {
    cnt++;
    scc[cnt].clear();
    dfs2(i, 0);
  }
  // id(x_i) == id(~x_i)
  for(int i = 1 ; i <= n ; ++i) if(scc_id[i] == scc_id[i + n]) return false;
  // id(x_ex) == id(x_uni)
  fill(scc_type, scc_type + 1 + cnt, 0);
  for(int i = n ; i >= 1 ; --i) {
    scc_type[scc_id[i]] |= type[i];
    if(type[i] == 1 && scc_type[scc_id[i]] >= 2) return false;

    scc_type[scc_id[i + n]] |= type[i + n];
    if(type[i + n] == 1 && scc_type[scc_id[i + n]] >= 2) return false;
  }
  
  // x_uni -> x_uni
  fill(deg, deg + 1 + n * 2, 0);
  for(int i = 1 ; i <= cnt ; ++i) sccG[i].clear();
  for(int i = 1 ; i <= n * 2 ; ++i) {
    for(auto j : G[i]) if(scc_id[i] != scc_id[j]) {
      sccG[scc_id[i]].push_back(scc_id[j]);
      deg[scc_id[j]]++;
    }
  }
  order.clear();
  for(int i = 1 ; i <= cnt ; ++i) order.push_back(i);
  sort(order.begin(), order.end(), [&](auto a, auto b) { return deg[a] > deg[b]; });
  fill(used, used + 1 + cnt, 0);
  for(auto i : order) {
    dfs3(i);
    if((used[i] & scc_type[i]) >= 2) return false;
  }
  // x_uni in same scc
  for(int i = 1 ; i <= cnt ; ++i) {
    int cc = 0;
    for(auto j : scc[i]) if(type[j] == 2) cc++;
    if(cc > 1) return false;
  }

  return true;
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int t; cin >> t;
  while(t--) {
    init();
    cout << (solve() ? "TRUE" : "FALSE") << '\n';
  }
}

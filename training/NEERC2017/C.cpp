#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int N = (int)1e5 + 5;

int n, m, vis[N], used[N];
vector<int> G[N];
vector<pii> edges;

int get_next(pii e, int u, int r) {
  if(r) return e.S != u ? 0 : e.F;
  else return e.F != u ? 0 : e.S;
}
void dfs(int u, int rev) {
  vis[u] = 1;
  for(auto i : G[u]) {
    int v = get_next(edges[i], u, rev);
    if(v && !vis[v]) dfs(v, rev), used[i] = 1;
  }
}

void init() {
  cin >> n >> m;
  for(int i = 0 ; i <= n ; ++i) G[i].clear();
  edges.clear();
  for(int i = 0 ; i < m ; ++i) {
    int a, b; cin >> a >> b;
    G[a].push_back((int)edges.size());
    G[b].push_back((int)edges.size());
    edges.push_back({a, b});
  }
}
void solve() {
  fill(used, used + m, 0);
  fill(vis + 1, vis + n + 1, 0);
  dfs(1, 0);
  fill(vis + 1, vis + n + 1, 0);
  dfs(1, 1);
  int k = m - n * 2;
  for(int i = 0 ; i < m ; ++i) if(!used[i] && k > 0) {
    cout << edges[i].F << ' ' << edges[i].S << '\n';
    k--;
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int t; cin >> t;
  while(t--) {
    init();
    solve();
  }
}


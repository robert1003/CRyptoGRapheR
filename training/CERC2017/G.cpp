#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
using ll = long long;
using ld = long double;

const int N = (int)3e5 + 5;

int n, m, vis[N];
vector<int> G[N];
ld d[N];
pair<ld, int> f[N];

inline int deg(int x){ return (int)G[x].size(); }

void init() {
  cin >> n >> m;
  for(int i = 0 ; i < m ; ++i) {
    int a, b; cin >> a >> b;
    G[a].push_back(b);
    G[b].push_back(a);
  }
}
void solve() {
  fill(vis, vis + n + 1, 0);
  priority_queue<pair<ld, int>, vector<pair<ld, int> >, greater<pair<ld, int> > > pq;
  for(int i = 1 ; i < n ; ++i) f[i] = {deg(i), 0};
  f[n] = {0, 1};
  pq.push({f[n].F / f[n].S, n});
  while(!pq.empty()) {
    auto p = pq.top(); pq.pop();
    if(vis[p.S]) continue;
    int u = p.S;
    vis[u] = 1; d[u] = f[u].F / f[u].S;
    for(auto v : G[u]) if(!vis[v]) {
      f[v].F += d[u];
      f[v].S += 1;
      pq.push({f[v].F / f[v].S, v});
    }
  }
  cout << fixed << setprecision(10) << d[1] << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}

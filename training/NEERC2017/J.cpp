#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = (int)3e3 + 5;
const ll inf = (ll)1e15;

int n, m, k;
vector<int> G[N];
vector<array<int, 3> > edges, edges2;
ll d[N];
bool vis[N];

pair<int, int> get_next(int u, int e) {
  return {(u == edges2[e][0] ? edges2[e][1] : edges2[e][0]), edges2[e][2]};
}
ll dijkstra() {
  priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > pq;
  fill(vis, vis + n + 1, false);
  fill(d, d + n + 1, inf);
  d[1] = 0; 
  pq.push({d[1], 1});
  while(!pq.empty()) {
    auto [dis, u] = pq.top(); pq.pop();
    if(vis[u]) continue;
    vis[u] = true;
    for(auto e : G[u]) {
      auto [v, w] = get_next(u, e);
      if(d[v] > dis + w) {
        d[v] = dis + w;
        pq.push({d[v], v});
      }
    }
  }
  return d[n];
}

void init() {
  cin >> n >> m >> k;
  for(int i = 0 ; i < m ; ++i) {
    int a, b, w; cin >> a >> b >> w;
    G[a].push_back((int)edges.size());
    G[b].push_back((int)edges.size());
    edges.push_back({a, b, w});
    edges2.push_back({a, b, w});
  }
}
void solve() {
  ll ans = dijkstra();
  for(int i = 0 ; i < m ; ++i) {
    int w = edges[i][2];
    for(int j = 0 ; j < m ; ++j) {
      edges2[j][2] = max(0, edges[j][2] - w);
    }
    ans = min(ans, dijkstra() + (ll)k * w);
  }
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}

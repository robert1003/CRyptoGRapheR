#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = (int)1e6 + 6;

int n, sz[N];
vector<int> G[N];

int dfs(int u, int f) {
  sz[u] = 0;
  for(auto v : G[u]) if(v != f) {
    sz[u] += dfs(v, u);
  }
  return ++sz[u];
}
bool ok(int k) {
  if(k == n) return false;
  int cnt = 0;
  for(int i = 2 ; i <= n ; ++i) if(sz[i] % k == 0) cnt++;
  return cnt >= n / k - 1;
}

void init() {
  cin >> n;
  for(int i = 1 ; i < n ; ++i) {
    int u, v; cin >> u >> v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
}
void solve() {
  dfs(1, 0);
  vector<int> ans;
  for(int i = 1 ; (ll)i * i <= (ll)n ; ++i) if(n % i == 0) {
    int p = i, q = n / i;
    if(ok(p)) ans.push_back(n / p - 1);
    if(p != q && ok(q)) ans.push_back(n / q - 1);
  }
  sort(ans.begin(), ans.end());
  for(auto i : ans) cout << i << ' ';
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}

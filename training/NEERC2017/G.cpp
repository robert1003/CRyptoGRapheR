#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
using ll = long long;
using oset = tree<pair<ll, ll>, null_type, less<pair<ll, ll> >, rb_tree_tag, tree_order_statistics_node_update>;

const int N = (int)3e4 + 5;
const ll inf = (ll)1e15;

ll n, r, k, base, a[N], b[N], c[N];
ll pb[N], f1[N], f2[N], g1[N], g2[N];

inline ll f(int x) {
  x = x - r + 1;
  return f1[x - 1] + f2[x + r - 1] - f2[x - 1];
}
inline ll g(int x) {
  x = x - r + 1;
  return g1[x - 1] + g2[x + r - 1] - g2[x - 1];
}
ll count(ll x) {
  ll cnt = 0;
  oset s; s.insert({pb[r] - pb[0], r});
  for(int i = r * 2 ; i <= n ; ++i) {
    pair<ll, ll> key = {x - (pb[i] - pb[i - r]), inf};
    cnt += s.order_of_key(key);
    s.insert({pb[i - r + 1] - pb[i - r * 2 + 1], i + r + 1});
  }
  s.clear();
  for(int i = r ; i < min(r * 2, n + 1) ; ++i) {
    pair<ll, ll> key = {x - f(i), inf};
    cnt += s.order_of_key(key);
    s.insert({g(i), i});
  }
  for(int i = r * 2 ; i <= n ; ++i) {
    s.erase({g(i - r), i - r});
    pair<ll, ll> key = {x - f(i), inf};
    cnt += s.order_of_key(key);
    s.insert({g(i), i});
  }
  return cnt;
}

void init() {
  cin >> n >> r >> k;
  for(int i = 1 ; i <= n ; ++i) cin >> a[i], base += a[i];
  for(int i = 1 ; i <= n ; ++i) cin >> b[i], b[i] -= a[i];
  for(int i = 1 ; i <= n ; ++i) cin >> c[i], c[i] -= a[i];
  for(int i = 1 ; i <= n ; ++i) {
    pb[i] = pb[i - 1] + b[i];
    f1[i] = f1[i - 1] + b[i] * 2 - c[i];
    f2[i] = f2[i - 1] + b[i];
    g1[i] = g1[i - 1] + c[i] - b[i] * 2;
    g2[i] = g2[i - 1] + c[i] - b[i];
  }
}
void solve() {
  ll l = 1, r = 3e10;
  while(l < r) {
    ll mid = l + (r - l) / 2, cnt = count(mid);
    if(cnt < k) l = mid + 1;
    else r = mid;
  }
  cout << l + base << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}

#include <bits/stdc++.h>
#define lson o * 2 + 1
#define rson o * 2 + 2
#define mid (l + r) >> 1
using namespace std;
using ll = long long;

const int N = (int)1e6 + 1;

namespace segtree {
  ll a[N * 4], tag[N * 4];
  void pull(int o=0) {
    a[o] = max(a[lson] + tag[lson], a[rson] + tag[rson]);
  }
  void update(int l, int r, int ql, int qr, ll v, int o=0) {
    if(ql <= l && r <= qr) return void(tag[o] += v);
    if(qr <= mid) update(l, mid, ql, qr, v, lson);
    else if(mid <= ql) update(mid, r, ql, qr, v, rson);
    else {
      update(l, mid, ql, mid, v, lson);
      update(mid, r, mid, qr, v, rson);
    }
    pull(o);
  }
  ll query(int l, int r, int ql, int qr, int o=0) {
    if(ql <= l && r <= qr) return a[o] + tag[o];
    if(qr <= mid) return query(l, mid, ql, qr, lson) + tag[o];
    else if(mid <= ql) return query(mid, r, ql, qr, rson) + tag[o];
    else return max(query(l, mid, ql, mid, lson), query(mid, r, mid, qr, rson)) + tag[o];
  }
}
namespace BIT {
  ll b[N];
  inline int lowbit(int x) { return x & (-x); }
  void update(int x, int v, int n) {
    for(int i = x ; i <= n ; i += lowbit(i)) b[i] += v;
  }
  ll query(int x, int n) {
    ll ans = 0;
    for(int i = x ; i > 0 ; i -= lowbit(i)) ans += b[i];
    return ans;
  }
}

void solve() {
  int q; cin >> q;
  vector<pair<int, int> > event;
  set<pair<int, int> > knight;
  while(q--) {
    char op; cin >> op;
    if(op == '+') {
      int t, d; cin >> t >> d;
      segtree::update(1, N, t, t + 1, t);
      segtree::update(1, N, 1, t + 1, d);
      BIT::update(t, d, N - 1);
      knight.insert({t, (int)event.size()});
      event.push_back({t, d});
    }
    else if(op == '-') {
      int i; cin >> i; i--;
      auto [t, d] = event[i];
      segtree::update(1, N, t, t + 1, -t);
      segtree::update(1, N, 1, t + 1, -d);
      BIT::update(t, -d, N - 1);
      event.push_back({-t, -d});
      knight.erase({t, i});
    }
    else {
      int t; cin >> t;
      auto it = knight.upper_bound({t, N});
      if(it == knight.begin()) cout << "0\n";
      else {
        it = prev(it);
        //cerr << "found: " << it->first << ' ' << it->second << '\n';
        //cerr << segtree::query(1, N, 1, it->first + 1)  << ' ' << (BIT::query(N - 1, N - 1) - BIT::query(it->first, N - 1)) << '\n';
        cout << max(0LL, segtree::query(1, N, 1, it->first + 1) - (BIT::query(N - 1, N - 1) - BIT::query(it->first, N - 1)) - t) << '\n';
      }
      event.push_back({-1, -1});
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  solve();
}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = (int)1e6 + 5;
const int inf = (int)1e9;

namespace segtree {
  set<int> idx[N * 4];

  void insert(int l, int r, int ql, int qr, int id, int o=0) {
    if(ql <= l && r <= qr) return void(idx[o].insert(id));
    int mid = (l + r) >> 1, lson = o * 2 + 1, rson = o * 2 + 2;
    if(qr <= mid) insert(l, mid, ql, qr, id, lson);
    else if(mid <= ql) insert(mid, r, ql, qr, id, rson);
    else {
      insert(l, mid, ql, mid, id, lson);
      insert(mid, r, mid, qr, id, rson);
    }
  }
  void remove(int l, int r, int ql, int qr, int id, int o=0) {
    if(ql <= l && r <= qr) return void(idx[o].erase(id));
    int mid = (l + r) >> 1, lson = o * 2 + 1, rson = o * 2 + 2;
    if(qr <= mid) remove(l, mid, ql, qr, id, lson);
    else if(mid <= ql) remove(mid, r, ql, qr, id, rson);
    else {
      remove(l, mid, ql, mid, id, lson);
      remove(mid, r, mid, qr, id, rson);
    }
  }
  void query(int l, int r, int q, vector<int>& cand, int o=0) {
    for(auto i : idx[o]) cand.push_back(i);
    if(l + 1 == r) return;
    int mid = (l + r) >> 1, lson = o * 2 + 1, rson = o * 2 + 2;
    if(q < mid) query(l, mid, q, cand, lson);
    else query(mid, r, q, cand, rson);
  }
};

int n;
vector<tuple<int, int, int> > v;
vector<int> uni;

inline int pos(int x) {
  return lower_bound(uni.begin(), uni.end(), x) - uni.begin() + 1;
}
inline bool in(tuple<int, int, int> t, ll x, ll y) {
  ll _, xx, yy; tie(_, xx, yy) = t;
  return (x - xx) * (x - xx) + (y - yy) * (y - yy) < yy * yy;
}

void init() {
  cin >> n;
  for(int i = 0 ; i < n ; ++i) {
    int t, x, y; cin >> t >> x >> y;
    v.push_back(tie(t, x, y));
    if(t == 1) {
      uni.push_back(x + y);
      uni.push_back(x - y);
    }
    else uni.push_back(x);
  }
  sort(uni.begin(), uni.end());
  uni.resize(unique(uni.begin(), uni.end()) - uni.begin());
}
void solve() {
  int m = (int)uni.size();
  for(int i = 0 ; i < n ; ++i) {
    int op, x, y; tie(op, x, y) = v[i];
    if(op == 1) {
      segtree::insert(1, m + 1, pos(x - y), pos(x + y), i);
    }
    else {
      vector<int> cand;
      segtree::query(1, m + 1, pos(x), cand);
      int ans = -1;
      for(auto j : cand) {
        if(in(v[j], x, y)) {
          int _, xx, yy; tie(_, xx, yy) = v[j];
          ans = j + 1;
          segtree::remove(1, m + 1, pos(xx - yy), pos(xx + yy), j);
          break;
        }
      }
      cout << ans << '\n';
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}

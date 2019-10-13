#include <bits/stdc++.h>
using namespace std;

struct DisjointSet {
  static const int maxn = (int)5e5 + 5;
  int n, fa[maxn], sz[maxn];
  vector<pair<int*, int>> h;
  vector<int> sp;
  
  void init(int _n) {
    n = _n;
    for(int i = 0 ; i < n ; ++i) {
      fa[i] = i;
      sz[i] = 1;
    }
    sp.clear(); h.clear();
  }
  void assign(int *k, int v) {
    h.push_back({k, *k});
    *k = v;
  }
  void save() { sp.push_back((int)h.size()); }
  void undo() {
    assert(!sp.empty());
    int last = sp.back(), cnt = 0; sp.pop_back();
    while(h.size() > last) {
      auto x = h.back(); h.pop_back();
      *x.first = x.second;
      cnt++;
    }
    n += cnt/2;
  }
  int f(int x) {
    while(fa[x] != x) x = fa[x];
    return x;
  }
  bool merge(int x, int y) {
    x = f(x); y = f(y);
    if(x == y) return 0;
    if(sz[x] < sz[y]) swap(x, y);
    assign(&sz[x], sz[x]+sz[y]);
    assign(&fa[y], x);
    n--;
    return 1;
  }
} djs;

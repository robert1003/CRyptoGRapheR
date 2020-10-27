#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;

const int N = (int)3e5 + 5;

struct Event {
  int y, type, idx;

  bool operator<(const Event& rhs) const {
    return tie(rhs.y, type) < tie(y, rhs.type);
  }
};

int n, m, fx[N], fy[N], bx[N], by[N], ans[N], pa[N], fa[N], cnt[N];

int find(int x) {
  return x == fa[x] ? x : fa[x] = find(fa[x]);
}
void merge(int x, int y) {
  x = find(x), y = find(y);
  if(x == y) return;
  fa[x] = y;
  cnt[y] += cnt[x];
  cnt[x] = 0;
}

void init() {
  cin >> m;
  for(int i = 0 ; i < m ; ++i) cin >> bx[i] >> by[i];
  cin >> n;
  for(int i = 0 ; i < n ; ++i) cin >> fx[i] >> fy[i];
}
void solve() {
  vector<Event> events;
  for(int i = 0 ; i < n ; ++i) events.push_back({fy[i], 0, i}), pa[i] = i;
  for(int i = 0 ; i < m ; ++i) events.push_back({by[i], 1, i});
  sort(events.begin(), events.end());
  set<pair<int, int> > active; // x, idx
  for(auto [y, type, idx] : events) {
    if(type == 0) { // fence
      // add right neighbor as parent
      auto it = active.insert({fx[idx], idx}).F;
      if(next(it) != active.end()) pa[idx] = next(it)->S;
      // remove left active fences
      auto itt = it;
      while(itt != active.begin()) {
        if(prev(itt)->S < idx) break;
        itt--;
      }
      active.erase(itt, it);
    }
    else { // buffalo
      auto it = active.lower_bound({bx[idx], -1});
      if(it != active.end()) cnt[it->S]++;
    }
  }

  for(int i = 0 ; i < n ; ++i) fa[i] = i;
  for(int i = n - 1 ; i >= 0 ; --i) {
    ans[i] = cnt[i];
    merge(i, pa[i]);
  }
  for(int i = 0 ; i < n ; ++i) cout << ans[i] << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll v[3], w, h;

bool ok(ll p, ll q) {
  return (p <= w && q <= h) or (p <= h && q <= w);
}

void init() {
  cin >> v[0] >> v[1] >> v[2] >> w >> h;
  sort(v, v + 3);
}
void solve() {
  bool succ = false;
  do {
    if(ok(v[0] + v[2] * 2, v[1] * 2 + v[2] * 2)) succ = true;
    else if(ok(v[0] + v[2], v[0] + v[2] + v[1] * 3)) succ = true;
    else if(ok(v[0] * 2 + v[1] + v[2], v[0] + v[1] + v[2])) succ = true;
    if(succ) break;
  } while(next_permutation(v, v + 3));
  if(succ) cout << "Yes\n";
  else cout << "No\n";
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}

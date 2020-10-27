#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
 
int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
 
  int D; cin >> D;
  for(int kase = 1 ; kase <= D ; kase++) {
    ll N, S; cin >> N >> S;
    ll mx = -1e15;
    for(int i = 0 ; i < N ; ++i) {
      ll f, t; cin >> f >> t;
      mx = max(mx, f - max(t - S, 0LL));
    }
    cout << "Case #" << kase << ": " << mx << '\n';
  }
  
  return 0;
}

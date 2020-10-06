#pragma GCC optimize ("O3,unroll-loops,no-stack-protector")
#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
using ll = long long;
using ull = unsigned long long;

const int N = 64;
const int M = 21;

int n;
ull b[N], a[N], smq, sum[2][1 << M];

ull powmod(ull a, ull b, int m) {
  if(b == 0) return 1;
  ull ans = powmod(a, b / 2, m);
  ans = (ans * ans) << (64 - m) >> (64 - m);
  if(b & 1) ans = (ans * a) << (64 - m) >> (64 - m);
  return ans;
}

void init() {
  cin >> n;
  for(int i = 0 ; i < n ; ++i) cin >> b[i];
  cin >> smq;
}
void solve() {
  if(n <= 42) {
    int m[2] = {n / 2, (n + 1) / 2};
    vector<pair<ull, int> > v[2];
    for(int k = 0 ; k < 2 ; ++k) {
      for(int i = 0 ; i < m[k] ; ++i) sum[k][1 << i] = b[i + m[0] * k];
      for(int i = 0 ; i < m[k] ; ++i) {
        for(int j = 0 ; j < (1 << m[k]) ; ++j) {
          if(j & (1 << i)) sum[k][j] += sum[k][j ^ (1 << i)];
        }
      }
      for(int i = 0 ; i < (1 << m[k]) ; ++i) v[k].push_back({sum[k][i], i});
    }
    sort(v[0].begin(), v[0].end());
    sort(v[1].begin(), v[1].end());
    for(auto [val, idx] : v[0]) {
      ull target = smq - val;
      auto search = lower_bound(v[1].begin(), v[1].end(), make_pair(target, 0));
      if(search == v[1].end()) continue;
      if(val + search->F == smq) {
        string ans = "";
        for(int i = 0 ; i < m[0] ; ++i) ans.push_back(idx & (1 << i) ? '1' : '0');
        for(int i = 0 ; i < m[1] ; ++i) ans.push_back(search->S & (1 << i) ? '1' : '0');
        cout << ans << '\n';
        return;
      }
    }
    assert(0);
  }
  else {
    ull t = 1 << (64 - n + 2), z = __builtin_ctzll(b[0]);
    auto inv = [&](ull p, int q) {
      return powmod(p, (1ULL << (q - 1)) - 1, q);
    };
    for(ull a0 = 1 ; a0 <= t ; ++a0) if(__builtin_ctzll(a0) == (int)z) {
      ull aa = a0 >> z, bb = b[0] >> z, rr = (bb * inv(aa, 64 - z)) << z >> z;
      for(ull j = 0 ; j < (1ULL << z) ; ++j) {
        ull r = (j << (64 - z)) + rr, sum = 0, ir = inv(r, 64);
        bool ok = true;
        for(int k = 0 ; k < n ; ++k) {
          a[k] = b[k] * ir;
          if(a[k] <= sum) { ok = false; break; }
          sum += a[k];
        }
        if(ok) {
          ull s = smq * ir;
          string ans = "";
          for(int k = n - 1 ; k >= 0 ; --k) {
            if(s >= a[k]) {
              ans.push_back('1');
              s -= a[k];
            }
            else ans.push_back('0');
          }
          if(s == 0) {
            reverse(ans.begin(), ans.end());
            cout << ans << '\n';
            return;
          }
        }
      }
    }
    assert(0);
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 501 + 5;
const int K = 7;

int n, dp[2][N][N][K];
vector<string> x;

inline int mod(int a, int m) { return (a % m + m) % m; }

int get_target(string s) {
  s += s;
  string best = s;
  int idx = 0, same = 1;
  for(int i = 0 ; i < K ; ++i) {
    if(s[i] != s[0]) same = 0;
    string now = s.substr(i, K);
    if(now > best) best = now, idx = i;
  }
  return (same ? -1 : idx);
}
inline void upd(int& a, int b) {
  a = max(a, b);
}

void init() {
  cin >> n;
  for(int i = 0 ; i < n ; ++i) {
    string s; cin >> s; x.push_back(s);
  }
}
void solve() {
  // get idx (max rotation)
  vector<int> target;
  for(auto &s : x) {
    int res = get_target(s);
    if(res != -1) target.push_back(res);
  }
  // get cnt
  vector<int> cnt(K, 0);
  for(int i = 1 ; i < (int)target.size() ; ++i) {
    cnt[mod(target[i] - target[i - 1], K)]++;
  }
  cnt[mod(target[0], K)]++;
  cnt[mod(-target.back(), K)]++;
  // dp: get max groups
  int ans = cnt[0];
  for(int i = 1 ; i < K ; ++i) {
    int val = min(cnt[i], cnt[K - i]);
    ans += val; cnt[i] -= val; cnt[K - i] -= val;
  }
  vector<int> v(3), cc(3);
  for(int i = 1 ; i < K ; ++i) if(cnt[i]) {
    int idx = min(i, K - i) - 1;
    v[idx] = i, cc[idx] = cnt[i];
  }

  memset(dp, -1, sizeof(dp));
  dp[0][0][0][0] = 0;
  int cur = 0;
  for(int a = 0 ; a <= cc[0] ; ++a) {
    for(int b = 0 ; b <= cc[1] ; ++b) {
      for(int c = 0 ; c <= cc[2] ; ++c) {
        for(int k = 0 ; k < K ; ++k) {
          if(a > 0 && dp[cur ^ 1][b][c][mod(k - v[0], K)] >= 0) upd(dp[cur][b][c][k], dp[cur ^ 1][b][c][mod(k - v[0], K)] + (k == 0));
          if(b > 0 && dp[cur][b - 1][c][mod(k - v[1], K)] >= 0) upd(dp[cur][b][c][k], dp[cur][b - 1][c][mod(k - v[1], K)] + (k == 0));
          if(c > 0 && dp[cur][b][c - 1][mod(k - v[2], K)] >= 0) upd(dp[cur][b][c][k], dp[cur][b][c - 1][mod(k - v[2], K)] + (k == 0));
        }
      }
    }
    for(int b = 0 ; b <= cc[1] ; ++b) {
      for(int c = 0 ; c <= cc[2] ; ++c) {
        for(int k = 0 ; k < K ; ++k) {
          dp[cur ^ 1][b][c][k] = dp[cur][b][c][k];
        }
      }
    }
    cur ^= 1;
  }

  cout << (int)target.size() + 1 - ans - dp[cur][cc[1]][cc[2]][0] << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}

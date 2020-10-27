#include <bits/stdc++.h>
#define ll long long
#define ld long double
using namespace std;
 
const int N = (int)1e6 + 5;
 
string s;
ld dp[N], pre[2][N];
ll cnt[2][N], n;
 
void init() {
  cin >> s;
  n = (int)s.size();
  for(int i = 0 ; i < n ; ++i) s[i] = (s[i] == 'C' ? 0 : 1);
  reverse(s.begin(), s.end());
}
void solve() {
  dp[0] = 0;
  for(int i = 1 ; i <= n ; ++i) {
    int t = s[i - 1];
    cnt[t][i] = cnt[t][i - 1] + 1;
    cnt[t ^ 1][i] = cnt[t ^ 1][i - 1];
 
    dp[i] = (ld)pre[t^1][i] / i + cnt[t^1][i];
 
    pre[t][i + 1] = pre[t][i] + dp[i] - cnt[t][i];
    pre[t ^ 1][i + 1] = pre[t ^ 1][i] + dp[i] - cnt[t ^ 1][i];
 
  }
  cout << fixed << setprecision(9) << dp[n] << '\n';
}
 
int main() {
  freopen("foreign.in","r",stdin);
  freopen("foreign.out","w",stdout);
  ios_base::sync_with_stdio(0), cin.tie(0);
 
  init();
  solve();
  
  return 0;
}

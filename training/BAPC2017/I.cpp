#include<bits/stdc++.h>
#define ll long long

using namespace std;

int dp[101][101][2];

inline int calc(int p, int q, int f) {
  if((p&1) and (q&1))
    return f ? 1 : -1;
  return 0;
}

int solve(int p, int q, int f) {
  if(p <= 0 or q <= 0) return 0;
  if(dp[p][q][f] != -1e9) return dp[p][q][f];
  for(int i = 1; i <= q; ++i) {
    dp[p][q][f] = max(dp[p][q][f], calc(p, i, f) - solve(q-i, p, 1^f^(p&1)^(i&1)));
  }
  return dp[p][q][f];
}

int main(){
  ios::sync_with_stdio(0); cin.tie(0);
  int p, q;
  cin >> p >> q;
  for(auto &x1 : dp)
    for(auto &x2 : x1)
      for(auto &x3 : x2)
        x3 = -1e9;
  cout << solve(p, q, 1) << endl;
  return 0;
}


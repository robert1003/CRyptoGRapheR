#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

ll A[20004];
ll B[20004];

ll mod = 1e5 + 7;

typedef vector<ll> Poly;
ll linearRec(Poly&& S, Poly && tr, ll k) {
  int n = tr.size();
  auto combine = [&] (Poly& a, Poly &b) {
    Poly res(n*2 + 1);
    for(int i = 0; i < n+1; ++i)
      for(int j = 0; j < n+1; ++j)
        res[i+j] = (res[i+j] + a[i] * b[j]) % mod;
    for(int i = 2*n; i > n; --i)
      for(int j = 0; j < n; ++j)
        res[i-1-j] = (res[i-1-j] + res[i]*tr[j]) % mod;
    res.resize(n+1);
    return res;
  };
  Poly pol(n+1), e(pol);
  pol[0] = e[1] = 1;
  for(++k; k; k /= 2) {
    if(k % 2) pol = combine(pol, e);
    e = combine(e, e);
  }
  ll res = 0;
  for(int i = 0; i < n; ++i)
    res = (res + pol[i+1]*S[i])%mod;
  return res;
}

ll calc(ll a, ll b) {
  if(b == 0) return b;
  if(a <= b) return 1;
  switch(b) {
    case 0:
      return 0;
    case 1:
      return 1;
    case 2:
      return linearRec({1, 1}, {1, 1}, a-1);
    case 3:
      return linearRec({1, 1, 1}, {1, 1, 1}, a-1);
    case 4:
      return linearRec({1, 1, 1, 1}, {1, 1, 1, 1}, a-1);
    case 5:
      return linearRec({1, 1, 1, 1, 1}, {1, 1, 1, 1, 1}, a-1);
    case 6:
      return linearRec({1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1}, a-1);
    default:
      assert(0);
  }

}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int N, M;
  cin >> N >> M;
  assert(N >= 1 and N <= 20000 and M >= 1 and M <= 20000);
  A[1] += 1;
  B[1] += 1;
  while(M --> 0) {
    char c;
    int j, k, h;
    cin >> c >> j >> k >> h;
    assert(j >= 1 and j <= N);
    assert(k >= 1 and k <= N);
    assert(h >= 1 and h <= 1000000);
    if(j <= k) {
      (c == 'a' ? A[j] : B[j]) += h;
      (c == 'a' ? A[k+1] : B[k+1]) -= h;
    }
    else {
      (c == 'a' ? A[j] : B[j]) += h;
      //(c == 'a' ? A[N+1] : B[N+1]) -= h;
      (c == 'a' ? A[1] : B[1]) += h;
      (c == 'a' ? A[k+1] : B[k+1]) -= h;
    }

  }

  for(int i = 1; i <= N; ++i)
    A[i] += A[i-1], B[i] += B[i-1];

  for(int i = 1; i <= N; ++i)
    B[i] %= 7;

  for(int i = 1; i <= N; ++i)
    A[i] = calc(A[i], B[i]);
  long long ans = 0;
  for(int i = 1; i <= N; ++i)
    ans += A[i];
  cout << ans << '\n';
  
  return 0;
}


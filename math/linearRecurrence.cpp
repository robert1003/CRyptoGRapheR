// Usage: linearRec({0, 1}, {1, 1}, k) //k'th fib
typedef vector<ll> Poly;
ll linearRec(Poly&& S, Poly&& tr, ll k) {
  int n=tr.size();
  auto combine=[&](Poly& a, Poly& b) {
    Poly res(n*2+1);
    for(int i=0;i<=n;i++) for(int j=0;j<=n;j++)
      res[i+j]=(res[i+j]+a[i]*b[j])%mod;
    for(int i=2*n;i>n;--i) for(int j=0;j<n;j++)
      res[i-1-j]=(res[i-1-j]+res[i]*tr[j])%mod;
    res.resize(n+1);
    return res;
  }; // combine: a * b mod (x^n-tr)
  Poly pol(n+1), e(pol);
  pol[0]=e[1]=1;
  for (++k;k;k/=2) {
    if(k%2) pol=combine(pol,e);
    e=combine(e,e);
  }
  ll res=0;
  for(int i=0;i<n;i++) res=(res+pol[i+1]*S[i])%mod;
  return res;
}

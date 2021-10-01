struct PolyOp {
#define FOR(i, c) for (int i = 0; i < (c); ++i)
  NTT<P, root, MAXK, MAXN> ntt;
  static int nxt2k(int x) {
    int i = 1; for (; i < x; i <<= 1); return i;
  }
  void Mul(int n, ll a[], int m, ll b[], ll c[]) {
    static ll aa[MAXN], bb[MAXN];
    int N = nxt2k(n+m);
    copy(a, a+n, aa); fill(aa+n, aa+N, 0);
    copy(b, b+m, bb); fill(bb+m, bb+N, 0);
    ntt.tran(N, aa); ntt.tran(N, bb);
    FOR(i, N) c[i] = aa[i] * bb[i] % P;
    ntt.tran(N, c, 1);
  }
  void Inv(int n, ll a[], ll b[]) {
    // ab = aa^-1 = 1 mod x^(n/2)
    // (b - a^-1)^2 = 0 mod x^n
    // bb + a^-2 - 2 ba^-1 = 0
    // bba + a^-1 - 2b = 0
    // a^-1 = 2b - bba
    static ll tmp[MAXN];
    if (n == 1) {b[0] = ntt.inv(a[0], P); return;}
    Inv((n+1)/2, a, b);
    int N = nxt2k(n*2);
    copy(a, a+n, tmp);
    fill(tmp+n, tmp+N, 0);
    fill(b+n, b+N, 0);
    ntt.tran(N, tmp); ntt.tran(N, b);
    FOR(i, N) {
      ll t1 = (2 - b[i] * tmp[i]) % P;
      if (t1 < 0) t1 += P;
      b[i] = b[i] * t1 % P;
    }
    ntt.tran(N, b, 1);
    fill(b+n, b+N, 0);
  }
  void Div(int n, ll a[], int m, ll b[], ll d[], ll r[]) {
    // Ra = Rb * Rd mod x^(n-m+1)
    // Rd = Ra * Rb^-1 mod
    static ll aa[MAXN], bb[MAXN], ta[MAXN], tb[MAXN];
    if (n < m) {copy(a, a+n, r); fill(r+n, r+m, 0); return;}
    // d: n-1 - (m-1) = n-m (n-m+1 terms)
    copy(a, a+n, aa); copy(b, b+m, bb);
    reverse(aa, aa+n); reverse(bb, bb+m);
    Inv(n-m+1, bb, tb);
    Mul(n-m+1, ta, n-m+1, tb, d);
    fill(d+n-m+1, d+n, 0); reverse(d, d+n-m+1);
    // r: m-1 - 1 = m-2 (m-1 terms)
    Mul(m, b, n-m+1, d, ta);
    FOR(i, n) { r[i] = a[i] - ta[i]; if (r[i] < 0) r[i] += P; }
  }
  void dx(int n, ll a[], ll b[]) { for(int i=1;i<=n-1;i++) b[i-1] = i * a[i] % P; }
  void Sx(int n, ll a[], ll b[]) {
    b[0] = 0;
    FOR(i, n) b[i+1] = a[i] * ntt.inv(i+1,P) % P;
  }
  void Ln(int n, ll a[], ll b[]) {
    // Integral a' a^-1 dx
    static ll a1[MAXN], a2[MAXN], b1[MAXN];
    int N = nxt2k(n*2);
    dx(n, a, a1); Inv(n, a, a2);
    Mul(n-1, a1, n, a2, b1);
    Sx(n+n-1-1, b1, b);
    fill(b+n, b+N, 0);
  }
  void Exp(int n, ll a[], ll b[]) {
    // Newton method to solve g(a(x))=ln(b(x))-a(x)=0
    // b' = b - g(b(x)) / g'(b(x))
    // b' = b (1 - lnb + a)
    static ll lnb[MAXN], c[MAXN], tmp[MAXN];
    assert(a[0] == 0); // dont know exp(a[0]) mod P
    if (n == 1) {b[0] = 1; return;}
    Exp((n+1)/2, a, b);
    fill(b+(n+1)/2, b+n, 0);
    Ln(n, b, lnb);
    fill(c, c+n, 0); c[0] = 1;
    FOR(i, n) {
      c[i] += a[i] - lnb[i];
      if (c[i] < 0) c[i] += P;
      if (c[i] >= P) c[i] -= P;
    }
    Mul(n, b, n, c, tmp);
    copy(tmp, tmp+n, b);
  }
  bool Sqrt(int n, ll a[], ll b[]){
    // Square root of a : b * b = a ( mod x^n )
    // bb = a  mod x^(n/2)
    // ( bb - a )^2 = 0 mod x^n
    // ( bb + a )^2 = 4 bba
    // ( ( bb + a ) / 2b )^2 = a
    // sqrt(a) = b / 2 + a / 2b
    static ll c[MAXN];
    int ind=0,x,y,p=1;
    while(a[ind]==0) ind++;
    for(int i=0;i<n;i++) a[i]=a[i+ind];
    if((ind&1)||!solve(a[0],mod,x,y)) // discrete sqrt
      return 0;
    b[0]=min(x,y);
    while(p<n) p<<=1;
    for(int t=2;t<=p;t<<=1){
      Inv(t,b,c); Mul(t,a,t,c,c);
      for(int i=0;i<t;i++)
        b[i]=(b[i]+c[i])*inv(2)%mod;
    }
    if(ind){
      for(int i=p-1;i>=ind/2;i--) b[i]=b[i-ind/2];
      for(int i=0;i<ind/2;i++) b[i]=0;
      for(int i=p-1;i>=ind;i--) a[i]=a[i-ind];
      for(int i=0;i<ind;i++) a[i]=0;
    }
  }
} polyop;

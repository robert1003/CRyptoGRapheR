/* p=a*2^k+1
   p                     a      k      root
   998244353             119    23     3
   2013265921            15     27     31
   2061584302081         15     37     7
   2748779069441         5      39     3
   1945555039024054273	 27     56     5 */
template<ll P, ll root, int MAXN>
struct NTT{
  static ll bigmod(ll a, ll b) {
    ll res = 1;
    for (ll bs = a; b; b >>= 1, bs = (bs * bs) % P)
      if(b&1) res=(res*bs)%P;
    return res;
  }
  static ll inv(ll a, ll b) {
    if(a==1)return 1;
    return (((ll)(a-inv(b%a,a))*b+1)/a)%b;
  }
  ll omega[MAXN+1];
  NTT() {
    omega[0] = 1;
    ll r = bigmod(root, (P-1)/MAXN);
    for (int i=1; i<=MAXN; i++)
      omega[i] = (omega[i-1]*r)%P;
  }
  void tran(int n, ll a[], bool inv_ntt=false){//n=2^k
    int basic = MAXN / n , theta = basic;
    for (int m = n; m >= 2; m >>= 1) {
      int mh = m >> 1;
      for (int i = 0; i < mh; i++) {
        ll w = omega[i*theta%MAXN];
        for (int j = i; j < n; j += m) {
          int k = j + mh;
          ll x = a[j] - a[k];
          if (x < 0) x += P;
          a[j] += a[k];
          if (a[j] >= P) a[j] -= P;
          a[k] = (w * x) % P;
        }
      }
      theta = (theta * 2) % MAXN;
    }
    int i = 0;
    for (int j = 1; j < n - 1; j++) {
      for (int k = n >> 1; k > (i ^= k); k >>= 1);
      if (j < i) swap(a[i], a[j]);
    }
    if (inv_ntt) {
      ll ni = inv(n,P);
      reverse( a+1 , a+n );
      for (i = 0; i < n; i++)
        a[i] = (a[i] * ni) % P;
    }
  }
};
const ll P=2013265921,root=31;
const int MAXN=4194304; // MAXN=2^k
NTT<P, root, MAXN> ntt;

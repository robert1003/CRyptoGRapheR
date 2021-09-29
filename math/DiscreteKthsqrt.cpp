/*
 * Solve x for x^P = A mod Q
 * https://arxiv.org/pdf/1111.4877.pdf
 * in O((lgQ)^2 + Q^0.25 (lgQ)^3)
 * Idea:
 * (P, Q-1) = 1 -> P^-1 mod (Q-1) exists
 * x has solution iff A^((Q-1) / P) = 1 mod Q
 * PP | (Q-1) -> P < sqrt(Q), solve lgQ rounds of discrete log
 * else -> find a s.t. s | (Pa - 1) -> ans = A^a
 */
void gcd(ll a, ll b, ll &x, ll &y, ll &g){
  if (b == 0) {
    x = 1, y = 0, g = a;
    return;
  }
  ll tx, ty;
  gcd(b, a%b, tx, ty, g);
  x = ty;
  y = tx - ty * (a / b);
  return;
}
ll P, A, Q, g;
// x^P = A mod Q

const int X = 1e5;

ll base;
ll ae[X], aXe[X], iaXe[X];
unordered_map<ll, ll> ht;

void build(ll a) { // ord(a) = P < sqrt(Q)
  base = a;
  ht.clear();
  ae[0] = 1;
  ae[1] = a;
  aXe[0] = 1;
  aXe[1] = pw(a, X, Q);
  iaXe[0] = 1;
  iaXe[1] = pw(aXe[1], Q-2, Q);
  for(int i=2;i<=X-1;i++) {
    ae[i] = mul(ae[i-1], ae[1], Q);
    aXe[i] = mul(aXe[i-1], aXe[1], Q);
    iaXe[i] = mul(iaXe[i-1], iaXe[1], Q);
  }
  for(int i=0;i<X;i++) ht[ae[i]] = i;
}

ll dis_log(ll x) {
  for(int i=0;i<X;i++) {
    ll iaXi = iaXe[i];
    ll rst = mul(x, iaXi, Q);
    if (ht.count(rst)) {
      ll res = i*X + ht[rst];
      return res;
    }
  }
}

ll main2() {
  ll t = 0, s = Q-1;
  while (s % P == 0) {
    ++t;
    s /= P;
  }
  if (A == 0) return 0;

  if (t == 0) {
    // a^{P^-1 mod phi(Q)}
    ll x, y, _;
    gcd(P, Q-1, x, y, _);
    if (x < 0) {
      x = (x % (Q-1) + Q-1) % (Q-1);
    }
    ll ans = pw(A, x, Q);
    if (pw(ans, P, Q) != A) while(1);
    return ans;
  }

  // A is not P-residue
  if (pw(A, (Q-1) / P, Q) != 1) return -1;

  for (g = 2; g < Q; ++g) {
    if (pw(g, (Q-1) / P, Q) != 1)
      break;
  }
  ll alpha = 0;
  {
    ll y, _;
    gcd(P, s, alpha, y, _);
    if (alpha < 0) alpha = (alpha % (Q-1) + Q-1) % (Q-1);
  }

  if (t == 1) {
    ll ans = pw(A, alpha, Q);
    return ans;
  }

  ll a = pw(g, (Q-1) / P, Q);
  build(a);
  ll b = pw(A, add(mul(P%(Q-1), alpha, Q-1), Q-2, Q-1), Q);
  ll c = pw(g, s, Q);
  ll h = 1;

  ll e = (Q-1) / s / P; // r^{t-1}
  for(int i=1;i<=t-1;i++) {
    e /= P;
    ll d = pw(b, e, Q);
    ll j = 0;
    if (d != 1) {
      j = -dis_log(d);
      if (j < 0) j = (j % (Q-1) + Q-1) % (Q-1);
    }
    b = mul(b, pw(c, mul(P%(Q-1), j, Q-1), Q), Q);
    h = mul(h, pw(c, j, Q), Q);
    c = pw(c, P, Q);
  }

  ll ans = mul(pw(A, alpha, Q), h, Q);

  return ans;
}

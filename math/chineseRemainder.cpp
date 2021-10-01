ll solve(ll x1, ll m1, ll x2, ll m2) {
  ll g = __gcd(m1, m2);
  if((x2 - x1) % g) return -1;// no sol
  m1 /= g; m2 /= g;
  pair<ll,ll> p = gcd(m1, m2);
  ll lcm = m1 * m2 * g;
  ll res=p.first*(x2-x1)%lcm*m1%lcm+x1; // overflow m^3
  return (res % lcm + lcm) % lcm;
}

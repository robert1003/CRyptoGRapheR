pair<ll,ll> gcd(ll a, ll b){
	if(b == 0) return {1, 0};
  pair<ll,ll> q = gcd(b, a % b);
  return {q.second, q.first - q.second * (a / b)};
}

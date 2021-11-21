ll dlog(ll x,ll y,ll m){
  if(y==1||m==1) return 0;
  ll s=max((int)sqrt(m),1)+2,g=1;
  unordered_map<ll,ll> mp;
  for(ll i=0;i<s;i++,g=g*x%m){
    if(g==y) return i;
    mp[g*y%m]=i;
  }
  if(gcd(g,m)!=gcd(y,m)) return -1; // std::gcd
  for(ll i=1,h=g;i<s;i++,h=h*g%m){
    if(mp.count(h)) return i*s-mp[h];
  }
  return -1;
}

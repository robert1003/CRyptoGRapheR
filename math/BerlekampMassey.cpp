// find shortest linear recurrence relation O(n^2)
// example: BM({1,1,2,3,5,8,13,21})
// 2*len terms for uniqueness
inline vector<ll> BM(const vector<ll> &x) {
  vector<ll> ls, cur;
  int lf; ll ld;
  for(int i=0;i<x.size();++i) {
    ll t=0;
    for(int j=0;j<cur.size();++j)
      t=(t+x[i-j-1]*cur[j])%mod;
    if((t-x[i])%mod==0) continue;
    if(!cur.size()) {
      cur.resize(i+1);lf=i;ld=(t-x[i])%mod;continue;
    }
    ll k=-(x[i]-t)*inv(ld, mod)%mod;
    vector<ll> c(i-lf-1); c.push_back(k);
    for(auto j:ls) c.push_back(-j*k%mod);
    if(c.size()<cur.size()) c.resize(cur.size());
    for(int j=0;j<cur.size();++j)
      c[j]=(c[j]+cur[j])%mod;
    if(i-lf+(int)ls.size()>=(int)cur.size())
      ls=cur,lf=i,ld=(t-x[i])%mod;
    cur=move(c);
  }
  for(auto& xx:cur) xx=(xx%mod+mod)%mod;
  return cur;
}

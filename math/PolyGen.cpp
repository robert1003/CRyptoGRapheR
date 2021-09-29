struct PolyGen{
  /* for a nth-order polynomial f(x), *
   * given f(0), f(1), ..., f(n) *
   * express f(x) as sigma_i{c_i*C(x,i)} */
  int n;
  vector<ll> coef;
  // initialize and calculate f(x), vector _fx should
  // be filled with f(0) to f(n)
  PolyGen(int _n,vector<ll> _fx):n(_n),coef(_fx){
    for(int i=0;i<n;i++)
      for(int j=n;j>i;j--)
        coef[j]-=coef[j-1];
  }
  // evaluate f(x), runs in O(n)
  ll eval(int x){
    ll m=1, ret=0;
    for(int i=0;i<=n;i++){
      ret+=coef[i]*m;
      m=m*(x-i)/(i+1);
    }
    return ret;
  }
};

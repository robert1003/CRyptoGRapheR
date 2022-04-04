// does not work when n is prime
ll f(ll x,ll mod){ return add(mul(x,x,mod),1,mod); }
ll pollard_rho(ll n) {
	if(!(n&1)) return 2;
  while(true){
    ll y=2,x=rand()%(n-1)+1,res=1,tmp=1;
    for(int sz=2;res==1;sz*=2){
      for(int i=0,t=0;i<sz&&res<=1;i++,t++){
        x=f(x,n); tmp=mul(tmp,abs(x-y),n);
        if(!(t&31)||i+1==sz) res=__gcd(tmp,n),tmp=1;
      }
      y=x;
    }
    if(res!=0&&res!=n) return res;
  }
}

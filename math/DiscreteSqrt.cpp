void calcH(ll &t,ll &h,const ll p){
  ll tmp=p-1; for(t=0;(tmp&1)==0;tmp/=2) t++; h=tmp;
}
// solve equation x^2 mod p=a where p is a prime
bool dsqrt(ll a,ll p,ll &x,ll &y){
  a%=p; if(p==2){ x=y=a; return true; }
  ll p2=p/2,tmp=mypow(a,p2,p);
  if(tmp==p-1) return false;
  if((p+1)%4==0){
    x=mypow(a,(p+1)/4,p); y=p-x; return true;
  } else{
    ll t,h,b,pb=0; calcH(t,h,p);
    if(t>=2){
      do{ b=rand()%(p-2)+2; }while(mypow(b,p/2,p)!=p-1);
      pb=mypow(b,h,p);
    } 
    ll s=mypow(a,h/2,p);
    for(int step=2; step<=t; step++){
      ll ss=mul(mul(s,s,p),a,p);
      for(int i=0;i<t-step;i++) ss=mul(ss,ss,p);
      if(ss+1==p) s=mul(s,pb,p);
      pb=mul(pb,pb,p);
    } 
    x=mul(s,a,p); y=p-x;
  } 
  return true; 
}

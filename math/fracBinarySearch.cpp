//find smallest p/q in [0,1] s.t. f(p/q)=1&&p,q<=N
struct Frac{ll p,q;};
Frac fracBS(function<bool(Frac)> f,ll N) {
  bool dir=1,A=1,B=1;
  Frac lo{0,1},hi{1,1}; // set hi to 1/0 to search (0,N]
  if(f(lo)) return lo;
  assert(f(hi));
  while(A or B){
    ll adv=0,step=1; // move hi if dir, else lo
    for(int si=0;step;(step*=2)>>=si){
      adv+=step; Frac m{lo.p*adv+hi.p,lo.q*adv+hi.q};
      if(abs(m.p)>N or m.q>N or dir==!f(m))
        adv-=step,si=2;
    }
    hi.p+=lo.p*adv; hi.q+=lo.q*adv;
    dir=!dir; swap(lo,hi); A=B; B=!!adv;
  }
  return dir?hi:lo;
}

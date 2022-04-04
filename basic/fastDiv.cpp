struct FastDiv{
	ull b,m;
	FastDiv(ull _b):b(_b),m(-1ULL/_b){}
  pair<ull,ull> div(ull a){ // (a/b,a%b)
    ull q=((__uint128_t(m)*a)>>64),r=a-q*b;
    return r>=b?make_pair(q+1,r-b):make_pair(q,r);
  }
};

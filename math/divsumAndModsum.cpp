ull sumsq(ull n){ return n/2*((n-1)|1); }
// sum i=0~n-1 floor((ki+c)/m)
ull divsum(ull n,ull k,ull c,ull m){
  ull res=k/m*sumsq(n)+c/m*n; k%=m; c%=m;
  if(!k) return res;
  ull n2=(n*k+c)/m;
  return res+(n-1)*n2-divsum(n2,m,m-1-c,k);
}
// sum i=0~n-1 (ki+c)%m
ll modsum(ull n, ll k, ll c, ll m){
  c=(c%m+m)%m; k=(k%m+m)%m;
  return n*c+k*sumsq(n)-m*divsum(n,k,c,m);
}

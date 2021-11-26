//return {sum{i=0~n}x, sum{i=0~n}ix, sum{i=0~n}x^2}
//x=floor((ai+b)/c);sum(ai+b)%c=(an+2b)*(n+1)/2-c*get<0>
ll sum(ll n){ return n*(n+1)/2; }
tuple<ll,ll,ll> calc(ll a, ll b, ll c, ll n){
  ll A=a/c,B=b/c,m=(a*n+b)/c,f,g,h,nf,ng,nh;
  if(a==0) return {B*(n+1),B*sum(n),B*B*(n+1)};
  if(a>=c or b>=c) {
    f=A*sum(n)+B*(n+1),g=A*sum(n)*(2*n+1)/3+B*sum(n);
    h=A*A*sum(n)*(2*n+1)/3+B*B*(n+1)+A*B*n*(n+1);
    tie(nf,ng,nh)=calc(a%c,b%c,c,n);
    return {f+nf,g+ng,h+nh+2*A*ng+2*B*nf};
  }
  tie(nf,ng,nh)=calc(c,c-b-1,a,m-1);
  return {n*m-nf,(n*(n+1)*m-nf-nh)/2,n*m*m-2*ng-nf};
} // beware overflow: {O(CN^2),O(CN^3),O(C^2N^3)}

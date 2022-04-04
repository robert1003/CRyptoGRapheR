/* 12721, 13331, 14341, 75577, 123457, 222557, 556679
* 999983, 1097774749, 1076767633, 100102021, 999997771
* 1001010013, 1000512343, 987654361, 999991231
* 999888733, 98789101, 987777733, 999991921, 1010101333
* 1010102101, 1000000000039, 1000000000000037
* 2305843009213693951, 4611686018427387847
* 9223372036854775783, 18446744073709551557 */
int mu[N],p_tbl[N]; // mobius, min prime factor
vector<int> primes;
void sieve() { // calculate multiplicative function f
  mu[1]=p_tbl[1]=1;
  for(int i=2;i<N;i++){
    if(!p_tbl[i]){
      p_tbl[i]=i; primes.push_back(i);
      mu[i]=-1; // f(i)=... where i is prime
    }
    for(int p:primes){
      int x=i*p;
      if(x>=N) break;
      p_tbl[x]=p; mu[x]=-mu[i];
      if(i%p==0){ // f(x)=f(i)/f(p^(k-1))*f(p^k)
        mu[x]=0; break;
      } // else f(x)=f(i)*f(p) where gcd(i,p)=1
} } }
vector<int> factor(int x){
  vector<int> fac{ 1 };
  while(x > 1){
    int fn=fac.size(),p=p_tbl[x],pos=0;
    while(x%p==0){
      x/=p;
      for(int i=0;i<fn;i++) fac.push_back(fac[pos++]*p);
    }
  }
  return fac;
}

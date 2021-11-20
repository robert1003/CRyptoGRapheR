// n < 4,759,123,141        3 :  2, 7, 61
// n < 1,122,004,669,633    4 :  2, 13, 23, 1662803
// n < 3,474,749,660,383          6 :  pirmes <= 13
// n < 2^64                       7 :
// 2, 325, 9375, 28178, 450775, 9780504, 1795265022
bool witness(ll a,ll n,ll u,int t){
	if(!(a%=n)) return 0;
	ll x=mypow(a,u,n);
	for(int i=0;i<t;i++) {
		ll nx=mul(x,x,n);
		if(nx==1&&x!=1&&x!=n-1) return 1;
		x=nx;
	}
	return x!=1;
}
bool miller_rabin(ll n,int s=100) {
	// iterate s times of witness on n
	// return 1 if prime, 0 otherwise
	if(n<2) return 0;
	if(!(n&1)) return n == 2;
	ll u=n-1; int t=0;
	while(!(u&1)) u>>=1, t++;
	while(s--){
		ll a=randll()%(n-1)+1;
		if(witness(a,n,u,t)) return 0;
	}
	return 1;
}

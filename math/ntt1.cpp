/* p=a*2^k+1
   p                     a      k      root
   998244353             119    23     3
   2013265921            15     27     31
   2061584302081         15     37     7
   2748779069441         5      39     3
   1945555039024054273	 27     56     5 */
template<ll P,ll root,int MAXK,int MAXN>
struct NTT{
	static ll powi(ll a,ll b){
		ll ret=1;
		for(;b;b>>=1,a=mul(a, a, P)){
			if(b&1)	ret=mul(ret, a, P);
		}
		return ret;
	}
	static ll inv(ll a,ll b){
		if(a==1) return 1;
		return (((__int128)(a-inv(b%a,a))*b+1)/a)%b;
	}
	ll omega[MAXK+1],inv_omega[MAXK+1];
	NTT(){
		omega[MAXK]=powi(root,(P-1)>>MAXK);
		for(int i=MAXK-1;i>=0;i--)
			omega[i]=mul(omega[i+1], omega[i+1], P);
		for(int i=0;i<=MAXK;i++)
			inv_omega[i]=inv(omega[i],P);
	}
	void tran(int n,ll a[],bool inv_ntt=false){//n=2^i
		for(int i=1,j=0;i<n;i++){
			for(int k=n>>1;!((j^=k)&k);k>>=1);
			if(i<j) swap(a[i],a[j]);
		}
		ll *G=(inv_ntt?inv_omega:omega);
		for(int k=2,t=1;k<=n;k<<=1){
			int k2=k>>1;ll dw=G[t++];
			for(int j=0;j<n;j+=k){
				ll w=1;
				for(int i=j;i<j+k2;i++){
					ll x=a[i],y=mul(a[i+k2], w, P);
					a[i]=x+y; if(a[i]>=P) a[i]-=P;
					a[i+k2]=x-y; if(a[i+k2]<0) a[i+k2]+=P;
					w=mul(w, dw, P);
				}
			}
		}
		if(inv_ntt){
			ll inv_n=inv(n,P);
			for(int i=0;i<n;i++) a[i]=mul(a[i], inv_n, P);
		}
	}
};
const LL P=2013265921,root=31;
const int MAXN=4194304,MAXK=22;//MAXN=2^i
NTT<P,root,MAXK,MAXN> ntt;

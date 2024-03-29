const int MXN=1048576; // (must be 2^k)
// before any usage,run pre_fft() first
typedef long double ld;
typedef complex<ld> cplx;
const ld PI=acosl(-1); const cplx I(0,1);
cplx omega[MXN+1];
void pre_fft(){
  for(int i=0;i<=MXN;i++)
    omega[i]=exp(i*2*PI/MXN*I);
}
// n must be 2^k
void fft(int n,cplx a[],bool inv=false){
  int basic=MXN/n,theta=basic;
  for(int m=n;m>=2;m>>=1) {
    int mh=m>>1;
    for(int i=0;i<mh;i++) {
      cplx w=omega[inv?MXN-(i*theta%MXN):i*theta%MXN];
      for(int j=i;j<n;j+=m) {
        int k=j+mh; cplx x=a[j]-a[k];
        a[j]+=a[k]; a[k]=w*x;
      }
    }
    theta=(theta*2)%MXN;
  }
  int i=0;
  for(int j=1;j<n-1;j++) {
    for(int k=n>>1;k>(i^=k);k>>=1);
    if(j<i) swap(a[i],a[j]);
  }
  if(inv) for(i=0;i<n;i++) a[i]/=n;
} // c=fft(cplx(a+b,a-b)); Re(ifft(c*c))/4+0.5;

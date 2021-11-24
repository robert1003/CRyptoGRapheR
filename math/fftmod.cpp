void fftmod(ll a[],int n,ll b[],int m,ll c[],ll mod){
	int B=32-__builtin_clz(n+m-1),N=1<<B,cut=sqrt(mod);
	vector<cplx> L(N),R(N),outs(N),outl(N);
	for(int i=0;i<n;i++) L[i]=cplx(a[i]/cut,a[i]%cut);
	for(int i=0;i<m;i++) R[i]=cplx(b[i]/cut,b[i]%cut);
	fft(N,L.data()); fft(N,R.data());
	for(int i=0;i<N;i++){
		int j=-i&(N-1);
		outl[j]=(L[i]+conj(L[j]))*R[i]/(2.0L*N);
		outs[j]=(L[i]-conj(L[j]))*R[i]/(2.0L*N)/1il;
	}
	fft(N,outl.data()); fft(N,outs.data());
	for(int i=0;i<n+m-1;i++){
		ll av=real(outl[i])+.5,cv=imag(outs[i])+.5;
		ll bv=(ll)(imag(outl[i])+.5)+(ll)(real(outs[i])+.5);
	  c[i]=((av%mod*cut+bv)%mod*cut+cv)%mod;
	}
} // NlogN*mod < 8.6e14 (maybe >=1e16 in practice)

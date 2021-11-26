ll PrimeCount(ll n){
  if(n<=1) return 0;
  const int v=sqrt(n); vector<int> smalls(v+1);
  for(int i=2;i<=v;++i) smalls[i]=(i+1)/2;
  int s=(v+1)/2,pc=0; vector<int> roughs(s);
  for(int i=0;i<s;++i) roughs[i]=2*i+1;
  vector<ll> larges(s); vector<bool> skip(v+1);
  for(int i=0;i<s;++i) larges[i]=(n/(2*i+1)+1)/2;
  for(int p=3;p<=v;++p){
    if(smalls[p]>smalls[p-1]){
      int q=p*p,ns=0; pc++;
      if(1LL*q*q>n) break;
      skip[p]=true;
      for(int i=q;i<=v;i+=2*p) skip[i]=true;
      for(int k=0;k<s;++k){
        int i=roughs[k]; ll d=1LL*i*p;
        if(skip[i]) continue;
        larges[ns]=larges[k]-(d<=v?larges[smalls[d]-pc]:smalls[n/d])+pc;
        roughs[ns++]=i;
      }
      s=ns;
      for(int j=v/p;j>=p;--j){
        int c=smalls[j]-pc;
        for(int i=j*p,e=min(i+p,v+1);i<e;++i) smalls[i]-=c;
  } } }
  for(int k=1;k<s;++k){
    const ll m=n/roughs[k]; ll ss=larges[k]-(pc+k-1);
    for(int l=1;l<k;++l){
      int p=roughs[l];
      if(1LL*p*p>m) break;
      ss-=smalls[m/p]-(pc+l-1);
    }
    larges[0]-=ss;
  }
  return larges[0];
}

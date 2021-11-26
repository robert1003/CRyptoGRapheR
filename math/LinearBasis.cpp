struct LinearBasis{ // n-bit linear basis
  int n,sz;vector<ull> B;//B:basis,sz:|B|,|span(B)|=2^sz
  void init(int _n){ B.clear(); B.resize(n=_n); sz=0; }
  bool insert(ull x){
    for(int i=n-1;i>=0;i--){
      if((x&(1ull<<i))==0) continue;
      if(!B[i]){ B[i]=x; sz++; return 1; }
      x^=B[i];
    } return 0;
  }
  bool contain(ull x){
    for(int i=n-1;i>=0;i--){
      if(x&(1ull<<i)){if(B[i]) x^=B[i]; else return 0;}
    } return 1;
  }
  pair<bool,ull> kth_min(ull k){ // k is 0-base
    if(k>=(1ull<<sz)) return {false,-1ull};
    ull ret=0; // note: 0 in span(non-empty B) iff sz==n
    for(int i=0;i<n;i++){
      if(B[i]){ if(k&1){ ret^=B[i]; } k>>=1; }
    }
    return {true,ret};
  }
  ull maximum(){
    ull ret=0;
    for(int i=n-1;i>=0;i--){
      if(B[i]&&(ret&(1ull<<i))==0) ret^=B[i];
    }
    return ret;
  }
}xorBasis;

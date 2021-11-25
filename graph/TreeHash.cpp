const ll P=880301,M=998244353; ll pp[N*2];
void init(){
  pp[0]=1; for(int i=1;i<N*2;i++) pp[i]=pp[i-1]*P%M;
}
pair<ll,int> hashT(const vector<int> *G,int x,int p=-1){
  vector<pair<ll,int>> tmp; ll ch='('; int len=1;
  for(int i:G[x]) if(i!=p) tmp.push_back(hashT(G,i,x));
  sort(tmp.begin(),tmp.end());
  for(const auto &i:tmp){
    ch=(ch+i.first*pp[len])%M; len+=i.second;
  }
  return {(ch+')'*pp[len])%M,len+1};
} // for unrooted tree: run with its centroid(s)

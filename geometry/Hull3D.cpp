struct PR{
  void ins(int x){ (a==-1?a:b)=x; }
  void rem(int x){ (a==x?a:b)=-1; }
  int cnt(){ return (a!=-1)+(b!=-1); }
  int a,b;
};
#define sz(x) (int)(x).size()
#define rep(i,s,t) for(int i=s;i<(t);i++)
struct F{ Pt q; int a,b,c; };
vector<F> hull3d(const vector<Pt>& A){
  assert(sz(A)>=4);
  vector<vector<PR>> E(sz(A),vector<PR>(sz(A),{-1,-1}));
#define E(x,y) E[f.x][f.y]
  vector<F> FS;
  auto mf=[&](int i,int j,int k,int l){
    Pt q=(A[j]-A[i])^((A[k]-A[i]));
    if(q*A[l]>q*A[i]) q=q*-1;
    F f{q,i,j,k};
    E(a,b).ins(k); E(a,c).ins(j); E(b,c).ins(i);
    FS.push_back(f);
  };
  rep(i,0,4) rep(j,i+1,4) rep(k,j+1,4)mf(i,j,k,6-i-j-k);
  rep(i,4,sz(A)){ rep(j,0,sz(FS)){ F f=FS[j];
      if(f.q*A[i]>f.q*A[f.a]){
        E(a,b).rem(f.c);E(a,c).rem(f.b);E(b,c).rem(f.a);
        swap(FS[j--],FS.back()); FS.pop_back();
      }
    }
    int nw=sz(FS);
    rep(j,0,nw){ F f=FS[j];
#define C(a,b,c) if(E(a,b).cnt()!=2) mf(f.a,f.b,i,f.c);
      C(a,b,c); C(a,c,b); C(b,c,a);
    }
  }
  for(F& it:FS) if(((A[it.b]-A[it.a])^(
    A[it.c]-A[it.a]))*(it.q)<=0) swap(it.c,it.b);
  return FS;
};

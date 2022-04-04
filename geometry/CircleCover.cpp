#define N 1021
struct CircleCover{            // overlap
  int C; Circle c[N]; bool g[N][N],over[N][N];
  // Area[i] : area covered by at least i circles
  ld Area[N];
  void init(int _C){ C=_C;}
  struct Teve {
    Pt p;ld ang;int add;
    Teve() {}
    Teve(Pt _a,ld _b,int _c):p(_a),ang(_b),add(_c){}
    bool operator<(const Teve &a) const
    { return ang<a.ang;}
  }eve[N*2];
  // strict: x=0,otherwise x=-1
  bool disjunct(Circle& a,Circle &b,int x)
  { return sign(norm(a.o-b.o)-a.r-b.r)>x; }
  bool contain(Circle& a,Circle &b,int x)
  { return sign(a.r-b.r-norm(a.o-b.o))>x; }
  bool contain(int i,int j){
    /* c[j] is non-strictly in c[i]. */
    return (sign(c[i].r-c[j].r)>0||(sign(c[i].r-c[j].r)==0&&i<j))&&contain(c[i],c[j],-1);
  }
  void solve(){
    for(int i=0;i<=C+1;i++) Area[i]=0;
    for(int i=0;i<C;i++) for(int j=0;j<C;j++)
        over[i][j]=contain(i,j);
    for(int i=0;i<C;i++) for(int j=0;j<C;j++) 
        g[i][j]=!(over[i][j]||over[j][i]||disjunct(c[i],c[j],-1));
    for(int i=0;i<C;i++){
      int E=0,cnt=1;
      for(int j=0;j<C;j++) if(j!=i&&over[j][i]) cnt++;
      for(int j=0;j<C;j++)
        if(i!=j && g[i][j]){
          vector<Pt> v=CCinter(c[i],c[j]);
          ld A=atan2(v[0].y-c[i].o.y,v[0].x-c[i].o.x);
          ld B=atan2(v[1].y-c[i].o.y,v[1].x-c[i].o.x);
          eve[E++]=Teve(v[1],B,1);
          eve[E++]=Teve(v[0],A,-1);
          if(B>A) cnt++;
        }
      if(E==0) Area[cnt]+=pi*c[i].r*c[i].r;
      else{
        sort(eve,eve+E); eve[E]=eve[0];
        for(int j=0;j<E;j++){
          cnt+=eve[j].add;
          Area[cnt]+=(eve[j].p^eve[j+1].p)*.5;
          ld theta=eve[j+1].ang-eve[j].ang;
          if(theta<0) theta+=2.*pi;
          Area[cnt]+=(theta-sin(theta))*c[i].r*c[i].r/2;
} } } } };

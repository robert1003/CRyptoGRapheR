#define N 1021
struct CircleCover{
  int C; Circle c[N];
  bool g[N][N], overlap[N][N];
  // Area[i] : area covered by at least i circles
  ld Area[N];
  void init(int _C){ C = _C; }
  bool CCinter(Circle& a, Circle& b, Pt& p1, Pt& p2){
    Pt o1 = a.o, o2 = b.o; ld r1 = a.r, r2 = b.r;
    if(norm(o1 - o2) > r1 + r2) return 0;
    if(norm(o1 - o2) < max(r1, r2) - min(r1, r2)) return 0;
    ld d2 = (o1 - o2) * (o1 - o2);
    ld d = sqrt(d2);
    if(d > r1 + r2) return 0;
    Pt u=(o1+o2)*0.5 + (o1-o2)*((r2*r2-r1*r1)/(2*d2));
    ld A=sqrt((r1+r2+d)*(r1-r2+d)*(r1+r2-d)*(-r1+r2+d));
    Pt v=Pt(o1.y-o2.y, -o1.x + o2.x) * A / (2*d2);
    p1 = u + v; p2 = u - v;
    return 1;
  }
  struct Teve {
    Pt p; ld ang; int add;
    Teve() {}
    Teve(Pt _a, ld _b, int _c):p(_a), ang(_b), add(_c){}
    bool operator<(const Teve &a)const
    {return ang < a.ang;}
  }eve[N * 2];
  // strict: x = 0, otherwise x = -1
  bool disjuct(Circle& a, Circle &b, int x)
  {return sign(norm(a.o - b.o) - a.r - b.r) > x;}
  bool contain(Circle& a, Circle &b, int x)
  {return sign(a.r - b.r - norm(a.o - b.o)) > x;}
  bool contain(int i, int j){
    /* c[j] is non-strictly in c[i]. */
    return (sign(c[i].r - c[j].r) > 0 ||
            (sign(c[i].r - c[j].r) == 0 && i < j)) && contain(c[i], c[j], -1);
  }
  void solve(){
    for(int i = 0; i <= C + 1; i++) Area[i] = 0;
    for(int i = 0; i < C; i++)
      for(int j = 0; j < C; j++)
        overlap[i][j] = contain(i, j);
    for(int i = 0; i < C; i++)
      for(int j = 0; j < C; j++) 
        g[i][j] = !(overlap[i][j] || overlap[j][i] ||
                    disjuct(c[i], c[j], -1));
    for(int i = 0; i < C; i++){
      int E = 0, cnt = 1;
      for(int j = 0; j < C; j++)
        if(j != i && overlap[j][i])
          cnt++;
      for(int j = 0; j < C; j++)
        if(i != j && g[i][j]){
          Pt aa, bb;
          CCinter(c[i], c[j], aa, bb);
          ld A=atan2(aa.y - c[i].o.y, aa.x - c[i].o.x);
          ld B=atan2(bb.y - c[i].o.y, bb.x - c[i].o.x);
          eve[E++] = Teve(bb, B, 1);
          eve[E++] = Teve(aa, A, -1);
          if(B > A) cnt++;
        }
      if(E == 0) Area[cnt] += pi * c[i].r * c[i].r;
      else{
        sort(eve , eve + E);
        eve[E] = eve[0];
        for(int j = 0; j < E; j++){
          cnt += eve[j].add; 
          Area[cnt] += (eve[j].p ^ eve[j + 1].p) * .5;
          ld theta = eve[j + 1].ang - eve[j].ang;
          if (theta < 0) theta += 2. * pi;
          Area[cnt] +=
            (theta - sin(theta)) * c[i].r*c[i].r * .5;
} } } } };

/* Delaunay Triangulation:
Given a sets of points on 2D plane, find a
triangulation such that no points will strictly
inside circumcircle of any triangle.

find: return a triangle contain given point
add_point: add a point into triangulation

A Triangle is in triangulation iff. its has_chd is 0.
Region of triangle u: iterate each u.edge[i].tri,
each points are u.p[(i+1)%3], u.p[(i+2)%3] 

Voronoi diagram: for each triangle in triangulation, 
the bisector of all its edges will split the region.
nearest point will belong to the triangle containing it
*/
typedef double T;     // T is integer: eps=0
const int N=100000+5; const T inf=1e9, eps=1e-8;
T sqr(T x) { return x*x; }
// return p4 is in circumcircle of tri(p1,p2,p3)
bool in_cc(const Pt& p1, const Pt& p2, const Pt& p3, const Pt& p4){
  T u11=p1.x-p4.x; T u21=p2.x-p4.x; T u31=p3.x-p4.x;
  T u12=p1.y-p4.y; T u22=p2.y-p4.y; T u32=p3.y-p4.y;
  T u13=sqr(p1.x)-sqr(p4.x)+sqr(p1.y)-sqr(p4.y);
  T u23=sqr(p2.x)-sqr(p4.x)+sqr(p2.y)-sqr(p4.y);
  T u33=sqr(p3.x)-sqr(p4.x)+sqr(p3.y)-sqr(p4.y);
  T det=-u13*u22*u31+u12*u23*u31+u13*u21*u32
        -u11*u23*u32-u12*u21*u33+u11*u22*u33;
  return det > eps;
}
T side(const Pt& a, const Pt& b, const Pt& p)
{ return (b-a)^(p-a); }
typedef int SdRef; struct Tri; typedef Tri* TriRef;
struct Edge {
  TriRef tri; SdRef side;
  Edge():tri(0), side(0){}
  Edge(TriRef _tri, SdRef _side):tri(_tri), side(_side){}
};
struct Tri {
  Pt p[3]; Edge edge[3]; TriRef chd[3];
  Tri() {}
  Tri(const Pt& p0, const Pt& p1, const Pt& p2) {
    p[0]=p0; p[1]=p1; p[2]=p2; chd[0]=chd[1]=chd[2]=0;
  }
  bool has_chd() const { return chd[0]!=0; }
  int num_chd() const {
    return chd[0]==0?0:(chd[1]==0?1:chd[2]==0?2:3);
  }
  bool contains(Pt const& q) const {
    for(int i=0;i<3;i++)
      if(side(p[i],p[(i+1)%3],q)<-eps) return false;
    return true;
  }
} pool[N*10], *tris;
void edge(Edge a, Edge b){
  if(a.tri) a.tri->edge[a.side]=b;
  if(b.tri) b.tri->edge[b.side]=a;
}
struct Trig { // Triangulation
  void init(){ // Tri should at least contain all points
    the_root=new(tris++)Tri(Pt(-inf,-inf),Pt(+inf+inf,-inf),Pt(-inf,+inf+inf));
  }
  TriRef find(Pt p)const{ return find(the_root,p); }
  void add_point(const Pt& p)
  { add_point(find(the_root,p),p); }
  TriRef the_root;
  static TriRef find(TriRef root, const Pt& p) {
    while(true){
      if(!root->has_chd()) return root;
      for(int i=0;i<3&&root->chd[i];++i)
        if (root->chd[i]->contains(p)) {
          root=root->chd[i]; break;
        }
    }
    assert(false); // "point not found"
  }
  void add_point(TriRef root, Pt const& p) {
    TriRef tab,tbc,tca; // split it into three triangles
    tab=new(tris++) Tri(root->p[0],root->p[1],p);
    tbc=new(tris++) Tri(root->p[1],root->p[2],p);
    tca=new(tris++) Tri(root->p[2],root->p[0],p);
    edge(Edge(tab,0), Edge(tbc,1));
    edge(Edge(tbc,0), Edge(tca,1));
    edge(Edge(tca,0), Edge(tab,1));
    edge(Edge(tab,2), root->edge[2]);
    edge(Edge(tbc,2), root->edge[0]);
    edge(Edge(tca,2), root->edge[1]);
    root->chd[0]=tab;root->chd[1]=tbc;root->chd[2]=tca;
    flip(tab,2); flip(tbc,2); flip(tca,2);
  }
  void flip(TriRef tri, SdRef pi) {
    TriRef trj=tri->edge[pi].tri; if (!trj) return;
    int pj=tri->edge[pi].side;
    if (!in_cc(tri->p[0],tri->p[1],tri->p[2],trj->p[pj])) return;
    /* flip edge between tri,trj */
    TriRef trk=new(tris++) Tri(tri->p[(pi+1)%3],trj->p[pj],tri->p[pi]);
    TriRef trl=new(tris++) Tri(trj->p[(pj+1)%3],tri->p[pi],trj->p[pj]);
    edge(Edge(trk,0),Edge(trl,0));
    edge(Edge(trk,1),tri->edge[(pi+2)%3]);
    edge(Edge(trk,2),trj->edge[(pj+1)%3]);
    edge(Edge(trl,1),trj->edge[(pj+2)%3]);
    edge(Edge(trl,2),tri->edge[(pi+1)%3]);
    tri->chd[0]=trk; tri->chd[1]=trl; tri->chd[2]=0;
    trj->chd[0]=trk; trj->chd[1]=trl; trj->chd[2]=0;
    flip(trk,1); flip(trk,2); flip(trl,1); flip(trl,2);
  }
}tri; // the triangulation structure
vector<TriRef> triang; // vector of all triangle
set<TriRef> vst;
void go(TriRef now){ // store all tri into triang
  if(vst.find(now)!=vst.end()) return;
  vst.insert(now);
  if(!now->has_chd()){
    triang.push_back(now); return;
  }
  for(int i=0;i<now->num_chd();i++) go(now->chd[i]);
}
void build(int n,Pt* ps){ // build triangulation
  tris=pool; triang.clear(); vst.clear();
  random_shuffle(ps,ps+n); tri.init();
  for(int i=0;i<n;++i) tri.add_point(ps[i]);
  go(tri.the_root);
}

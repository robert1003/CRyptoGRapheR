const int MXN=100005;
const int MXK=10;
struct KDTree{
  struct Nd{
    LL x[MXK];
    int id;
    Nd *l,*r;
  }tree[MXN],*root;
  int n,k;
  LL dis(LL a,LL b){return (a-b)*(a-b);}
  LL dis(LL a[MXK],LL b[MXK]){
    LL ret=0;
    for(int i=0;i<k;i++) ret+=dis(a[i],b[i]);
    return ret;
  }
  void init(vector<vector<LL>> &ip,int _n,int _k){
    n=_n,k=_k;
    for(int i=0;i<n;i++){
      tree[i].id=i;
      copy(ip[i].begin(),ip[i].end(),tree[i].x);
    }
    root=build(0,n-1,0);
  }
  Nd* build(int l,int r,int d){
    if(l>r) return NULL;
    if(d==k) d=0;
    int m=(l+r)>>1;
    nth_element(tree+l,tree+m,tree+r+1,[&](const Nd &a,const Nd &b){return a.x[d]<b.x[d];});
    tree[m].l=build(l,m-1,d+1);
    tree[m].r=build(m+1,r,d+1);
    return tree+m;
  }
  LL pt[MXK],cd[MXK],sd,md;
  int mID;
  void nearest(Nd *r,int d){
    if(!r||sd>=md) return;
    if(d==k) d=0;
    LL td=dis(r->x,pt);
    if(td<md) md=td,mID=r->id;
    LL old=cd[d];
    nearest(pt[d]<r->x[d]?r->l:r->r,d+1);
    cd[d]=dis(r->x[d],pt[d]),sd+=cd[d]-old;
    nearest(pt[d]<r->x[d]?r->r:r->l,d+1);
    sd-=cd[d]-old,cd[d]=old;
  }
  pair<LL,int> query(vector<LL> &_pt,LL _md=1LL<<57){
    mID=-1,md=_md;
    copy(_pt.begin(),_pt.end(),pt);
    nearest(root,0);
    return {md,mID};
  }
}tree;

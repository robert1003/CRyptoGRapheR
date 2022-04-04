const int MEM=100005;
struct Splay {
  static Splay nil,mem[MEM],*pmem; Splay *ch[2],*f;
  int val,rev,size; // int sum,vir,tot;
  Splay(int _val=-1):val(_val),rev(0),size(1)
  { f=ch[0]=ch[1]=&nil; }
  bool isr(){ return f->ch[0]!=this&&f->ch[1]!=this; }
  int dir(){ return f->ch[0]!=this; }
  void setCh(Splay *c,int d){
    ch[d]=c; if(c!=&nil) c->f=this; pull();
  }
  void push(){
    if(!rev) return; swap(ch[0],ch[1]);
    if(ch[0]!=&nil) ch[0]->rev^=1;
    if(ch[1]!=&nil) ch[1]->rev^=1;
    rev=0;
  }
  void pull(){
    size=ch[0]->size+ch[1]->size+1;
    // sum={ch[0]->sum,ch[1]->sum,val}; tot={sum,vir};
    if(ch[0]!=&nil) ch[0]->f=this;
    if(ch[1]!=&nil) ch[1]->f=this;
  }
}Splay::nil,Splay::mem[MEM],*Splay::pmem=Splay::mem;
Splay *nil=&Splay::nil; vector<Splay*> splayVec;
void rotate(Splay *x){
  Splay *p=x->f; int d=x->dir();
  if(!p->isr()) p->f->setCh(x,p->dir()); else x->f=p->f;
  p->setCh(x->ch[!d],d); x->setCh(p,!d);
}
void splay(Splay *x){
  splayVec.clear();
  for(Splay *q=x;; q=q->f){
    splayVec.push_back(q);
    if(q->isr()) break;
  }
  reverse(begin(splayVec),end(splayVec));
  for(auto it:splayVec) it->push();
  while(!x->isr()){
    if(x->f->isr()) rotate(x);
    else if(x->dir()==x->f->dir())
      rotate(x->f),rotate(x);
    else rotate(x),rotate(x);
  }
}
int id(Splay *x){ return x-Splay::mem+1; }
Splay* access(Splay *x){
  Splay *q=nil;
  for(;x!=nil;x=x->f){
    splay(x); // x->vir+={x->ch[0]->tot}-{q->tot};
    x->setCh(q,1); q=x;
  }
  return q;
}
void chroot(Splay *x){ access(x); splay(x); x->rev^=1; }
void link(Splay *x,Splay *y){
  chroot(y); access(x); splay(x); y->f=x; 
  // x->vir+={y->tot};
}
void cut_p(Splay *y){
  access(y);splay(y); y->ch[0]=y->ch[0]->f=nil;
}
void cut(Splay *x,Splay *y){ chroot(x); cut_p(y); }
Splay* get_root(Splay *x) {
  x=access(x);
  for(;x->ch[0]!=nil;x=x->ch[0]) x->push();
  splay(x); return x;
}
bool conn(Splay *x,Splay *y){
  return get_root(x)==get_root(y);
}
Splay* lca(Splay *x,Splay *y){
  access(x); return access(y);
}
/* query(Splay *x,Splay *y){ // path
  setroot(y),x=access(x); return x->size; // x->sum;
} */
/* query(Splay *x,Splay *y){ // path
  Splay *p=lca(x,y); 
  return 1+p->ch[1]->size+(x!=p?x->size:0);
  // {p->val,p->ch[1]->sum,x!=p?x->sum:0};
} */
/* query(Splay *x){ // subtree
  access(x); return {x->val,x->vir};
} */

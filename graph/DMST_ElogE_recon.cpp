struct RollbackUF {
  vi e; vector<pii> st;
  RollbackUF(int n):e(n,-1) {}
  int size(int x) { return -e[find(x)]; }
  int find(int x) { return e[x]<0?x:find(e[x]); }
  int time() { return st.size(); }
  void rollback(int t) {
    for(int i=time();i-->t;)e[st[i].first]=st[i].second;
    st.resize(t);
  }
  bool join(int a,int b) {
    a=find(a),b=find(b);
    if(a==b) return false;
    if(e[a]>e[b]) swap(a,b);
    st.push_back({a,e[a]}); st.push_back({b,e[b]});
    e[a]+=e[b]; e[b]=a;
    return true;
  }
};
struct Edge {int a,b; ll w;};
struct Node { // lazy skew heap node
  Edge key; Node *l,*r; ll d;
  void prop() {
    key.w+=d; if(l) l->d+=d; if(r) r->d+=d; d=0;
  }
  Node(Edge e):key(e),l(0),r(0),d(0){}
  Edge top() { prop(); return key; }
};
Node *merge(Node *a,Node *b) {
  if(!a||!b) return a?a:b;
  a->prop(); b->prop();
  if(a->key.w>b->key.w) swap(a,b);
  swap(a->l,(a->r=merge(b,a->r)));
  return a;
}
void pop(Node*& a){ a->prop(); a=merge(a->l,a->r); }
pair<ll,vi> dmst(int n,int r,vector<Edge>& g){
  RollbackUF uf(n); vector<Node*> pq(n);
  for(Edge e:g) pq[e.b]=merge(pq[e.b],new Node(e));
  ll res=0; vi seen(n,-1),path(n),par(n); seen[r]=r;
  vector<Edge> Q(n),in(n,{-1,-1,0});
  deque<tuple<int,int,vector<Edge>>> cycs;
  for(int s=0;s<n;s++){
    int u=s,qi=0,w;
    while(seen[u]<0){
      if(!pq[u]) return {-1,{}};
      Edge e=pq[u]->top(); pq[u]->d-=e.w,pop(pq[u]);
      Q[qi]=e,path[qi++]=u,seen[u]=s;
      res+=e.w,u=uf.find(e.a);
      if(seen[u]==s) { // found cycle,contract
        Node* cyc=0; int end=qi,t=uf.time();
        do cyc=merge(cyc,pq[w=path[--qi]]);
        while(uf.join(u,w));
        u=uf.find(u),pq[u]=cyc,seen[u]=-1;
        cycs.push_front({u,t,{&Q[qi],&Q[end]}});
      }
    }
    for(int i=0;i<qi;i++) in[uf.find(Q[i].b)]=Q[i];
  }
  for(auto& [u,t,comp]:cycs) { // restore sol
    uf.rollback(t); Edge inEdge=in[u];
    for(auto& e:comp) in[uf.find(e.b)]=e;
    in[uf.find(inEdge.b)]=inEdge;
  }
  for(int i=0;i<n;i++) par[i]=in[i].a;
  return {res,par};
}

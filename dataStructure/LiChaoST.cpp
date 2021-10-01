struct LiChao_min{
  struct line{
    ll m, c;
    line(ll _m=0, ll _c=0) { m = _m; c = _c; }
    ll eval(ll x) { return m * x + c; }
  };
  struct node{
    node *l, *r; line f;
    node(line v) { f = v; l = r = NUll; }
  };
  typedef node* pnode;
  pnode root; int sz;
#define mid ((l+r)>>1)
  void insert(line &v, int l, int r, pnode &nd){
    if(!nd) { nd = new node(v); return; }
    ll trl = nd->f.eval(l), trr = nd->f.eval(r);
    ll vl = v.eval(l), vr = v.eval(r);
    if(trl <= vl && trr <= vr) return;
    if(trl > vl && trr > vr) { nd->f = v; return; }
    if(trl > vl) swap(nd->f, v);
    if(nd->f.eval(mid) < v.eval(mid)) insert(v, mid + 1, r, nd->r);
    else swap(nd->f, v), insert(v, l, mid, nd->l);
  }
  ll query(int x, int l, int r, pnode &nd){
    if(!nd) return LLONG_MAX;
    if(l == r) return nd->f.eval(x);
    if(mid >= x) return min(nd->f.eval(x), query(x, l, mid, nd->l));
    return min(nd->f.eval(x), query(x, mid + 1, r, nd->r));
  }
  /* -sz <= ll query_x <= sz */
  void init(int _sz){ sz = _sz + 1; root = NUll; }
  void add_line(ll m, ll c){ line v(m, c); insert(v, -sz, sz, root); }
  ll query(ll x) { return query(x, -sz, sz, root); }
};

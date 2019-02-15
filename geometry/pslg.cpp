// <: dcmp(x-a.x) < 0 || (dcmp(x-a.x) == 0 && dcmp(y-a.y) < 0)
// ==: dmcp(x-a.x)==0&&dcmp(y-a.y)==0
ld poly_area(vector<Pt> &v) {
  ld area = 0; int n = v.size();
  for(int i = 0 ; i < n-1 ; ++i) {
    area += (v[i]-v[0])^(v[(i+1)%n]-v[0]);
  }
  return area/2;
}
struct PSLG {
#define PB push_back
#define maxn 300000
  struct Edge {
    int u, v; ld ang;
    Edge(int _u, int _v, ld _ang):u(_u), v(_v), ang(_ang) {}

    bool operator<(const Edge& e) const {
      return ang < e.ang;
    }
  };
  int n, m, face_cnt;
  vector<Pt> v;
  vector<Edge> edges;
  vector<int> G[maxn];
  int vis[maxn*2], left[maxn*2], prev[maxn*2];
  vector<vector<Pt> > faces;
  ld area[maxn];

  void init(int _n) {
    n = _n;
    for(int i = 0 ; i < n ; i++) G[i].clear();
    edges.clear();
    faces.clear();
  }

  ld getang(int from, int to) {
    Pt x = v[to]-v[from];
    return atan2(x.y, x.x);
  }

  void addedge(int from, int to) {
    edges.PB(Edge(from, to, getang(from, to)));
    edges.PB(Edge(to, from, getang(to, from)));
    m = (int)edges.size();
    G[from].PB(m-2);
    G[to].PB(m-1);
  }

  void build() {
    for(int u = 0 ; u < n ; u++) {
      sort(G[u].begin(), G[u].end(), [&](int a, int b){return edges[a] < edges[b];});
      for(int i = 0 ; i < (int)G[u].size() ; i++) {
        prev[G[u][(i+1)%G[u].size()]] = G[u][i];
      }
    }

    memset(vis, 0, sizeof(int)*(edges.size()+5));
    face_cnt = 0;
    for(int u = 0 ; u < n ; u++) {
      for(int i = 0 ; i < (int)G[u].size() ; i++) {
        int e = G[u][i];
        if(!vis[e]) {
          face_cnt++;
          vector<Pt> poly;
          while(true) {
            vis[e] = 1; left[e] = face_cnt-1;
            int from = edges[e].u;
            poly.PB(v[from]);
            e = prev[e^1];
            if(e == G[u][i]) break;
            assert(vis[e] == 0);
          }
          faces.PB(poly);
        }
      }
    }

    for(int i = 0 ; i < face_cnt ; ++i) area[i] = poly_area(faces[i]);
  }
} pslg;
int ID(Pt p, vector<Pt>& v) {
  return (int)(lower_bound(v.begin(), v.end(), p) - v.begin());
}
void build_graph(vector<Line>& seg) {
  // get points
  vector<Pt> vp;
  vector<ld> dis[maxn];
  int n = seg.size();
  
  for(int i = 0 ; i < n ; i++) {
    vp.PB(seg[i].s); vp.PB(seg[i].e);
    for(int j = i+1 ; j < n ; j++) {
      Pt p = SSIntersect(seg[i], seg[j]);
      if(!isnan(p.x)) {
        vp.PB(p);
        dis[i].PB(norm(p-seg[i].s));
        dis[j].PB(norm(p-seg[j].s));
      }
    }
  }
  sort(vp.begin(), vp.end());
  int c = (int)(unique(vp.begin(), vp.end()) - vp.begin());
  vp.resize(c);
  pslg.init(c);
  pslg.v = vp;
  
  // get edges
  for(int i = 0; i < n ; i++) {
    ld len = norm(seg[i].v);
    dis[i].PB(0), dis[i].PB(len);
    sort(dis[i].begin(), dis[i].end());
    int sz = (int)dis[i].size();
    for(int j = 1 ; j < sz ; j++) {
      Pt a = seg[i].s + seg[i].v*dis[i][j-1]/len;
      Pt b = seg[i].s + seg[i].v*dis[i][j]/len;
      if(a == b) continue;
      pslg.addedge(ID(a, vp), ID(b, vp));
    }
  }
  
  pslg.build();
}

struct TwoSAT {
  int n;
  Scc scc;
  void init(int _n) {
    // (0,1),(2,3),...
    n = _n; scc.init(n*2);
  }
  void add_disjunction(int a,int na,int b,int nb) {
    a = 2*a^na, b = 2*b^nb;
    scc.addEdge(a^1, b);
    scc.addEdge(b^1, a);
  }
  vector<int> solve() {
    scc.solve();
    vector<int> assignment(n,0);
    for(int i=0; i<n; i++) {
      if (scc.bln[2*i] == scc.bln[2*i^1]) return {};
      assignment[i] = scc.bln[2*i] > scc.bln[2*i^1];
    }
    return assignment;
  }
};

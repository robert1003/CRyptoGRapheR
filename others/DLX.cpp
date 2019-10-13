struct DLX {
  static const int maxr = 5000;
  static const int maxc = 2000;
  static const int maxnode = 20000;
  // row:[1, R], col:[1, C]
  int C, sz;
  int S[maxc];
  int row[maxnode], col[maxnode], L[maxnode], R[maxnode], U[maxnode], D[maxnode];
  int ansd, ans[maxr];

  void init(int _C) {
    C = _C;

    for(int i = 0 ; i <= C ; ++i) {
      U[i] = i; D[i] = i; L[i] = i-1; R[i] = i+1;
    }
    R[C] = 0; L[0] = C;
    sz = C+1;
    memset(S, 0, sizeof(S));
  }
  void addrow(int r, vector<int> co) {
    int fir = sz;
    for(auto &c : co) {
      L[sz] = sz-1; R[sz] = sz+1; D[sz] = c; U[sz] = U[c];
      D[U[c]] = sz; U[c] = sz;
      row[sz] = r; col[sz] = c;
      S[c]++; sz++;
    }
    R[sz-1] = fir; L[fir] = sz-1;
  }
  void remove(int c) {
    L[R[c]] = L[c]; R[L[c]] = R[c];
    for(int i = D[c] ; i != c ; i = D[i]) {
      for(int j = R[i] ; j != i ; j = R[j]) {
        U[D[j]] = U[j]; D[U[j]] = D[j]; --S[col[j]];
      }
    }
  }
  void resume(int c) {
    for(int i = U[c] ; i != c ; i = U[i]) {
      for(int j = L[i] ; j != i ; j = L[j]) {
        ++S[col[j]]; U[D[j]] = j; D[U[j]] = j;
      }
    }
    L[R[c]] = c;
    R[L[c]] = c;
  }
  bool dfs(int d) {
    if(R[0] == 0) { ansd = d; return true; }
    int c = R[0];
    for(int i = R[0] ; i != 0 ; i = R[i]) if(S[i] < S[c]) c = i;
    remove(c);
    for(int i = D[c] ; i != c ; i = D[i]) {
      ans[d] = row[i];
      for(int j = R[i] ; j != i ; j = R[j]) remove(col[j]);
      if(dfs(d+1)) return true;
      for(int j = L[i] ; j != i ; j = L[j]) resume(col[j]);
    }
    resume(c);
    return false;
  }
  bool solve(vector<int> &v) {
    v.clear();
    if(!dfs(0)) return false;
    for(int i = 0 ; i < ansd ; ++i) v.push_back(ans[i]);
    return true;
  }
} dlx;

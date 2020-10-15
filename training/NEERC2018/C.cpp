#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 500 + 5;

int n, m, cnt, dis[N][N], sum[N];
bitset<N> candi;

int ask(int u) {
  cout << u << endl;
  string s; cin >> s;
  if(s[0] == 'F') return -1;
  else {
    int w; cin >> w;
    return w;
  }
}

void init() {
  cin >> n >> m;
  memset(dis, 0x3f, sizeof(dis));
  for(int i = 1 ; i <= n ; ++i) dis[i][i] = 0;
  for(int i = 0 ; i < m ; ++i) {
    int q, u; cin >> q >> u;
    for(int j = 0 ; j < q - 1 ; ++j) {
      int v; cin >> v;
      dis[u][v] = dis[v][u] = 1;
      u = v;
    }
  }
  for(int k = 1 ; k <= n ; ++k) {
    for(int i = 1 ; i <= n ; ++i) {
      for(int j = 1 ; j <= n ; ++j) {
        dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
      }
    }
  }
}
void solve() {
  for(int _ = 1 ; _ <= n ; ++_) {
    candi.set();
    for(int i = 1 ; i <= n ; ++i) {
      sum[i] = 0;
      for(int j = 1 ; j <= n ; ++j) sum[i] += dis[i][j];
    }
    cnt = n;
    while(cnt > 1) {
      int u = -1, mn = 100000;
      for(int i = 1 ; i <= n ; ++i) if(candi[i] && sum[i] < mn) mn = sum[i], u = i;
      int w = ask(u);
      if(w == -1) {
        cnt = 0;
        break;
      }
      vector<int> rem;
      for(int i = 1 ; i <= n ; ++i) if(candi[i] && dis[i][w] >= dis[i][u]) {
        candi[i] = 0, cnt--;
        rem.push_back(i);
      }
      for(auto i : rem) {
        for(int j = 1 ; j <= n ; ++j) if(candi[j]) sum[j] -= dis[i][j];
      }
    }
    if(cnt) {
      for(int i = 1 ; i <= n ; ++i) if(candi[i]) {
        assert(ask(i) == -1);
        break;
      }
    }
  }
}

int main() {
  init();
  solve();
}

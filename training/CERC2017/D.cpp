#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
using ll = long long;

const int N = 2000 + 5;

int R, C, e[N][N], nxt[N], cur_r, cur_c;

inline int mod(int x, int m) { return (x % m + m) % m; }

int next_row(int r, int c) {
  int mx = -1, nr = -1;
  for(int i = r - 1 ; i <= r + 1 ; ++i) {
    int now = e[mod(i, R)][mod(c + 1, C)];
    if(now > mx) mx = now, nr = i;
  }
  return nr;
}
int first_col(int r, int c) {
  do {
    r = mod(next_row(r, c++), R);
  } while(c < C);
  return r;
}
void move(int k) {
  static int vis[N], last_k[N], idx = 0;
  idx++;
  if(k >= C - cur_c) {
    k -= C - cur_c;
    cur_r = first_col(cur_r, cur_c);
    cur_c = 0;
  }
  vis[cur_r] = idx; last_k[cur_r] = k;
  while(k >= C) {
    k -= C;
    cur_r = nxt[cur_r];

    if(vis[cur_r] == idx) {
      int len = last_k[cur_r] - k;
      k %= len;
    }

    vis[cur_r] = idx; last_k[cur_r] = k;
  }
  while(k--) {
    cur_r = mod(next_row(cur_r, cur_c++), R);
  }
}
bool ok(int x, pair<int, int>& p) {
  return x >= p.F && x <= p.S;
}
void update(int r, int c) {
  int end_r = first_col(r, c);
  pair<int, int> cur = {r, r};
  for(int i = c - 1 ; i >= 0 ; --i) {
    pair<int, int> now = {1e9, -1e9};
    for(int j = cur.F - 1 ; j <= cur.F + 1 ; ++j) {
      if(ok(next_row(j, i), cur)) { now.F = j; break; }
    }
    for(int j = cur.S + 1 ; j >= cur.S - 1 ; --j) {
      if(ok(next_row(j, i), cur)) { now.S = j; break; }
    }
    cur = now;
    if(cur.F > cur.S) return;
  }
  if(cur.S - cur.F + 1 >= R) {
    for(int i = 0 ; i < R ; ++i) nxt[i] = end_r;
  }
  else {
    for(int i = cur.F ; i <= cur.S ; ++i) nxt[mod(i, R)] = end_r;
  }
}

void init() {
  cin >> R >> C;
  for(int r = 0 ; r < R ; ++r) {
    for(int c = 0 ; c < C ; ++c) {
      cin >> e[r][c];
    }
  }
  for(int r = 0 ; r < R ; ++r) nxt[r] = first_col(r, 0);
}
void print() {
  for(int i = 0 ; i < R ; ++i) cerr << "nxt[" << i << "]= " << nxt[i] << '\n';
}
void solve() {
  cur_r = cur_c = 0;
  int q; cin >> q;
  while(q--) {
    string op; cin >> op;
    if(op[0] == 'm') {
      int k; cin >> k;
      move(k);
      cout << cur_r + 1 << ' ' << cur_c + 1 << '\n';
    }
    else {
      int a, b, v; cin >> a >> b >> v; a--; b--;
      e[a][b] = v;
      for(int i = a - 1 ; i <= a + 1 ; ++i) {
        update(mod(i, R), mod(b - 1, C));
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}

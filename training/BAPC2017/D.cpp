#include<bits/stdc++.h>
#define ll long long

using namespace std;

struct Edge{
  int v, w;
  bool ban;
};
vector<Edge> E[100005];
bool inque[100005];
long long d[100005];
int p[100005];

int main(){
  ios::sync_with_stdio(0); cin.tie(0);
  int n, m;
  cin >> n >> m;
  for(int i = 0; i < m; ++i) {
    int a, b, distance;
    cin >> a >> b >> distance;
    E[a].push_back({b, distance, 0});
    E[b].push_back({a, distance, 0});
  }
  queue<int> Q;
  fill(d, d + n, (long long)1e18);
  Q.push(1), d[1] = 0, p[1] = 1;
  while(!Q.empty()) {
    auto x = Q.front(); Q.pop();
    inque[x] = 0;
    for(auto e : E[x]) {
      auto y = e.v, w = e.w;
      if(d[x] + w < d[y]) {
        d[y] = d[x] + w;
        p[y] = x;
        if(!inque[y])
          Q.push(y), inque[y] = 1;
      }
    }
  }
  for(int i = 0; i < n; ++i)
    for(auto &e : E[i]) {
      auto j = e.v;
      if(p[i] == j)
        e.ban = 1;
    }

  fill(d, d+n, (long long)(1e18));
  Q.push(0), d[0] = 0, p[0] = 0;
  while(!Q.empty()) {
    auto x = Q.front(); Q.pop();
    inque[x] = 0;
    for(auto e : E[x]) {
      if(e.ban) continue;
      auto y = e.v, w = e.w;
      if(d[x] + w < d[y]) {
        d[y] = d[x] + w;
        p[y] = x;
        if(!inque[y])
          Q.push(y), inque[y] = 1;
      }
    }
  }
  if(d[1] > 1e17)
    cout << "impossible\n";
  else {
    vector<int> sol;
    for(int v = 1; v != 0; v = p[v]) {
      sol.push_back(v);
    }
    sol.push_back(0);
    cout << sol.size();
    for(auto it = sol.rbegin(); it != sol.rend(); ++it)
      cout << ' ' << *it;
    cout << '\n';
  }

  return 0;
}


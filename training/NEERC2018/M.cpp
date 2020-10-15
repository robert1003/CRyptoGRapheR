#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 10;

int n, G[N][N];

void print(vector<vector<string> > &graph) {
  cout << n * 3 << ' ' << n * 3 << ' ' << 3 << '\n';
  for(int i = 2 ; i >= 0 ; --i) {
    for(int j = 0 ; j < n * 3 ; ++j) cout << graph[i][j] << '\n';
    cout << '\n';
  }
}
void build_stair(int v, int i, int j, vector<vector<string> > &graph) {
  graph[2][i + 1][j + 1] = '.';
  graph[1][i][j + 1] = graph[1][i + 1][j + 1] = '.';
  graph[0][j][n * 3 - 1] = '1' + v;
}
void build_hole(int i, int j, vector<vector<string> > &graph) {
  graph[2][j + 1][i + 1] = '.';
  graph[1][j + 1][i + 1] = '.';
  graph[0][j + 1][i + 1] = '.';
}

void init() {
  cin >> n;
  for(int i = 0 ; i < n ; ++i) {
    for(int j = 0 ; j < n ; ++j) cin >> G[i][j];
  }
}
void solve() {
  vector<vector<string> > graph(3, vector<string>('#', string(3 * n, '#')));
  // build basic
  for(int i = 0 ; i < n ; ++i) {
    for(int j = 0 ; j < n * 3 ; ++j) {
      graph[0][i * 3][j] = '.';
      graph[2][j][i * 3] = '.';
    }
    build_stair(i, i * 3, i * 3, graph);
  }
  // build graph
  for(int i = 0 ; i < n ; ++i) {
    for(int j = 0 ; j < n ; ++j) {
      if(G[i][j]) build_hole(i * 3, j * 3, graph);
    }
  }
  // print
  print(graph);
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}

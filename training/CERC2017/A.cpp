#include<bits/stdc++.h>
#define ll long long
 
using namespace std;
 
int r, n;
string seat[100];
 
inline int get_empty(int j) {
  int empty = 0;
  for(int i = 0 ; i < 11 ; ++i) {
    if(seat[j][i] == '.') continue;
    empty += seat[j][i] == '-';
  }
  return empty;
}
int get_re() {
  int e1 = get_empty(1), e2 = get_empty(r / 2 + 2);
  if(e1 == 0 && e2 == 0) return -1;
  else return e1 >= e2 ? 1 : r / 2 + 2;
}
int get_rw() {
  int num = 1, mn = 1e9, idx = -1;
  for(int i = 1 ; i < r / 2 + 1 ; ++i) {
    int cnt = -get_empty(i);
    int dis = min(i, min(abs(i - r / 2 - 1), abs(i - r - 2)));
    if(tie(cnt, dis) < tie(num, mn)) {
      num = cnt;
      mn = dis;
      idx = i;
    }
  }
  for(int i = r / 2 + 2 ; i < r + 2 ; ++i) {
    int cnt = -get_empty(i);
    int dis = min(i, min(abs(i - r / 2 - 1), abs(i - r - 2)));
    if(tie(cnt, dis) < tie(num, mn)) {
      num = cnt;
      mn = dis;
      idx = i;
    }
  }
  assert(idx != -1);
  return idx;
}
void add_seat(int row, char c, int c1, int c2) {
  vector<int> cc;
  if(c1 >= 0 && seat[row][c1] == '-') cc.push_back(c1);
  if(c2 >= 0 && seat[row][c2] == '-') cc.push_back(c2);
  if((int)cc.size() == 1) seat[row][cc[0]] = c;
  else {
    int lef = 0, rig = 0;
    for(int i = 0 ; i < r + 3 ; ++i) {
      for(int j = 0 ; j < 11 ; ++j) {
        if(seat[i][j] == '#' or isalpha(seat[i][j])) {
          if(j < 5) lef++;
          if(j > 5) rig++;
        }
      }
    }
    if(lef > rig) seat[row][cc[1]] = c;
    else seat[row][cc[0]] = c;
  }
}
 
void init() {
  cin >> r >> n;
  for(int i = 0 ; i < r + 3 ; ++i) cin >> seat[i];
}
void solve() {
  for(char c = 'a' ; c < 'a' + n ; ++c) {
    int re = get_re();
    if(re == -1) re = get_rw();
    cerr << c << ' ' << re << '\n'; 
    if(seat[re][4] == '-' or seat[re][6] == '-') add_seat(re, c, 4, 6);
    else if(seat[re][2] == '-' or seat[re][8] == '-') add_seat(re, c, 2, 8);
    else if(seat[re][0] == '-' or seat[re][10] == '-') add_seat(re, c, 0, 10);
    else if(seat[re][5] == '-') add_seat(re, c, 5, -1);
    else add_seat(re, c, 1, 9);
  }
  for(int i = 0 ; i < r + 3 ; ++i) cout << seat[i] << '\n';
}
 
int main(){
  cin.tie(0); ios::sync_with_stdio(0);
 
  init();
  solve();
 
  return 0;
}

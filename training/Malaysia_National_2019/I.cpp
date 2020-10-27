#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  string L[3];
  for(int i = 0; i < 3; ++i) cin >> L[i];

  pair<int, int> pos;
  for(int i = 0; i < 3; ++i)
    for(int j = 0; j < 10; ++j)
      if(L[i][j] == '=') {
        pos = {i, j};
        break;
      }

  string ans = "You shall pass!!!";
  for(int i = pos.second+1; i < 10; ++i)
    if(L[pos.first][i] != '.') {
      ans = L[pos.first][i];
      break;
    }
  cout << ans << '\n';

  
  return 0;
}


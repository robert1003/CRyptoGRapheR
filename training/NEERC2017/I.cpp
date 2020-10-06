#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

const int N = 10000 + 5;

int n, ans[N], split[N], cnt = 0;
vector<int> group[N];
map<pii, bool> mem;

// true: i < j
bool ask(int i, int j) {
  auto it = mem.find({i, j});
  if(it != mem.end()) return it->second;
  cnt++;
  assert(cnt <= 300000);
  cout << "? " << i << ' ' << j << endl;
  char c; cin >> c;
  if(c == '>') mem[{i, j}] = false;
  else mem[{i, j}] = true;
  return c == '<';
}

void init() {
  cin >> n;
}
void solve() {
  if(n == 1) {
    cout << "! 1" << endl;
    return;
  }
  int even = n / 2, odd = (n + 1) / 2;
  for(int i = 1 ; i <= odd ; ++i) {
    if(ask(1, i)) group[2].push_back(i);
    else group[1].push_back(i);
  }
  ans[1] = 2 * group[1].size();
  split[1] = ans[1];
  for(int i = 2 ; i <= even ; ++i) {
    int l = 1, r = group[i].size() ? i : i - 1;
    while(l + 1 < r) {
      int mid = l + (r - l) / 2;
      if(ask(i, group[mid][0])) r = mid;
      else l = mid;
    }
    vector<int> ll, lg, rl, rg;
    for(auto j : group[l]) ask(i, j) ? lg.push_back(j) : ll.push_back(j);
    for(auto j : group[r]) ask(i, j) ? rg.push_back(j) : rl.push_back(j);
    if((int)lg.size() == 0) {
      ans[i] = split[l] + 2 * rl.size();
      for(int j = i ; j >= r ; --j) {
        split[j + 1] = split[j];
        swap(group[j + 1], group[j]);
      }
      group[r] = rl; group[r + 1] = rg;
      split[r] = ans[i];
    }
    else {
      ans[i] = split[l] - 2 * lg.size();
      for(int j = i ; j >= l ; --j) {
        split[j + 1] = split[j];
        swap(group[j + 1], group[j]);
      }
      group[l] = ll; group[l + 1] = lg;
      split[l] = ans[i];
    }
  }
  for(int i = 1 ; i <= odd ; ++i) ans[even + group[i][0]] = i * 2 - 1;
  cout << "!";
  for(int i = 1 ; i <= n ; ++i) cout << ' ' << ans[i];
  cout << endl;
}

int main() {
  init();
  solve();
}

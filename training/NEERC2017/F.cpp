#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int a, b, n, op;
vector<array<int, 4> > ans;

pair<int, int> flip(int x, int y) {
  op = 0;
  if(x < 0) x = -x, op += 1;
  if(y < 0) y = -y, op += 2;
  return {x, y};
}
pair<int, int> uflip(int x, int y) {
  if(op & 1) x = -x;
  if(op & 2) y = -y;
  return {x, y};
}
bool intersect(array<int, 4> p, array<int, 4> q) {
  if(min(p[0], p[2]) <= q[0] && q[0] <= max(p[0], p[2]) && min(q[1], q[3]) <= p[3] && p[3] <= max(q[1], q[3])) return true;
  if(min(q[0], q[2]) <= p[0] && p[0] <= max(q[0], q[2]) && min(p[1], p[3]) <= q[3] && q[3] <= max(p[1], p[3])) return true;
  if(p[0] == q[0] && min(q[1], q[3]) <= p[1] && p[1] <= max(q[1], q[3])) return true;
  if(q[0] == p[0] && min(p[1], p[3]) <= q[1] && q[1] <= max(p[1], p[3])) return true;

  return false;
}

void init() {
  cin >> a >> b >> n;
}
void solve() {
  tie(a, b) = flip(a, b);
  ans.clear();
  while(1) {
    //cerr << a << ' ' << b << '\n';
    if(a < n && b < n) {
      if(ans.size() && !intersect({a, n - 1, -(n - a - 1), 0}, ans.back())) {
        ans.push_back({a, n - 1, -(n - a - 1), 0});
        //cerr << "1a " << a << ' ' << n - 1 << ' ' << -(n - a - 1) << ' ' << 0 << '\n';
      }
      else {
        ans.push_back({0, b - n + 1, n - 1, b});
        //cerr << "1b " << 0 << ' ' << b - n + 1 << ' ' << n - 1 << ' ' << b << '\n';
      }
      break;
    }
    else if(a >= n && b < n) {
      ans.push_back({a - n + 1, b - n + 1, a, b});
      //cerr << "2 " << a - n + 1 << ' ' << b - n + 1 << ' ' << a << ' ' << b << '\n';
      a = a - n, b = 0;
    }
    else if(a < n && b >= n) {
      ans.push_back({a, b, a - n + 1, b - n + 1});
      //cerr << "3 " << a << ' ' << b << ' ' << a - n + 1 << ' ' << b - n + 1 << '\n';
      a = 0, b = b - n;
    }
    else if(a >= n && b >= n && a >= b) {
      ans.push_back({a, b, a - n + 1, b - n + 1});
      //cerr << "4 " << a << ' ' << b << ' ' << a - n + 1 << ' ' << b - n + 1 << '\n';
      a = a - n, b = b - n + 1;
    }
    else if(a >= n && b >= n && a < b) {
      ans.push_back({a - n + 1, b - n + 1, a, b});
      //cerr << "5 " << a - n + 1 << ' ' << b - n + 1 << ' ' << a << ' ' << b << '\n';
      a = a - n + 1, b = b - n;
    }
    else assert(0);
  }
  reverse(ans.begin(), ans.end());
  cout << ans.size() << '\n';
  for(auto [x1, y1, x2, y2] : ans) {
    tie(x1, y1) = uflip(x1, y1);
    tie(x2, y2) = uflip(x2, y2);
    cout << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int t; cin >> t;
  while(t--) {
    init();
    solve();
  }
}

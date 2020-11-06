#include<bits/stdc++.h>
#define ll long long

using namespace std;

map<string, long double> M;
int main(){
  ios::sync_with_stdio(0); cin.tie(0);
  int N;
  cin >> N;
  M["pink"] = log(1.0L);
  M["blue"] = -1e20;;
  long double ub = log(10.0L);
  for(int i = 0; i < N; ++i) {
    string a, b;
    cin >> a >> b;
    long double w;
    cin >> w;
    if(!M.count(a))
      M[a] = -1e20;
    if(M.count(b)) {
      M[a] = max(M[a], log(w) + M[b]);
      if(a == "blue")
        M[a] = min(M[a], ub);
    }
  }
  cout.precision(20);
  cout << fixed;
  cout << exp(M["blue"]) << endl;

  return 0;
}


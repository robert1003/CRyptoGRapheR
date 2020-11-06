#include<bits/stdc++.h>
#define ll long long

using namespace std;

int main(){
  ios::sync_with_stdio(0); cin.tie(0);
  int n;
  cin >> n;
  vector<int> vec(n);
  for(auto &x : vec)
    cin >> x;
  sort(begin(vec), end(vec));
  reverse(begin(vec), end(vec));
  int a = 0, b = 0;
  for(int i = 0; i < vec.size(); ++i)
    if(i&1) b += vec[i];
    else a += vec[i];
  cout << a << ' ' << b << '\n';


  return 0;
}


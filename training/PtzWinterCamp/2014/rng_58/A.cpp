#include<bits/stdc++.h>
#define ll long long

using namespace std;

int main(){
  ios::sync_with_stdio(0); cin.tie(0);
  long double d;
  cin >> d;
  cout.precision(20);
  cout << fixed;

  long double ans = 0;
  for(int i = 0; i <= d; ++i)
    ans = max(ans, i + sqrt(d*d-i*i));

  ans = max(ans, sqrt(2*d*d));
  auto dx = d*d-floor(d)*floor(d);
  if(dx <= 1)
    ans = max(ans, floor(d)+max(dx,1.L));
  cout << ans << endl;
  return 0;
}


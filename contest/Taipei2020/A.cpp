#include<bits/stdc++.h>
#define ll long long

using namespace std;

int main(){
  ios::sync_with_stdio(0); cin.tie(0);
  int t; cin>>t;
  while(t--){
    ll x; cin>>x;
    bool flag=0;
    for(ll a=1;a*a<=x;a++){
      if(x%a==0&&a*2>=x/a) flag=1;
    }
    cout<<flag<<"\n";
  }
  return 0;
}

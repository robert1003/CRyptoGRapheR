#include<bits/stdc++.h>
#define ll long long

using namespace std;

int main(){
  ios::sync_with_stdio(0); cin.tie(0);
  int n; cin>>n;
  vector<ll> a(n);
  for(int i=0;i<n;i++) cin>>a[i];
  set<ll> s;
  vector<ll> v;
  stack<ll> tmp;
  for(int i=0;i<n;i++){
    while(!v.empty()&&__gcd(v.back(),a[i])!=v.back()) tmp.push(v.back()),v.pop_back();
    while(!tmp.empty()){
      if(v.empty()||v.back()!=__gcd(a[i],tmp.top()))
        v.push_back(__gcd(a[i],tmp.top())),s.insert(__gcd(a[i],tmp.top()));
      tmp.pop();
    }
    if(v.empty()||v.back()!=a[i]) v.push_back(a[i]),s.insert(a[i]);
  }
  cout<<s.size()<<"\n";
  return 0;
}


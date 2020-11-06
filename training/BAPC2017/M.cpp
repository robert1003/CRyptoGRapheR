#include<bits/stdc++.h>
#define ll long long

using namespace std;

int main(){
  ios::sync_with_stdio(0); cin.tie(0);
  int n; cin>>n;
  int x1,y1,x2,y2; cin>>x1>>y1>>x2>>y2;
  vector<pair<int,int>> a(n);
  for(int i=0;i<n;i++) cin>>a[i].first>>a[i].second;
  if(x1>x2){
    x1=-x1; x2=-x2;
    for(int i=0;i<n;i++) a[i].first=-a[i].first;
  }
  if(y1>y2){
    y1=-y1; y2=-y2;
    for(int i=0;i<n;i++) a[i].second=-a[i].second;
  }
  sort(a.begin(),a.end());
  vector<int> v;
  for(int i=0;i<n;i++){
    if(a[i].first<x1||a[i].first>x2||a[i].second<y1||a[i].second>y2) continue;
    if(v.empty()||a[i].second>=v.back()) v.push_back(a[i].second);
    else *upper_bound(v.begin(),v.end(),a[i].second)=a[i].second;
  }
  cout<<v.size()<<"\n";
  return 0;
}


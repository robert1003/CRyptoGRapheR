#include<bits/stdc++.h>
#define ll long long
 
using namespace std;
 
ll powi(ll a,ll b,ll p){
  ll ret=1;
  for(;b;b>>=1,a=a*a%p){
    if(b&1)
      ret=ret*a%p;
  }
  return ret;
}
 
ll inv(ll a,ll p){
  return powi(a,p-2,p);
}
 
int main(){
  cin.tie(0); ios::sync_with_stdio(0);
  ll n,p,r; cin>>n>>p>>r;
  if(n<p){
    if(r==0){
      cout<<"-1 -1\n";
      exit(0);
    }
    ll cur=1;
    for(ll i=1;i<=n;i++) cur=cur*i%p;
    cur=r*inv(cur,p)%p;
    for(ll i=2;i<=n;i++){
      if(cur*i%p<i){
        cout<<i<<" "<<cur*i%p<<"\n";
        exit(0);
      }
    }
    cout<<"-1 -1\n";
  }
  else if(n<p+p){
    if(r==0){
      if(p==2){
        if(n==2) cout<<"-1 -1\n";
        else cout<<"3 1\n";
      }
      else cout<<"2 1\n";
      exit(0);
    }
    ll cur=1;
    for(ll i=1;i<=n;i++){
      if(i==p) continue;
      cur=cur*i%p;
    }
    for(ll i=1;i<p;i++){
      if(cur*i%p==r){
        cout<<p<<" "<<i<<"\n";
        exit(0);
      }
    }
    cout<<"-1 -1\n";
  }
  else{
    if(r==0) cout<<"2 1\n";
    else cout<<"-1 -1\n";
  }
  return 0;
}

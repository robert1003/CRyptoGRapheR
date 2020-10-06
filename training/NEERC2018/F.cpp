#include<bits/stdc++.h>
#define ll long long

using namespace std;

pair<ll,ll> gcd(ll a,ll b){
  if(b==0) return {1,0};
  pair<ll,ll> q=gcd(b,a%b);
  return {q.second,q.first-q.second*(a/b)};
}

int main(){
  cin.tie(0); ios::sync_with_stdio(0);
  ll n; cin>>n;
  ll a=-1,b=-1,tmp=n;
  for(ll i=2;i*i<=tmp;i++){
    if(tmp%i==0){
      while(tmp%i==0) tmp/=i;
      if(a==-1) a=i;
      else{
        b=i;
        break;
      }
    }
  }
  if(a!=-1&&b==-1&&tmp>1) b=tmp;
  if(b==-1){
    cout<<"NO\n";
    return 0;
  }
  cout<<"YES\n2\n";
  ll x,y; tie(x,y)=gcd(a,b);
  x*=n-1; y*=n-1;
  if(y<0) swap(x,y),swap(a,b);
  ll k=(-x+b-1)/b;
  x+=k*b; y-=k*a;
  if(a<b) swap(a,b),swap(x,y);
  cout<<x<<" "<<n/a<<"\n";
  cout<<y<<" "<<n/b<<"\n";
  return 0;
}


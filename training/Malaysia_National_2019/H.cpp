#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

struct pt{
  ll x,y;
  friend bool operator<(const pt &a,const pt &b){
    return tie(a.x,a.y)<tie(b.x,b.y);
  }
};

pt a[55],hull[55];

int sgn(ll x){
  return (x>0)-(x<0);
}

int cross(const pt &o,const pt &a,const pt &b){
  return sgn((a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x));
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int t; cin>>t;
  for(int tt=1;tt<=t;tt++){
    if(tt>1) cout<<"\n";
    cout<<"Case "<<tt<<"\n";
    int n,q; cin>>n>>q;
    for(int i=0;i<n;i++) cin>>a[i].x>>a[i].y;
    sort(a,a+n);
    int m=0;
    for(int i=0;i<n;i++){
      while(m>=2&&cross(hull[m-2],hull[m-1],a[i])<0) m--;
      hull[m++]=a[i];
    }
    int l=m;
    for(int i=n-2;i>=0;i--){
      while(m-l>=1&&cross(hull[m-2],hull[m-1],a[i])<0) m--;
      hull[m++]=a[i];
    }
    for(int i=0;i<m;i++) cout<<hull[i].x<<" "<<hull[i].y<<"\n";
    while(q--){
      pt p; cin>>p.x>>p.y;
      bool f=1;
      for(int i=1;i<m;i++){
        if(cross(p,hull[i-1],hull[i])<=0) f=0;
      }
      cout<<p.x<<" "<<p.y<<" is "<<(f?"unsafe!\n":"safe!\n");
    }
  }
  return 0;
}


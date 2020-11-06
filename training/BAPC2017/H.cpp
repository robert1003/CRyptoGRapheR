#include<bits/stdc++.h>
#define ll long long

using namespace std;

struct Pt{
  ll x,y;
  friend Pt operator-(const Pt &a,const Pt &b){
    return {a.x-b.x,a.y-b.y};
  }
  friend ll operator*(const Pt &a,const Pt &b){
    return a.x*b.x+a.y*b.y;
  }
  friend ll operator^(const Pt &a,const Pt &b){
    return a.x*b.y-a.y*b.x;
  }
};

int ori(const Pt &o,const Pt &a,const Pt &b){
  ll ret=(a-o)^(b-o);
  return (ret>0)-(ret<0);
}
bool banana(const Pt &p1,const Pt &p2,const Pt &q1,const Pt &q2){
  if(((p2-p1)^(q2-q1))==0){
    if(ori(p1,p2,q1)) return false;
    return ((p1-q1)*(p2-q1))<=0||((p1-q2)*(p2-q2))<=0||
           ((q1-p1)*(q2-p1))<=0||((q1-p2)*(q2-p2))<=0;
  }
  return (ori(p1,p2,q1)*ori(p1,p2,q2)<=0)&&(ori(q1,q2,p1)*ori(q1,q2,p2)<=0);
}

int p[1005];
int find(int x){
  return x==p[x]?x:p[x]=find(p[x]);
}

int main(){
  ios::sync_with_stdio(0); cin.tie(0);
  int n; cin>>n;
  vector<pair<Pt,Pt>> a(n);
  for(int i=0;i<n;i++) cin>>a[i].first.x>>a[i].first.y>>a[i].second.x>>a[i].second.y;
  int ans=-n;
  iota(p,p+n,0);
  for(int i=0;i<n;i++){
    for(int j=i+1;j<n;j++){
      if(banana(a[i].first,a[i].second,a[j].first,a[j].second)){
        ans+=1;
        p[find(i)]=find(j);
      }
    }
  }
  for(int i=0;i<n;i++){
    if(i==find(i)) ans++;
  }
  cout<<ans<<"\n";
  return 0;
}


#include<bits/stdc++.h>
#define ll long long

using namespace std;

struct Hasher{
  unsigned ll operator()(const pair<ll,ll> p) const{
    return ((unsigned ll)p.first<<32)+p.second;
  }
};

ll ans=5e10;

ll cross(const array<ll,3>&a,const array<ll,3>&b){
  return a[0]*b[1]-a[1]*b[0];
}

void solve(vector<array<ll,3>> a){
  vector<vector<array<ll,3>>> v(5);
  int n=a.size();
  for(int i=0;i<n;i++){
    if(a[i][0]>=0&&a[i][1]>=0) v[1].push_back(a[i]);
    if(a[i][0]<0&&a[i][1]>0) v[2].push_back(a[i]);
    if(a[i][0]<=0&&a[i][1]<=0) v[3].push_back(a[i]);
    if(a[i][0]>0&&a[i][1]<0) v[4].push_back(a[i]);
  }
  if(v[1].empty()) return;
  ll mn2=5e10,mn4=5e10;
  for(auto &i:v[2]) mn2=min(mn2,i[2]);
  for(auto &i:v[4]) mn4=min(mn4,i[2]);
  sort(v[1].begin(),v[1].end(),[](const auto &i,const auto &j){return cross(i,j)>0;});
  sort(v[3].begin(),v[3].end(),[](const auto &i,const auto &j){return cross(i,j)>0;});
  ll bst=5e10;
  for(int i=0,j=0;i<(int)v[3].size();i++){
    while(j<(int)v[1].size()&&cross(v[3][i],v[1][j])>0){
      bst=min(bst,v[1][j++][2]);
    }
    ans=min(ans,v[3][i][2]+bst+mn2);
  }
  bst=5e10;
  for(int i=(int)v[3].size()-1,j=(int)v[1].size()-1;i>=0;i--){
    while(j>=0&&cross(v[3][i],v[1][j])<0){
      bst=min(bst,v[1][j--][2]);
    }
    ans=min(ans,v[3][i][2]+bst+mn4);
  }
  vector<ll> pre(v[1].size());
  pre[0]=v[1][0][2];
  for(int i=1;i<(int)v[1].size();i++) pre[i]=min(pre[i-1],v[1][i][2]);
  bst=5e10;
  for(int i=(int)v[3].size()-1,j=(int)v[1].size()-1;i>=0;i--){
    while(j>=0&&cross(v[3][i],v[1][j])<0){
      bst=min(bst,v[1][j--][2]);
    }
    int jj=j;
    if(jj<0) continue;
    if(cross(v[3][i],v[1][jj])==0) jj--;
    if(jj<0) continue;
    ans=min(ans,v[3][i][2]+bst+pre[jj]);
  }
}

int main(){
  ios::sync_with_stdio(0); cin.tie(0);
  int n; cin>>n;
  vector<array<ll,3>> a;
  for(int i=0;i<n;i++){
    int x,y,p;
    cin>>x>>y>>p;
    if(!x&&!y) continue;
    if(x==0) y/=abs(y);
    else if(y==0) x/=abs(x);
    else{
      ll g=__gcd(abs(x),abs(y));
      x/=g; y/=g;
    }
    a.push_back({x,y,p});
  }
  n=a.size();
  sort(a.begin(),a.end());
  vector<array<ll,3>> tmp=move(a);
  a.clear();
  for(int i=0;i<n;i++){
    if(i==0||tmp[i][0]!=tmp[i-1][0]||tmp[i][1]!=tmp[i-1][1])
      a.push_back(tmp[i]);
  }
  n=a.size();
  for(int i=0;i<2;i++){
    for(int j=0;j<2;j++){
      solve(a);
      for(int k=0;k<n;k++) a[k][0]=-a[k][0];
    }
    for(int k=0;k<n;k++) a[k][1]=-a[k][1];
  }
  unordered_map<pair<ll,ll>,ll,Hasher> mp;
  for(int i=0;i<n;i++)
    mp[make_pair(a[i][0],a[i][1])]=a[i][2];
  for(int i=0;i<n;i++){
    if(a[i][0]<0||a[i][1]<0) continue;
    if(mp.count(make_pair(-a[i][0],-a[i][1]))&&mp.count(make_pair(a[i][1],-a[i][0]))&&mp.count(make_pair(-a[i][1],a[i][0]))){
      ans=min(ans,a[i][2]+mp[make_pair(-a[i][0],-a[i][1])]+mp[make_pair(a[i][1],-a[i][0])]+mp[make_pair(-a[i][1],a[i][0])]);
    }
  }
  if(ans>1e10) ans=-1;
  cout<<ans<<"\n";
  return 0;
}


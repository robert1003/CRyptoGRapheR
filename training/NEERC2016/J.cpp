#include <bits/stdc++.h>
#define ll long long
#define bye cout<<"yes\n"<<i<<"\n",exit(0)
using namespace std;
 
set<int> s[5005];
array<ll,2> a[5005];
int mn[5005],mx[5005];
 
int main() {
  string filename="jenga";
  freopen((filename+".in").data(),"r",stdin);
  freopen((filename+".out").data(),"w",stdout);
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n,w,h,m; cin>>n>>w>>h>>m; w*=2;
  for(int i=1;i<=h;i++){
    a[i][0]=(ll)n*w/2*n;
    a[i][1]=(ll)n*w/2*n;
  }
  for(int i=1;i<=h;i++) mn[i]=1,mx[i]=n;
  for(int i=1;i<=m;i++){
    int l,k; cin>>l>>k;
    if(l&1){
      a[l][0]-=n*w/2;
      a[l][1]-=k*w-w/2;
    }
    else{
      a[l][0]-=k*w-w/2;
      a[l][1]-=n*w/2;
    }
    s[l].insert(k);
    while(s[l].count(mn[l])) mn[l]++;
    while(s[l].count(mx[l])) mx[l]--;
    ll x=0,y=0;
    int c=0;
    for(int j=h;j>=1;j--){
      if(x||y){
        if((int)s[j].size()==n) bye;
        if(j&1){
          ll mny=(ll)(mn[j]-1)*c*w,mxy=(ll)mx[j]*c*w;
          if(!(mny<y&&y<mxy)) bye;
        }
        else{
          ll mnx=(ll)(mn[j]-1)*c*w,mxx=(ll)mx[j]*c*w;
          if(!(mnx<x&&x<mxx)) bye;
        }
      }
      x+=a[j][0]; y+=a[j][1]; c+=n-s[j].size();
    }
  }
  cout<<"no\n";
  return 0;
}

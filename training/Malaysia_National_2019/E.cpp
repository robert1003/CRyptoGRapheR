#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int a[1005];
int p[1005][1005];

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int t;
  while(cin>>t,t){
    int n; cin>>n;
    for(int i=0;i<n;i++) cin>>a[i];
    reverse(a,a+n);
    for(int i=0;i<=n;i++){
      for(int j=0;j<=t;j++)
        p[i][j]=0;
    }
    p[0][0]=1;
    for(int i=1;i<=n;i++){
      for(int j=0;j<=t;j++){
        if(j>=a[i-1]&&p[i-1][j-a[i-1]]) p[i][j]=1;
        else if(p[i-1][j]) p[i][j]=2;
      }
    }
    int ans=t;
    while(p[n][ans]==0) ans--;
    vector<int> bg;
    for(int i=n,j=ans;i||j;i--){
      if(p[i][j]==1) bg.push_back(i-1),j-=a[i-1];
    }
    for(int i:bg) cout<<a[i]<<" ";
    cout<<ans<<"\n";
  }
  return 0;
}


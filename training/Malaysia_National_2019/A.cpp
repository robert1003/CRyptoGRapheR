#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

char a[1005][1005],b[1005][1005];

void lr(int n){
  memcpy(b,a,sizeof(a));
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++)
      a[i][j]=b[j][n-i-1];
  }
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      if(a[i][j]=='<') a[i][j]='v';
      else if(a[i][j]=='v') a[i][j]='>';
      else if(a[i][j]=='>') a[i][j]='^';
      else if(a[i][j]=='^') a[i][j]='<';
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n; string s; cin>>n>>s;
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++)
      cin>>a[i][j];
  }
  int p=0;
  for(char c:s){
    if(c=='L') p++;
    else p--;
  }
  p&=3;
  while(p--) lr(n);
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++)
      cout<<a[i][j];
    cout<<"\n";
  }
  return 0;
}


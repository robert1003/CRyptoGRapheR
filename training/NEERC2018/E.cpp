#include<bits/stdc++.h>
#define ll long long
 
using namespace std;
 
string a[70];
 
int main(){
  cin.tie(0); ios::sync_with_stdio(0);
  int n; cin>>n;
  if(n<=9){
    for(int i=1;i<n;i++) cout<<"a"<<i<<" ";
    if(n==8) cout<<"a8 h8\n";
    else if(n==9) cout<<"b8 h8\n";
    else cout<<"h"<<n-1<<" h8\n";
  }
  else{
    cout<<"a1 ";
    int r=0;
    for(int i=8;i>0&&n>2;i--){
      if(i&1){
        for(int j=6;j>=(i==1?1:0)&&n>2;j--) cout<<(char)('a'+j)<<i<<" ",n--;
      }
      else{
        for(int j=0;j<7&&n>2;j++) cout<<(char)('a'+j)<<i<<" ",n--;
      }
      r=i;
    }
    if(n==2) cout<<"h"<<r<<" h8\n";
    else{
      for(int i=1;i<8&&n>1;i++) cout<<"h"<<i<<" ",n--;
      cout<<"h8\n";
    }
  }
  return 0;
}

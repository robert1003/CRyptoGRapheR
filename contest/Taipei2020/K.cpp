#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long

using namespace std;

ull f[20],c16[20],t16;
ull p10[20],c10[20],t10;
bool v[20];

ull hexi(ull k){
  int len=0;
  while(len<=16&&k>=c16[len]) k-=c16[len++];
  if(len>16) return -1ll;
  fill(v,v+16,0);
  int n=16,m=len;
  ull res=0;
  for(int i=0;i<len;i++){
    int st=(i==0?1:0);
    int cc=k/(f[n-1]/f[n-m]);
    k%=f[n-1]/f[n-m]; n--; m--;
    for(int j=st;j<16;j++){
      if(!v[j]){
        if(!cc--){
          v[j]=1; res+=j*(1ull<<((len-i-1)*4));
          break;
        }
      }
    }
  }
  return res;
}

ll hc(ull v){
  ll l=0,r=t16-1,m;
  while(l<r){
    m=(l+r+1)>>1;
    if(hexi(m)<=v) l=m;
    else r=m-1;
  }
  return l+1;
}

ull deciiii(ull k){
  int len=0;
  while(len<=10&&k>=c10[len]) k-=c10[len++];
  if(len>10) return -1ll;
  fill(v,v+10,0);
  int n=10,m=len;
  ull res=0;
  for(int i=0;i<len;i++){
    int st=(i==0?1:0);
    int cc=k/(f[n-1]/f[n-m]);
    k%=f[n-1]/f[n-m]; n--; m--;
    for(int j=st;j<10;j++){
      if(!v[j]){
        if(!cc--){
          v[j]=1; res+=j*p10[len-i-1];
          break;
        }
      }
    }
  }
  return res;
}

ll dc(ull v){
  ll l=0,r=t10-1,m;
  while(l<r){
    m=(l+r+1)>>1;
    if(deciiii(m)<=v) l=m;
    else r=m-1;
  }
  return l+1;
}

int main(){
  ios::sync_with_stdio(0); cin.tie(0);
  f[0]=1;
  for(int i=1;i<=16;i++) f[i]=f[i-1]*i;
  c16[0]=1;
  for(int i=1;i<=16;i++) c16[i]=15*f[15]/f[16-i];
  for(int i=0;i<=16;i++) t16+=c16[i];
  c10[0]=1;
  for(int i=1;i<=10;i++) c10[i]=9*f[9]/f[10-i];
  for(int i=0;i<=10;i++) t10+=c10[i];
  p10[0]=1;
  for(int i=1;i<=10;i++) p10[i]=p10[i-1]*10;
  int t; cin>>t;
  while(t--){
    char bs; cin>>dec>>bs;
    if(bs=='d'){
      int tp; cin>>dec>>tp;
      if(tp==0){
        ull a,b; cin>>dec>>a>>b;
        if(a==0) cout<<dec<<dc(b)<<"\n";
        else cout<<dec<<dc(b)-dc(a-1)<<"\n";
      }
      else{
        ull x; cin>>dec>>x;
        ull ret=deciiii(x-1);
        if(!~ret) cout<<"-\n";
        else cout<<dec<<deciiii(x-1)<<"\n";
      }
    }
    else{
      int tp; cin>>dec>>tp;
      if(tp==0){
        ull a,b; cin>>hex>>a>>b;
        if(a==0) cout<<hex<<hc(b)<<"\n";
        else cout<<hex<<hc(b)-hc(a-1)<<"\n";
      }
      else{
        ull x; cin>>hex>>x;
        ull ret=hexi(x-1);
        if(!~ret) cout<<"-\n";
        else cout<<hex<<hexi(x-1)<<"\n";
      }
    }
  }
  return 0;
}

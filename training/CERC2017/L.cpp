#pragma GCC optimize("O3,unroll-loops,no-stack-protector")
#include<bits/stdc++.h>
#define ll long long
#define cl(i) ((i<<1)+1)
#define cr(i) ((i<<1)+2)
 
using namespace std;
 
bitset<8200> t1[8200];
bitset<16500> t2[16500];
bitset<3010> a1[3010];
bitset<6020> a2[6020];
 
int lx,rx,ly,ry;
void sety1(int i,int j=0,int l=0,int r=3001){
  if(ly<=l&&r<=ry){
    t1[i][j]=1;
    return;
  }
  int m=(l+r)>>1;
  if(ly<=m) sety1(i,cl(j),l,m);
  if(ry>m) sety1(i,cr(j),m+1,r);
}
 
void setx1(int i=0,int l=0,int r=3001){
  if(lx<=l&&r<=rx){
    sety1(i);
    return;
  }
  int m=(l+r)>>1;
  if(lx<=m) setx1(cl(i),l,m);
  if(rx>m) setx1(cr(i),m+1,r);
}
 
void pushy1(int i,int x,int j=0,int l=0,int r=3001){
  if(l==r){
    a1[x][l]=t1[i][j];
    return;
  }
  if(t1[i][j]) t1[i][cl(j)]=t1[i][cr(j)]=1;
  int m=(l+r)>>1;
  pushy1(i,x,cl(j),l,m);
  pushy1(i,x,cr(j),m+1,r);
}
 
void pushx1(int i=0,int l=0,int r=3001){
  if(l==r){
    pushy1(i,l);
    return;
  }
  t1[cl(i)]|=t1[i];
  t1[cr(i)]|=t1[i];
  int m=(l+r)>>1;
  pushx1(cl(i),l,m);
  pushx1(cr(i),m+1,r);
}
 
void sety2(int i,int j=0,int l=0,int r=6002){
  if(ly<=l&&r<=ry){
    t2[i][j]=1;
    return;
  }
  int m=(l+r)>>1;
  if(ly<=m) sety2(i,cl(j),l,m);
  if(ry>m) sety2(i,cr(j),m+1,r);
}
 
void setx2(int i=0,int l=0,int r=6002){
  if(lx<=l&&r<=rx){
    sety2(i);
    return;
  }
  int m=(l+r)>>1;
  if(lx<=m) setx2(cl(i),l,m);
  if(rx>m) setx2(cr(i),m+1,r);
}
 
void pushy2(int i,int x,int j=0,int l=0,int r=6002){
  if(l==r){
    a2[x][l]=t2[i][j];
    return;
  }
  if(t2[i][j]) t2[i][cl(j)]=t2[i][cr(j)]=1;
  int m=(l+r)>>1;
  pushy2(i,x,cl(j),l,m);
  pushy2(i,x,cr(j),m+1,r);
}
 
void pushx2(int i=0,int l=0,int r=6002){
  if(l==r){
    pushy2(i,l);
    return;
  }
  t2[cl(i)]|=t2[i];
  t2[cr(i)]|=t2[i];
  int m=(l+r)>>1;
  pushx2(cl(i),l,m);
  pushx2(cr(i),m+1,r);
}
 
const int sh1=1502,sh2=3004;
 
int main(){
  cin.tie(0); ios::sync_with_stdio(0);
  int n; cin>>n;
  while(n--){
    char c; int x,y,l; cin>>c>>x>>y>>l; l>>=1;
    if(c=='A'){
      lx=x-l; ly=y-l; rx=x+l; ry=y+l;
      lx+=sh1; ly+=sh1; rx+=sh1-1; ry+=sh1-1;
      setx1();
    }
    else{
      lx=x-l; ly=y; rx=x+l; ry=y;
      tie(lx,ly)=make_pair(lx-ly,lx+ly);
      tie(rx,ry)=make_pair(rx-ry,rx+ry);
      lx+=sh2; ly+=sh2; rx+=sh2-1; ry+=sh2-1;
      setx2();
    }
  }
  pushx1(); pushx2();
  ll cnt=0;
  for(int i=-sh1+1;i<sh1;i++){
    for(int j=-sh1+1;j<sh1;j++){
      if(a1[i+sh1][j+sh1]) cnt+=4;
      else{
        if(a2[i-j+sh2][i+j+sh2]) cnt++;
        if(a2[i-(j+1)+sh2][i+(j+1)+sh2]) cnt++;
        if(a2[i-j+sh2][i+j+1+sh2]) cnt++;
        if(a2[i-j-1+sh2][i+j+sh2]) cnt++;
      }
    }
  }
  cout<<cnt/4<<"."<<setfill('0')<<setw(2)<<((cnt&3)*25)<<"\n";
  return 0;
}

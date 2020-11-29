#include<bits/stdc++.h>
#define ll long long

using namespace std;

int n,a[6];
int bst=1e9,cur,mnn;
int ch[6][6];
int msk[25];

void dfs(int i){
  if(bst==mnn||cur>=bst) return;
  if(i==n){
    bst=min(bst,cur);
    return;
  }
  vector<int> id(i);
  int stcur=cur;
  while(1){
    int k=0,cm=0;
    bool flag=1;
    for(int j=0;j<i;j++){
      if(id[j]<a[j]){
        ch[i][k++]=ch[j][id[j]];
        if(cm&msk[ch[j][id[j]]]){
          flag=0;
          break;
        }
        cm|=msk[ch[j][id[j]]];
      }
    }
    if(flag&&k<=a[i]){
      for(int j=k;j<a[i];j++) ch[i][j]=cur++;
      for(int j=0;j<a[i];j++) msk[ch[i][j]]|=(1<<i);
      dfs(i+1);
      for(int j=0;j<a[i];j++) msk[ch[i][j]]^=(1<<i);
      cur=stcur;
    }
    for(int j=i-1;j>=0;j--){
      if(id[j]+1<=a[j]){
        id[j]++;
        break;
      }
      else{
        if(j==0) return;
        id[j]=0;
      }
    }
  }
}

int main(){
  ios::sync_with_stdio(0); cin.tie(0);
  cin>>n;
  ll ans=0;
  for(int i=0;i<n;i++){
    cin>>a[i];
    if(a[i]>4){
      ans+=a[i]-4;
      a[i]=4;
    }
  }
  sort(a,a+n); reverse(a,a+n);
  cur=a[0];
  for(int i=0;i<a[0];i++){
    ch[0][i]=i;
    msk[i]|=1;
  }
  mnn=a[0]+a[1]-1+max(0,a[2]-2)+max(0,a[3]-3)+max(0,a[4]-4);
  dfs(1);
  cout<<ans+bst<<"\n";
  return 0;
}


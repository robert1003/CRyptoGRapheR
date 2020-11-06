#include<bits/stdc++.h>
#define ll long long

using namespace std;

constexpr int N=1005;
bitset<N> a[N];
vector<int> ans;

int solve(bitset<N> cur,bitset<N> mask){
  bitset<N> win;
  for(int i=cur._Find_first();i!=N;i=cur._Find_next(i))
    win|=a[i];
  win&=mask;
  bitset<N> rem=mask&~win;
  if(win.none()) return -1;
  int lst=0;
  if(!rem.none()&&(lst=solve(win,rem))==-1) return -1;
  if(lst){
    for(int i=win._Find_first();i!=N;i=win._Find_next(i)){
      if(a[i][lst]){
        ans.push_back(i); lst=i; win[i]=0;
      }
    }
  }
  else{
    ans.push_back(lst=win._Find_first()); win[lst]=0;
  }
  for(int i=win._Find_first();i!=N;i=win._Find_next(i)){
    ans.push_back(i); win[i]=0; lst=(a[lst][i]?lst:i);
  }
  return lst;
}

int main(){
  ios::sync_with_stdio(0); cin.tie(0);
  int n; cin>>n;
  for(int i=0;i<n;i++){
    string s; cin>>s;
    for(int j=0;j<(int)s.size();j++){
      if(s[j]=='1') a[i][j]=1;
    }
  }
  bitset<N> mask(string(n,'1')),cur("1");
  mask[0]=0;
  if(solve(cur,mask)==-1) cout<<"impossible\n";
  else{
    ans.push_back(0);
    for(int i=0;i<n;i++) cout<<ans[i]<<" \n"[i+1==n];
  }
  return 0;
}


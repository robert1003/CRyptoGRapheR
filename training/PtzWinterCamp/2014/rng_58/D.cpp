#include<bits/stdc++.h>
#define ll long long

using namespace std;

int h,w,n;
pair<int,int> a[200005];
vector<int> sum[400005],_sub[400005],*sub=_sub+200002;

int walk(int y){
  int dir=(y&1),x=0;
  while(x<h){
    if(dir==0){
      int sb=x-y;
      auto it=upper_bound(sub[sb].begin(),sub[sb].end(),y);
      if(it==sub[sb].end()){
        int k=min(h-x,w-1-y);
        x+=k+1; y+=k;
      }
      else{
        int k=*it-y-1;
        x+=k+1; y+=k;
      }
      dir=1;
    }
    else{
      int sm=x+y+1;
      auto it=upper_bound(sum[sm].begin(),sum[sm].end(),y);
      if(it==sum[sm].begin()){
        int k=min(h-x,y);
        x+=k+1; y-=k;
      }
      else{
        --it;
        int k=y-*it;
        x+=k+1; y-=k;
      }
      dir=0;
    }
  }
  return y;
}

int main(){
  ios::sync_with_stdio(0); cin.tie(0);
  cin>>h>>w>>n;
  for(int i=0;i<n;i++){
    cin>>a[i].first>>a[i].second;
    sum[a[i].first+a[i].second].push_back(a[i].second);
    sub[a[i].first-a[i].second].push_back(a[i].second);
  }
  for(int i=0;i<=400002;i++) sort(sum[i].begin(),sum[i].end());
  for(int i=-200001;i<=200002;i++) sort(sub[i].begin(),sub[i].end());
  for(int i=0;i<w;i++){
    cout<<walk(i)+1<<"\n";
  }
  return 0;
}


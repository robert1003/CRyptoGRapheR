#include <bits/stdc++.h>
#define ll long long
using namespace std;
 
const int ninf=-32768,inf=32767;
 
int main() {
  string filename="hard";
  freopen((filename+".in").data(),"r",stdin);
  freopen((filename+".out").data(),"w",stdout);
  ios_base::sync_with_stdio(0), cin.tie(0);
  vector<pair<int,int>> v;
  string s; int x;
  while(getline(cin,s)){
    pair<int,int> s1,s2;
    stringstream ss(s);
    ss>>s>>s>>x;
    if(s=="<=") s1={ninf,x};
    else s1={x,inf};
    ss>>s;
    if(ss&&s=="&&"){
      ss>>s>>s>>x;
      if(s=="<=") s2={ninf,x};
      else s2={x,inf};
      int l=max(s1.first,s2.first);
      int r=min(s1.second,s2.second);
      if(l<=r) v.push_back({l,r});
    }
    else{
      v.push_back(s1);
      if(!ss) break;
    }
  }
  sort(v.begin(),v.end());
  vector<pair<int,int>> ans;
  for(auto &&i:v){
    if(ans.empty()||i.first>ans.back().second+1) ans.push_back(i);
    else ans.back().second=max(ans.back().second,i.second);
  }
  if(ans.empty()) cout<<"false\n";
  else if(ans.size()==1&&ans[0]==make_pair(ninf,inf)) cout<<"true\n";
  else{
    for(int i=0;i<(int)ans.size();i++){
      if(ans[i].first==ninf) cout<<"x <= "<<ans[i].second;
      else if(ans[i].second==inf) cout<<"x >= "<<ans[i].first;
      else cout<<"x >= "<<ans[i].first<<" && x <= "<<ans[i].second;
      if(i+1!=(int)ans.size()) cout<<" ||";
      cout<<"\n";
    }
  }
  return 0;
}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  vector<pair<int,int>> v(5);
  for(int i=0;i<5;i++){
    string s; cin>>s;
    if(s[1]=='>') v[i]={s[2]-'A',s[0]-'A'};
    else v[i]={s[0]-'A',s[2]-'A'};
  }
  vector<int> a(5);
  iota(a.begin(),a.end(),0);
  do{
    vector<int> p(5);
    for(int i=0;i<5;i++) p[a[i]]=i;
    bool f=1;
    for(int i=0;i<5;i++){
      if(p[v[i].first]>p[v[i].second]) f=0;
    }
    if(f){
      for(int i=0;i<5;i++) cout<<(char)(a[i]+'A');
      cout<<"\n";
      return 0;
    }
  }while(next_permutation(a.begin(),a.end()));
  cout<<"impossible\n";
  return 0;
}


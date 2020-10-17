#include <bits/stdc++.h>
#define ll long long
using namespace std;
 
int main() {
  freopen("abbreviation.in","r",stdin);
  freopen("abbreviation.out","w",stdout);
  ios_base::sync_with_stdio(0), cin.tie(0);
  vector<string> sa;
  string s,sep;
  char c=0;
  auto dump=[&](){
    if(sa.empty()) return;
    if(sa.size()==1) cout<<sa[0];
    else{
      string fst;
      for(auto &i:sa) fst+=i[0];
      cout<<fst<<" (";
      for(int i=0;i<(int)sa.size();i++)
        cout<<sa[i]<<" )"[i+1==(int)sa.size()];
    }
    sa.clear();
  };
  while(c!=EOF){
    while(!isalpha(c=getchar())&&c!=EOF) sep+=c;
    if(sep!=" "||sa.empty()){
      dump(); cout<<sep; sep="";
    }
    if(c==EOF) break;
    s=c;
    while(isalpha(c=getchar())) s+=c;
    bool f=isupper(s[0])&&(s.size()>1);
    for(int i=1;i<(int)s.size();i++) f=f&&islower(s[i]);
    if(f) sa.push_back(s);
    else{
      dump(); cout<<sep; cout<<s;
    }
    sep=c;
  }
  dump();
  return 0;
}

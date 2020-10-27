#include <bits/stdc++.h>
#define ll long long
using namespace std;
 
map<ll,ll> mp,p;
 
int main() {
  string filename="expect";
  freopen((filename+".in").data(),"r",stdin);
  freopen((filename+".out").data(),"w",stdout);
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n,q; cin>>n>>q;
  ll cn=0,pt=0;
  for(int i=0;i<n;i++){
    char c; ll t,k; cin>>c>>t>>k;
    if(c=='-'){
      if(cn>0) mp[cn]+=t-pt;
      cn+=k;
    }
    else{
      if(cn>0) mp[cn]+=t-pt;
      cn-=k;
    }
    pt=t;
  }
  ll ps=0,pc=0;
  for(auto i=mp.rbegin();i!=mp.rend();i++)
    i->second+=pc,pc=i->second;
  pc=0;
  p[0]=0;
  for(auto &&i:mp)
    ps=p[i.first]=ps+i.second*(i.first-pc),pc=i.first;
  while(q--){
    ll k; cin>>k;
    if(k<cn) cout<<"INFINITY\n";
    else if(k>=pc) cout<<"0\n";
    else{
      int nk=mp.upper_bound(k)->first,pk=prev(p.upper_bound(k))->first;
      ll cs=p[pk]+(k-pk)*mp[nk];
      cout<<ps-cs<<"\n";
    }
  }
  return 0;
}

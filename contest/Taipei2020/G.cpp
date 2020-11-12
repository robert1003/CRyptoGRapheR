#include<bits/stdc++.h>
#define ll long long

using namespace std;

ll mul(ll a,ll b,ll p){
  return (__int128)a*b%p;
}

vector<vector<vector<int>>> G;
vector<int> ni;
vector<bool> cyc,v;
vector<int> id;
stack<int> stk;
vector<string> h1,h2,rh1,rh2;
bool flag;

string tree(vector<vector<int>> &cG,int x,int p){
  vector<string> tmp1;
  for(int i:cG[x]){
    if(!cyc[i]&&i!=p){
      auto tmp=tree(cG,i,x);
      tmp1.push_back(tmp);
    }
  }
  sort(tmp1.begin(),tmp1.end());
  string ret = "(";
  for(auto &&x : tmp1)
    ret += x;
  return ret + ")";
}

void cycle(vector<vector<int>> &cG,int x,int p){
  if(flag) return;
  if(v[x]){
    while(stk.top()!=x){
      cyc[stk.top()]=1;
      id.push_back(stk.top());
      stk.pop();
    }
    cyc[x]=1; id.push_back(x);
    stk.push(x); cyc[x]=1;
    flag=1;
    return;
  }
  v[x]=1; stk.push(x);
  for(int i:cG[x]){
    if(i!=p){
      cycle(cG,i,x);
      if(flag) return;
    }
  }
  v[x]=0; stk.pop();
}

int minro(vector<string> &h){

  int a=0,n=h.size();// h.insert(h.end(),h.begin(),h.end());
  h.resize(n*2);
  for(int i = n; i < h.size(); ++i)
    h[i] = h[i-n];
  for(int b=0;b<n;b++){
    for(int k=0;k<n;k++){
      if(a+k==b||h[a+k]<h[b+k]){
        b+=max(0,k-1); break;
      }
      if(h[a+k]>h[b+k]){
        a=b;
        break;
      }
    }
  }
  return a;
}

tuple<int,vector<string>> jelly(vector<vector<int>> &cG,int n){
  while(!stk.empty()) stk.pop();
  cyc.assign(n,0);
  id.clear(); id.reserve(n);
  v.assign(n,0);
  flag=0; cycle(cG,0,0);
  int m=id.size();
  h1.resize(m);
  rh1.resize(m);
  for(int i=0;i<m;i++){
    auto ret=tree(cG,id[i],id[i]);
    h1[i]=ret;
    rh1[m-i-1]=ret;
  }
  int i1=minro(h1),ri1=minro(rh1);
  h1=vector<string>(h1.begin()+i1,h1.begin()+i1+m);
  rh1=vector<string>(rh1.begin()+ri1,rh1.begin()+ri1+m);
  if(rh1<h1) h1=rh1;
  return make_tuple(m, h1);
}

int main(){
  ios::sync_with_stdio(0); cin.tie(0);
  int t; cin>>t;
  while(t--){
    int k; cin>>k;
    G.clear(); G.resize(k);
    ni.resize(k);
    vector<tuple<int,int,vector<string>>> tot(k);
    for(int i=0;i<k;i++){
      cin>>ni[i]; G[i].resize(ni[i]);
      for(int j=0;j<ni[i];j++){
        int a,b; cin>>a>>b;
        G[i][a-1].push_back(b-1);
        G[i][b-1].push_back(a-1);
      }
      auto ret=jelly(G[i],ni[i]);
      tot[i]=make_tuple(ni[i],get<0>(ret),get<1>(ret));
    }
    sort(tot.begin(),tot.end());
    cout<<unique(tot.begin(),tot.end())-tot.begin()<<"\n";
  }
  return 0;
}

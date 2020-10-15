#include<bits/stdc++.h>
#define ll long long
 
using namespace std;
 
struct Node{
  ll sz;
  map<string,Node*> sub;
  Node():sz(0){sub.clear();}
  void *operator new(size_t);
}mem[1000005];
int top=0;
void* Node::operator new(size_t){
  return mem+top++;
}
 
void insert(Node* root,string s,ll sz){
  Node *cur=root; cur->sz+=sz;
  for(int i=1,p;(p=s.find('/',i))!=-1;i=p+1){
    string d=s.substr(i,p-i);
    if(!cur->sub.count(d)) cur->sub[d]=new Node;
    cur=cur->sub[d]; cur->sz+=sz;
  }
}
 
void print(Node *cur,ll t,string &&s){
  int cnt=0;
  for(auto &&i:cur->sub){
    if(i.second->sz>=t) cnt++;
  }
  if(cur->sub.empty()) cout<<"  ";
  else if(cnt==0) cout<<"+ ";
  else cout<<"- ";
  cout<<s<<" "<<cur->sz<<"\n";
  if(cnt){
    for(auto &&i:cur->sub)
      print(i.second,t,s+i.first+"/");
  }
}
 
int main(){
  cin.tie(0); ios::sync_with_stdio(0);
  int n; cin>>n;
  Node *root=new Node;
  for(int i=0;i<n;i++){
    string s; ll k; cin>>s>>k;
    insert(root,s,k);
  }
  ll t; cin>>t;
  print(root,t,"/");
  return 0;
}

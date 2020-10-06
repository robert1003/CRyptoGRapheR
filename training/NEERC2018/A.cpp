#include<bits/stdc++.h>
#define F first
#define S second
#define ll long long
#define MP make_pair
 
using namespace std;
 
void print(vector<array<int, 2> > v, bool swp) {
  int a = 0, b = 0;
  for(auto i : v) {
    a += i[0] > i[1];
    b += i[1] > i[0];
  }
  if(swp) cout << b << ":" << a << '\n';
  else cout << a << ":" << b << '\n';
  for(int i = 0 ; i < (int)v.size() ; ++i) {
    if(swp) cout << v[i][1] << ':' << v[i][0];
    else cout << v[i][0] << ':' << v[i][1];
    if(i != (int)v.size() - 1) cout << ' ';
  }
  cout << '\n';
}
 
int a, b;
 
bool solve(bool swp) {
    vector<int> vi;
    if(swp) vi = {2, 1, 0};
    else vi = {0, 1, 2};
    for(auto i : vi) {
      int A = a, B = b;
      vector<array<int, 2> > v;
      v.push_back({25, 0}); A -= 25;
      v.push_back({25, 0}); A -= 25;
      for(int j = 0 ; j < i ; ++j) {
        B -= 25;
        v.push_back({0, 25});
      }
      if(i == 2) v.push_back({15, 0}), A -= 15;
      else v.push_back({25, 0}), A -= 25;
      if(A < 0 || B < 0) continue;
      if(max(A,B)<23){
        if(A&&i==0) continue;
        v[0][1]+=B; v[2][0]+=A;
        print(v,swp);
        return 1;
      }
      if(A>B){
        if(i==0) continue;
        v[2][0]+=23; A-=23;
        int k=min(A,B);
        v[2][0]+=k; v[2][1]+=k;
        A-=k; B-=k;
      }
      else{
        v[0][1]+=23; B-=23;
        int k=min(A,B);
        v[0][0]+=k; v[0][1]+=k;
        A-=k; B-=k;
      }
      for(int i=0;i<(int)v.size();i++){
        if(A&&v[i][0]==0){
          int k=min(A,23); A-=k; v[i][0]+=k;
        }
        if(B&&v[i][1]==0){
          int k=min(B,(i==4?13:23)); B-=k; v[i][1]+=k;
        }
      }
      if(!A&&!B){
        print(v,swp);
        return 1;
      }
    }
    return 0;
    /*  
      for(int j = i + 3 ; j >= 0 ; --j) {
        if(v[j][0] > v[j][1]) {
          int mb = min(v[j][0] - 2, B);
          v[j][1] += mb;
          B -= mb;
        }
        else {
          int ma = min(v[j][1] - 2, A);
          v[j][0] += ma;
          A -= ma;
        }
      }
 
      vector<int> aw, bw = {1};
      if(i == 2) {
        for(int j = 0 ; j < i ; ++j) aw.push_back(j + 2);
      }
      else {
        for(int j = 0 ; j < i ; ++j) aw.push_back(j + 2);
        bw.push_back((int)v.size() - 1);
      }
      int ii = (i == 2 ? 4 : 0);
 
      //print(v, swp);
      //cerr << "A: " << A << " B: " << B << '\n';
      int idxa = (aw.size() ? aw.size() - 1 : -1), idxb = (bw.size() ? bw.size() - 1 : -1);
      while(A > 0 || B > 0) {
        while(A == 0 && (!aw.empty() && idxa >= 0 && v[aw[idxa]][0] == 0)) idxa--;
        while(B == 0 && (!bw.empty() && idxb >= 0 && v[bw[idxb]][1] == 0)) idxb--;
        if(A == 0 && idxa >= 0) A++, v[aw[idxa]][0]--;
        if(B == 0 && idxb >= 0) B++, v[bw[idxb]][1]--;
        if(A == 0 || B == 0) break;
        A--, B--;
        v[ii][0]++, v[ii][1]++;
      //cerr << "A: " << A << " B: " << B << '\n';
      }
      if(A == 0 && B == 0) {
        print(v, swp);
        return true;
      }
    }
    return false;
    */
    
}
 
int main(){
  cin.tie(0); ios::sync_with_stdio(0);
 
  int t; cin >> t;
  while(t--) {
    cin >> a >> b;
    if(!solve(0)) {
      swap(a, b);
      if(!solve(1)) {
        cout << "Impossible\n";
      }
    }
  }
 
  return 0;
}

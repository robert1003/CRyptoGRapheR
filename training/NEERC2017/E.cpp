#include<bits/stdc++.h>
#define ll long long
 
using namespace std;
 
int a[1005],ans[1005],c[1005];
 
int main(){
    cin.tie(0); ios::sync_with_stdio(0);
    int n; cin>>n;
    for(int i=0;i<n;i++) cin>>a[i];
    int l=0,r=0;
    for(int i=0;i<n;i++){
        if(a[i]>0) c[a[i]]++;
        else if(a[i]==0) r++;
        else{
            if(c[-a[i]]) --c[-a[i]];
            else if(r>l) ans[l++]=-a[i];
            else{
                cout<<"No\n";
                return 0;
            }
        }
    }
    cout<<"Yes\n";
    for(int i=0;i<r;i++) cout<<max(ans[i],1)<<" \n"[i+1==r];
    return 0;
}

#include<bits/stdc++.h>
#define ll long long

using namespace std;

int main(){
    cin.tie(0); ios::sync_with_stdio(0);
    pair<ll,ll> _a,_b;
    cin>>_a.first>>_a.second>>_b.first>>_b.second;
    int n; cin>>n;
    while(n--){
        ll x; cin>>x;
        pair<ll,ll> a,b;
        a.first=_a.first-x; a.second=_a.second-x;
        b.first=_b.first-x; b.second=_b.second-x;
        if((a.first<0)^(a.second<0)){
            a.second=max(abs(a.first),abs(a.second));
            a.first=0;
        }
        else{
            a.first=abs(a.first); a.second=abs(a.second);
            if(a.first>a.second) swap(a.first,a.second);
        }
        if((b.first<0)^(b.second<0)){
            b.second=max(abs(b.first),abs(b.second));
            b.first=0;
        }
        else{
            b.first=abs(b.first); b.second=abs(b.second);
            if(b.first>b.second) swap(b.first,b.second);
        }
        if(a>b) swap(a,b);
        if(a.second<=b.first) cout<<a.second-a.first+b.second-b.first<<"\n";
        else cout<<max(a.second,b.second)-a.first<<"\n";
    }
    return 0;
}

#include<bits/stdc++.h>
#define ll long long
#define mod 1000000007LL

using namespace std;

int p[1000005],sz[1000005];
ll a[1000005],mn[1000005],mx[1000005];

int find(int x){
    return x==p[x]?x:p[x]=find(p[x]);
}

int merge(int x,int y){
    if(sz[x]<sz[y]) swap(x,y);
    p[y]=x;
    sz[x]+=sz[y];
    mn[x]=min(mn[x],mn[y]);
    mx[x]=max(mx[x],mx[y]);
    return x;
}

int main(){
    cin.tie(0); ios::sync_with_stdio(0);
    int n; cin>>n;
    for(int i=0;i<n;i++) cin>>a[i];
    set<pair<ll,int>> s1,s2;
    function<void(int)> push=[&](int x){
        if(mx[x]>=0) s1.insert({mx[x],x});
        else s2.insert({mx[x],x});
        if(mn[x]>=0) s1.insert({mn[x],x});
        else s2.insert({mn[x],x});
    };
    function<void(int)> pop=[&](int x){
        if(mx[x]>=0) s1.erase({mx[x],x});
        else s2.erase({mx[x],x});
        if(mn[x]>=0) s1.erase({mn[x],x});
        else s2.erase({mn[x],x});
    };
    auto getmx=[&](){
        vector<int> x,y;
        for(auto i=s1.rbegin();i!=s1.rend();i++){
            if(x.empty()||i->second!=x[0]) x.push_back(i->second);
            if(x.size()==2) break;
        }
        for(auto i=s2.begin();i!=s2.end();i++){
            if(y.empty()||i->second!=y[0]) y.push_back(i->second);
            if(y.size()==2) break;
        }
        if(x.size()==1&&y.size()==1) return make_tuple(mn[x[0]]*mx[y[0]],x[0],y[0]);
        if(x.size()<=1) return make_tuple(mn[y[0]]*mn[y[1]],y[0],y[1]);
        else if(y.size()<=1) return make_tuple(mx[x[0]]*mx[x[1]],x[0],x[1]);
        ll xx=mx[x[0]]*mx[x[1]],yy=mn[y[0]]*mn[y[1]];
        if(xx>=yy) return make_tuple(xx,x[0],x[1]);
        else return make_tuple(yy,y[0],y[1]);
    };
    auto getmn=[&](){
        if(!s1.empty()&&!s2.empty()){
            vector<int> x,y;
            for(auto i=s1.rbegin();i!=s1.rend();i++){
                if(x.empty()||i->second!=x[0]) x.push_back(i->second);
                if(x.size()==2) break;
            }
            for(auto i=s2.begin();i!=s2.end();i++){
                if(y.empty()||i->second!=y[0]) y.push_back(i->second);
                if(y.size()==2) break;
            }
            if(x[0]!=y[0]) return make_tuple(mx[x[0]]*mn[y[0]],x[0],y[0]);
            else if(x.size()==1) return make_tuple(mx[x[0]]*mn[y[1]],x[0],y[1]);
            else if(y.size()==1) return make_tuple(mx[x[1]]*mn[y[0]],x[1],y[0]);
            else{
                ll xx=mx[x[0]]*mn[y[1]],yy=mx[x[1]]*mn[y[0]];
                if(xx<=yy) return make_tuple(xx,x[0],y[1]);
                else return make_tuple(yy,x[1],y[0]);
            }
        }
        else if(s2.empty()){
            vector<int> x;
            for(auto i=s1.begin();i!=s1.end();i++){
                if(x.empty()||i->second!=x[0]) x.push_back(i->second);
                if(x.size()==2) break;
            }
            return make_tuple(mn[x[0]]*mn[x[1]],x[0],x[1]);
        }
        else{
            vector<int> y;
            for(auto i=s2.rbegin();i!=s2.rend();i++){
                if(y.empty()||i->second!=y[0]) y.push_back(i->second);
                if(y.size()==2) break;
            }
            return make_tuple(mx[y[0]]*mx[y[1]],y[0],y[1]);
        }
    };
    copy(a,a+n,mn); copy(a,a+n,mx);
    iota(p,p+n,0); fill(sz,sz+n,1);
    ll ans1=0,ans2=0;
    for(int i=0;i<n;i++) push(i);
    for(int i=1;i<n;i++){
        ll w; int x,y; tie(w,x,y)=getmx();
        ans2=((ans2+w%mod)+mod)%mod;
        pop(x); pop(y); push(merge(x,y));
    }
    copy(a,a+n,mn); copy(a,a+n,mx);
    iota(p,p+n,0); fill(sz,sz+n,1);
    s1.clear(); s2.clear();
    for(int i=0;i<n;i++) push(i);
    for(int i=1;i<n;i++){
        ll w; int x,y; tie(w,x,y)=getmn();
        ans1=((ans1+w%mod)+mod)%mod;
        pop(x); pop(y); push(merge(x,y));
    }
    cout<<ans1<<" "<<ans2<<"\n";
    return 0;
}

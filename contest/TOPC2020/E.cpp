#include<bits/stdc++.h>
#define ll long long

using namespace std;

bitset<20> s,t,c;
bitset<20> a[1048576];
int id[20];
bool v[20];

void init(){
    a[0].reset(); a[1].reset(); a[1][0]=1;
    for(int i=1;i<19;i++){
        int sz=(1<<i);
        for(int j=0;j<sz;j++) a[sz+j]=a[sz-j-1],a[sz+j][i]=1;
    }
}

int main(){
    cin.tie(0); ios::sync_with_stdio(0);
    init();
    cin>>s>>t;
    int k; cin>>k;
    if((((s^t).count()^k)&1)||(s^t).count()>k||s==t){
        cout<<"-1\n";
        return 0;
    }
    int i=0;
    while(s[i]==t[i]) i++;
    c.reset();
    for(int j=0,kk=0;j<20;j++){
        if(i==j) continue;
        id[kk]=j;
        c[kk]=s[j]^t[j];
        kk++;
    }
    int st=0;
    while(a[st]!=c) st++;
    while(1){
        int ns=(st+1)%(1<<19);
        if(a[ns].count()+1>k) break;
        int j=(a[st]^a[ns])._Find_first();
        s.flip(id[j]);
        cout<<s<<"\n";
        k--;
        st=ns;
    }
    s.flip(i); cout<<s<<"\n"; v[i]=1; k--;
    vector<int> res;
    for(int j=0;j<20;j++){
        if(s[j]!=t[j]){
            k--,res.push_back(j),v[j]=1;
        }
    }
    k>>=1;
    vector<int> fl;
    for(int j=0;k;j++){
        if(!v[j]) fl.push_back(j),k--;
    }
    for(int j:fl) s.flip(j),cout<<s<<"\n";
    for(int j:res) s.flip(j),cout<<s<<"\n";
    for(int j:fl) s.flip(j),cout<<s<<"\n";
    return 0;
}

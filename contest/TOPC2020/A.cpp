#include<bits/stdc++.h>
#define ll long long

using namespace std;

int main(){
    cin.tie(0); ios::sync_with_stdio(0);
    int n,m; cin>>n>>m;
    cout<<n<<" "<<m<<"\n";
    while(n){
        n--;
        cout<<n<<" "<<m<<"\n";
    }
    while(m){
        m--;
        cout<<n<<" "<<m<<"\n";
    }
    for(int i=0;i<10;i++){
        if(i&1){
            for(int j=9;j>=0;j--)
                cout<<i<<" "<<j<<"\n";
        }
        else{
            for(int j=(i==0?1:0);j<10;j++)
                cout<<i<<" "<<j<<"\n";
        }
    }
    return 0;
}

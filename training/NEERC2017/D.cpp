#include<bits/stdc++.h>
#define ll long long
 
using namespace std;
 
int main(){
    cin.tie(0); ios::sync_with_stdio(0);
    int a,b,c; cin>>a>>b>>c;
    int mx=max(a,max(b,c)),mn=min(a,min(b,c)),md=a+b+c-mx-mn;
    if(mn<(mx+md-1)/md){
        cout<<"-1\n";
        return 0;
    }
    vector<tuple<int,int,int>> arr;
    for(int i=0,j=0;i<mx;i+=md,j++){
        for(int k=0;k<md&&i+k<mx;k++)
            arr.push_back(make_tuple(k,j,0));
    }
    int r=mn-(mx+md-1)/md;
    for(int i=1;i<=r;i++) get<1>(arr[i])=-i;
    char cc[3]={};
    if(a>=b&&a>=c) cc[2]='z';
    else if(b>=c) cc[1]='z';
    else cc[0]='z';
    if(c<=a&&c<=b) cc[0]='x';
    else if(b<=a) cc[1]='x';
    else cc[2]='x';
    char res='x'+'y'+'z'-cc[0]-cc[1]-cc[2];
    if(cc[0]==0) cc[0]=res;
    else if(cc[1]==0) cc[1]=res;
    else cc[2]=res;
    cout<<arr.size()<<"\n";
    for(int i=0;i<(int)arr.size();i++){
        int x,y,z; tie(x,y,z)=arr[i];
        for(int j=0;j<3;j++){
            if(cc[j]=='x') cout<<x<<" \n"[j==2];
            else if(cc[j]=='y') cout<<y<<" \n"[j==2];
            else cout<<z<<" \n"[j==2];
        }
    }
    return 0;
}

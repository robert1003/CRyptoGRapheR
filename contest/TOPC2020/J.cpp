#include<bits/stdc++.h>
#define ll long long

using namespace std;

double dp[13][13];

int main(){
    cin.tie(0); ios::sync_with_stdio(0);
    int t; cin>>t;
    while(t--){
        double a,b; cin>>a>>b;
        for(int i=0;i<13;i++){
            for(int j=0;j<13;j++)
                dp[i][j]=0;
        }
        dp[0][0]=1.0;
        for(int i=0;i<=10;i++){
            for(int j=0;j<=10;j++){
                if(i==10&&j==10) continue;
                if((i+j)&2){
                    dp[i][j+1]+=dp[i][j]*b;
                    dp[i+1][j]+=dp[i][j]*(1-b);
                }
                else{
                    dp[i+1][j]+=dp[i][j]*a;
                    dp[i][j+1]+=dp[i][j]*(1-a);
                }
            }
        }
        double x=0,y=0,z=0;
        for(int i=0;i<10;i++) x+=dp[11][i];
        for(int i=0;i<10;i++) y+=dp[i][11];
        z=dp[10][10];
        //cout<<x<<" "<<y<<" "<<z<<" "<<x+y+z<<"\n";
        x+=z*(1/(1-(a*b+(1-a)*(1-b))))*a*(1-b);
        y+=z*(1/(1-(a*b+(1-a)*(1-b))))*b*(1-a);
        //cout<<x<<" "<<y<<"\n";
        double p = x, q = y;
        double ans = p * p * p * p * (1 + (1 - p) * 4 + (1 - p) * (1 - p) * 10 + (1 - p) * (1 - p) * (1 - p) * 20);  
        cout << fixed << setprecision(12) << ans << '\n';

    }
    return 0;
}
